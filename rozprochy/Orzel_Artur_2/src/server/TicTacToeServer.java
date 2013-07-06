package server;

import java.io.FileInputStream;
import java.io.IOException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;

import publ.GameBoard;
import publ.GameBoardCell;
import publ.GameType;
import publ.IPlayer;
import publ.IServerService;
import publ.Player;
import publ.PlayerNotAllowedException;

public class TicTacToeServer {
	public static final String PROPERTIES_FILE = "properties.conf";
	
	private String rmiServerAddress;
	private String rmiServerPort;
	private String rmiServerName;
	private IServerService serverService;
	
	public TicTacToeServer() throws IOException {
		readProperties();
		serverService = new ServerService();
	}
	
	public void readProperties() throws IOException {
		Properties properties = new Properties();
		properties.load(new FileInputStream(PROPERTIES_FILE));
		rmiServerAddress = properties.getProperty("rmiServerAddress", "127.0.0.1"); 
		rmiServerPort = properties.getProperty("rmiServerPort", "1099"); 
		rmiServerName = properties.getProperty("rmiServerName", "server");
	}

	public static void main(String[] args) {
		TicTacToeServer server = null;
		
		try {
			server = new TicTacToeServer();
			IServerService stubServer = (IServerService) UnicastRemoteObject.exportObject(server.serverService, 0);
			String serviceBindPath = "rmi://" + server.rmiServerAddress 
					+ ":" + server.rmiServerPort + "/" + server.rmiServerName;
			Naming.rebind(serviceBindPath, stubServer);
		} catch(Exception e) {
			System.err.println("Problem with starting server");
			try {
				if(server.serverService != null) {
					UnicastRemoteObject.unexportObject(server.serverService, true);
					server.serverService = null;
				}
			} catch(Exception e1) {
				//ignorujemy - nic nie mozna zrobic
			}
		}
	}

}
