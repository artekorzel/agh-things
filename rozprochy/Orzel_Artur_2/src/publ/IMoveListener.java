package publ;

import java.rmi.Remote;
import java.rmi.RemoteException;


public interface IMoveListener extends Remote {
	public void setPlayerCell(GameBoardCell playerCell) throws RemoteException;
	
	public void onPlayerMove(IPlayer player, GameBoard gameBoard) throws RemoteException;
	
	public void onVictory(GameBoard gameBoard) throws RemoteException;
	
	public void onTie(GameBoard gameBoard) throws RemoteException;
	
	public void onLoss(GameBoard gameBoard) throws RemoteException;
	
	public void onError(String message) throws RemoteException;
	
}
