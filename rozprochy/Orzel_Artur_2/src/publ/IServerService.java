package publ;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IServerService extends Remote {
	public void register(IPlayer player) throws RemoteException, PlayerNotAllowedException;
	
	public void chooseGame(IPlayer player, GameType gameType) throws RemoteException, PlayerNotAllowedException;
	
	public void doMove(IPlayer player, GameBoard gameBoard) throws RemoteException, PlayerNotAllowedException;
}
