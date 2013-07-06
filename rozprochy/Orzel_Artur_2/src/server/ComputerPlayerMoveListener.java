package server;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Random;

import publ.GameBoard;
import publ.GameBoardCell;
import publ.IMoveListener;
import publ.IPlayer;
import publ.IServerService;

public class ComputerPlayerMoveListener extends UnicastRemoteObject implements IMoveListener {
	
	private GameBoardCell playerCell;
	private IServerService serverService;
	private IPlayer player;

	public ComputerPlayerMoveListener(IServerService serverService, IPlayer player) throws RemoteException {
		super();
		
		this.serverService = serverService;
		this.player = player;
	}

	@Override
	public void setPlayerCell(GameBoardCell playerCell) throws RemoteException {
		this.playerCell = playerCell;
	}

	@Override
	public void onPlayerMove(IPlayer player, GameBoard gameBoard) throws RemoteException {
		Random random = new Random();
		
		try {
			int boardSizeSquared = GameBoard.BOARD_SIZE * GameBoard.BOARD_SIZE;
			String move = Integer.toString(random.nextInt(boardSizeSquared));
			while(!gameBoard.doMoveIfProper(move, playerCell, serverService, this.player)) {
				move = Integer.toString(random.nextInt(boardSizeSquared));
			}
		} catch (Exception e) {
			System.err.println("Computer player failure!");
			doFinalize();
		}
	}

	@Override
	public void onVictory(GameBoard gameBoard) throws RemoteException {
		doFinalize();
	}

	@Override
	public void onLoss(GameBoard gameBoard) throws RemoteException {
		doFinalize();
	}

	@Override
	public void onTie(GameBoard gameBoard) throws RemoteException {
		doFinalize();
	}

	@Override
	public void onError(String message) throws RemoteException {
		doFinalize();
		
	}
	
	private void doFinalize() throws RemoteException {
		UnicastRemoteObject.unexportObject(this, false);
	}
	
}
