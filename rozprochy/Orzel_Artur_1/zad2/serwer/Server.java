import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
	private static final int BUFLEN = 1024;

	public static void main(String[] args) {
		if (args.length != 2) {
			System.out.println("Uzycie: java -jar zad2_server.jar <PORT> <PLIK>");
			return;
		}

		byte[] buffer = new byte[BUFLEN];
		int length;

		ServerSocket serverSocket = null;
		Socket clientSocket = null;
		FileInputStream file = null;
		try {
			// tworzymy socket serwera
			serverSocket = new ServerSocket(Integer.parseInt(args[0])); 
			
			System.out.println("Oczekiwanie na klienta...\n");
			
			// pobieramy socket klienta po zaakceptowaniu polaczenia
			clientSocket = serverSocket.accept(); 
							
			// pobieramy stream wyjsciowy
			OutputStream out = clientSocket.getOutputStream(); 			

			file = new FileInputStream(args[1]);

			while ((length = file.read(buffer)) > 0) {
				out.write(buffer, 0, length);
			}

		} catch (IOException e) {
			e.printStackTrace();
			return;
		} catch (NumberFormatException e) {
			e.printStackTrace();
			return;
		} finally {
			if (file != null) {
				try {
					file.close();
				} catch (IOException e) {
					//nic nie mozna zrobic
				}
			}
			if (clientSocket != null) {
				try {
					clientSocket.close();
				} catch (IOException e) {
					//nic nie mozna zrobic
				}
			}
			if (serverSocket != null) {
				try {
					serverSocket.close();
				} catch (IOException e) {
					//nic nie mozna zrobic
				}
			}
		}
		
		System.out.println("Przesyłanie zakończone sukcesem.");
	}

}
