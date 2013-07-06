import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class MulticastChat {
	private static final int MAX_MESSAGE_LENGTH = 20;
	private static final int BUFLEN = 100;
	private static boolean working = true;
	private static int port;
	private static InetAddress groupAddress;
	private static MulticastSocket socket;

	public static void main(String[] args) {
		if (args.length != 3 || args[2].length() > 6) {
			System.out.println("Uzycie: java -jar zad3_chat.jar " +
					"<IP> <PORT> <NICK - maks 6 znakow>");
			return;
		}

		initialize(args); // inicjalizuje socket, adres, potrzebne wartosci pol

		DatagramPacket sending;
		System.out.println("Przygotowany do nadawania...");
		while (working) {
			String message = System.console().readLine(); // pobierz wiadomosc
			if (message.length() > MAX_MESSAGE_LENGTH) {
				System.err
						.println("Zbyt dluga wiadomosc - maksymalna dlugosc to 20");
				continue;
			}

			String preparedMessage = Messager.prepareMessage(message); 
			// przygotuj do wyslania w odpowiednim kodowaniu
			try { // na odpowiedni serwer
				sending = new DatagramPacket(preparedMessage.getBytes("ASCII"),
						preparedMessage.length(), groupAddress, port);
			} catch (UnsupportedEncodingException e) {
				System.err
						.println("SYSTEM: Problem z kodowaniem, uzycie defaultowego");
				sending = new DatagramPacket(preparedMessage.getBytes(),
						preparedMessage.length(), groupAddress, port);
			}

			try {
				socket.send(sending); // wyslij, jesli nieudane to koniec
			} catch (IOException e) {
				e.printStackTrace();
				working = false;
			}
		}

		finalizeSocket();
	}

	private static void initialize(String[] args) {
		String nick = args[2];
		Messager.setNick(nick);

		try {
			port = Integer.parseInt(args[1]); // pobierz numer portu
		} catch (NumberFormatException e) {
			e.printStackTrace();
			return;
		}

		Runtime.getRuntime().addShutdownHook(new Thread() { 
			// koniec pracy CTRL+C

					@Override
					public void run() {
						working = false;
						finalizeSocket();
					}

				});

		try {
			groupAddress = InetAddress.getByName(args[0]); 
			// pobierz adres grupowy i sprawdz czy odpowiedni

			if (!groupAddress.isMulticastAddress()) {
				throw new Exception(
						"Podany adres nie jest adresem multicastowym");
			}
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}

		try {
			// przygotuj socket komunikacyjny
			socket = new MulticastSocket(port); 
			socket.joinGroup(groupAddress);
		} catch (IOException e) {
			e.printStackTrace();
			if (socket != null) {
				socket.close();
			}
			return;
		}

		// przygotuj program do odbierania wiadomosci w osobnym watku
		startReceivingThread(); 
	}

	private static void startReceivingThread() {
		Thread receiver = new Thread() {

			@Override
			public void run() {
				byte[] buffer;
				DatagramPacket received;
				System.out.println("Przygotowany do odbierania...");
				while (working) {
					try {
						buffer = new byte[BUFLEN];
						received = new DatagramPacket(buffer, BUFLEN);
						socket.receive(received);
				
				// jesli dane w odpowiednim formacie to sparsuj i ladnie wypisz
						Messager.checkAndPrintMessage(received.getData());
					} catch (IOException e) {
						e.printStackTrace();
						working = false;
					}
				}
			}

		};
		receiver.start();
	}

	private static void finalizeSocket() { // zakoncz komunikacje

		if (socket != null) {
			try {
				socket.leaveGroup(groupAddress);
			} catch (IOException e) {
				e.printStackTrace();
			}
			socket.close();
		}
	}

}
