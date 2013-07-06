package client;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

import publ.GameBoard;
import publ.GameBoardCell;
import publ.IMoveListener;
import publ.IPlayer;
import publ.PlayerNotAllowedException;

public class PlayerMoveListener extends UnicastRemoteObject implements IMoveListener {
	
	private GameBoardCell playerCell;
	private TicTacToeClient client;

	public PlayerMoveListener(TicTacToeClient client) throws RemoteException {
		super();
		
		this.client = client;
	}

	@Override
	public void setPlayerCell(GameBoardCell playerCell) throws RemoteException {
		this.playerCell = playerCell;
	}

	@Override
	public void onPlayerMove(IPlayer player, GameBoard gameBoard)
			throws RemoteException {
		System.out.println("Player: " + player.getNick() 
				+ " moved:\n" + gameBoard.toString());
		String move = System.console().readLine("\nChoose your move(0 - 8): ");
		try {
			while(!gameBoard.doMoveIfProper(move, playerCell, client.getServerService(), client.getPlayer())) {
				move = System.console().readLine("Improper move, try again: ");
			}
		} catch (RemoteException e) {
			System.err.println("Problem with connection to the server");
			doFinalize();
		} catch (PlayerNotAllowedException e) {
			System.err.println("You are not allowed! Game over");
			doFinalize();
		}
	}

	@Override
	public void onVictory(GameBoard gameBoard) throws RemoteException {
		onGameOver(gameBoard, "You win!!!");
	}

	@Override
	public void onLoss(GameBoard gameBoard) throws RemoteException {
		onGameOver(gameBoard, "You lose!!!");
	}

	@Override
	public void onTie(GameBoard gameBoard) throws RemoteException {
		onGameOver(gameBoard, "Tie!!!");
	}
	
	private void onGameOver(GameBoard gameBoard, String message) throws RemoteException {
		System.out.println(message);
		System.out.println(gameBoard.toString());
		doFinalize();
	}

	@Override
	public void onError(String message) throws RemoteException {
		System.out.println(message);
		doFinalize();
		
	}
	
	private void doFinalize() throws RemoteException {
		UnicastRemoteObject.unexportObject(this, true);
		client.setServerService(null);
	}
	
}
