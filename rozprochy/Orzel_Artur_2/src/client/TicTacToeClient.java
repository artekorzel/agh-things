package client;

import java.io.FileInputStream;
import java.io.IOException;
import java.rmi.Naming;
import java.rmi.NoSuchObjectException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Properties;

import publ.GameType;
import publ.IMoveListener;
import publ.IServerService;
import publ.Player;
import publ.PlayerNotAllowedException;

public class TicTacToeClient {
	public static final String PROPERTIES_FILE = "properties.conf";

	private IServerService serverService;
	private Player player;
	private IMoveListener moveListener;
	private String rmiServerAddress;
	private String rmiServerPort;
	private String rmiServerName;
	
	public TicTacToeClient(String nick) throws IOException {
		player = new Player();
		player.setNick(nick);
		
		moveListener = new PlayerMoveListener(this);
		player.setMoveListener(moveListener);
		
		readProperties();
	}
	
	public void readProperties() throws IOException {
		Properties properties = new Properties();
		properties.load(new FileInputStream(PROPERTIES_FILE));
		rmiServerAddress = properties.getProperty("rmiServerAddress", "127.0.0.1"); 
		rmiServerPort = properties.getProperty("rmiServerPort", "1099"); 
		rmiServerName = properties.getProperty("rmiServerName", "server");
	}
	
	public static void main(String[] args) {
		if(args.length != 1) {
			System.err.println("Usage: ant client <nick>");
			return;
		}
		
		TicTacToeClient client = null;
		try {
			try {
				client = new TicTacToeClient(args[0]);		
				client.serverService = (IServerService) Naming.lookup("rmi://" + client.rmiServerAddress 
						+ ":" + client.rmiServerPort + "/" + client.rmiServerName);
				client.serverService.register(client.player);
				
				String gameType = System.console().readLine("Choose game:\n1: " +
						"Single player\n2: Multi player\n[else]: Quit\n");
				
				if(gameType.equals("1")) {
					client.serverService.chooseGame(client.player, GameType.SINGLE_PLAYER);
				} else if(gameType.equals("2")) {
					client.serverService.chooseGame(client.player, GameType.MULTI_PLAYER);
				} else {
					throw new Exception();
				}
				
			} catch(NotBoundException e) {
				System.err.println("Specified server service does not exist");
				throw new Exception();
			} catch(RemoteException e) {
				System.err.println("Problem with connection to server service");
				throw new Exception();
			} catch(IOException e) {
				System.err.println("Properties file not found");
				throw new Exception();
			} catch (PlayerNotAllowedException e) {
				System.err.println("Cannot start the game");
				throw new Exception();
			} 
		}catch (Throwable e) {
			if(client != null) {
				try {
					UnicastRemoteObject.unexportObject(client.moveListener, true);
					client.serverService = null;
				} catch (NoSuchObjectException e1) {
					System.err.println("Problem with disconnecting");
				}
			}
			return;
		}
	}

	public IServerService getServerService() {
		return serverService;
	}

	public void setServerService(IServerService serverService) {
		this.serverService = serverService;
	}

	public Player getPlayer() {
		return player;
	}
}
