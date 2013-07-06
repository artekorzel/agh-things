package server;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;

import publ.GameBoard;
import publ.GameBoardCell;
import publ.GameType;
import publ.IMoveListener;
import publ.IPlayer;
import publ.IServerService;
import publ.Player;
import publ.PlayerNotAllowedException;

public class ServerService implements IServerService {
	public static final String COMPUTER_PLAYER_NICK_PREFIX = "Computer ";

	private final List<IPlayer> playersWaitingForGame = new ArrayList<IPlayer>();
	private final Queue<IPlayer> playersWaitingForSecondOne = new LinkedList<IPlayer>();	
	private final Map<IPlayer, IPlayer> gameDetails = new HashMap<IPlayer, IPlayer>();
	private final AtomicInteger computerPlayersCounter = new AtomicInteger(0);

	@Override
	public void register(IPlayer player) throws RemoteException,
			PlayerNotAllowedException {		
		synchronized(playersWaitingForSecondOne) {
			if(playersWaitingForSecondOne.contains(player)) {
				throw new PlayerNotAllowedException("Nick already registered");
			}
			
			synchronized (gameDetails) {
				if(gameDetails.containsKey(player)
						|| gameDetails.containsValue(player)) {
					throw new PlayerNotAllowedException("Nick already registered");
				}
				
				synchronized(playersWaitingForGame) {
					if(playersWaitingForGame.contains(player)) {
						throw new PlayerNotAllowedException("Nick already registered");
					}	
					
					playersWaitingForGame.add(player);
				}
			}	
		}	
	}

	@Override
	public void chooseGame(IPlayer player, GameType gameType)
			throws RemoteException, PlayerNotAllowedException {
		synchronized(playersWaitingForGame) {
			if(!playersWaitingForGame.contains(player)) {
				throw new PlayerNotAllowedException("Player not registered");
			}
			
			if(gameType.equals(GameType.SINGLE_PLAYER)) {
				IPlayer computerPlayer = createComputerPlayer();
				initializeGameDetails(player, computerPlayer);
			} else {
				initializeMultiPlayerMode(player);
			}
			
			playersWaitingForGame.remove(player);
		}
	}

	private IPlayer createComputerPlayer() throws RemoteException {
		Player computerPlayer = new Player();
		computerPlayer.setNick(COMPUTER_PLAYER_NICK_PREFIX + computerPlayersCounter.incrementAndGet());
		computerPlayer.setMoveListener(new ComputerPlayerMoveListener(this, computerPlayer));
		return computerPlayer;
	}

	private void initializeMultiPlayerMode(IPlayer player) {
		synchronized(playersWaitingForSecondOne) {
			if(playersWaitingForSecondOne.isEmpty()) {
				playersWaitingForSecondOne.add(player);
			} else {
				IPlayer rival = playersWaitingForSecondOne.remove();
				initializeGameDetails(rival, player);
			}
		}
	}

	private void initializeGameDetails(IPlayer playerOne, IPlayer playerTwo) {	
		setPlayerCellOrSafelyDisconnect(playerOne, playerTwo, GameBoardCell.CROSS);	
		setPlayerCellOrSafelyDisconnect(playerTwo, playerOne, GameBoardCell.NOUGHT);		
		
		synchronized (gameDetails) {
			gameDetails.put(playerOne, playerTwo);
		}
		
		try {			
			GameBoard gameBoard = new GameBoard();
			playerOne.getMoveListener().onPlayerMove(playerTwo, gameBoard);
		} catch (RemoteException e) {
			finalizeGame(playerOne, "Problem with connection - game stopped");
		}
	}

	private void setPlayerCellOrSafelyDisconnect(IPlayer playerToSetCell, 
			IPlayer playerToInform, GameBoardCell cell) {
		try {
			playerToSetCell.getMoveListener().setPlayerCell(cell);
		} catch (RemoteException e) {
			System.err.println("Cannot set player's cell type");
			
			try {
				playerToInform.getMoveListener().onError("Problem with starting the game - disconnect and try again");
			} catch (RemoteException e1) {
				System.err.println("Problem with player's connection");
			}	
		}
	}

	private void finalizeGame(IPlayer playerOne, String message) {
		System.err.println(message);

		synchronized (gameDetails) {
			gameDetails.remove(playerOne);
		}
	}

	@Override
	public void doMove(IPlayer player, GameBoard gameBoard)
			throws RemoteException, PlayerNotAllowedException {
		IPlayer rival = null;
		IPlayer playerOne, playerTwo;
		
		synchronized(gameDetails) {
			if(gameDetails.containsKey(player)) {
				rival = gameDetails.get(player);
				playerOne = player;
				playerTwo = rival;
			} else {
				for(Map.Entry<IPlayer, IPlayer> entry : gameDetails.entrySet()) {
					if(entry.getValue().equals(player)) {
						rival = entry.getKey();
						break;
					}
				}
				
				if(rival == null) {
					throw new PlayerNotAllowedException("Player does not play any game");
				}
				
				playerOne = rival;
				playerTwo = player;
			}
		}
		
		boolean gameIsFinished =  gameBoard.checkIfFinished(playerOne, playerTwo);		
		summarizeGameBoardChange(gameIsFinished, gameBoard, player, rival, playerOne);
		
	}

	private void summarizeGameBoardChange(boolean gameIsFinished, GameBoard gameBoard, IPlayer player,
			IPlayer rival, IPlayer playerOne) throws RemoteException {
		IMoveListener playerMoveListener = player.getMoveListener();
		IMoveListener rivalIMoveListener = rival.getMoveListener();
		
		if(gameIsFinished) {
			synchronized(gameDetails) {
				gameDetails.remove(playerOne);
			}
			
			IPlayer winner = gameBoard.getWinner();
			
			if(winner == null) {
				playerMoveListener.onTie(gameBoard);
				rivalIMoveListener.onTie(gameBoard);
			} else if(winner.equals(rival)) {
				playerMoveListener.onLoss(gameBoard);
				rivalIMoveListener.onVictory(gameBoard);
			} else {	//equals player
				playerMoveListener.onVictory(gameBoard);
				rivalIMoveListener.onLoss(gameBoard);
			}
		} else {
			rivalIMoveListener.onPlayerMove(player, gameBoard);
		}
	}
}
