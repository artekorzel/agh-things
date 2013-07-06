import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {
	private static final int BUFLEN = 20;
	private static Socket socket = null;	
	private static boolean working = true;	
	private static byte[] toSend;
	private static InputStream serverIn;
	private static OutputStream serverOut;

	public static void main(String[] args) {
		boolean isSecurityContextOk = initializeSecurityContext(args);
		if(!isSecurityContextOk) {
			return;
		}
		
		Operation choosenOperation = chooseOperation();
		
		while(working) {	
			try {
				prepareSocketAndStreams(args);

				System.out.println("Wysylamy: " + new String(toSend));
				serverOut.write(toSend);	//wyslij przetworzona wartosc podana na standardowe wejscie
				
				byte[] received = new byte[BUFLEN];
				int numberOfReceivedBytes = serverIn.read(received);	//odbierz zmieniona wartosc od serwera i przetworz zaleznie od typu
				choosenOperation.consumeAfterReceive(received, numberOfReceivedBytes);
				
				socket.close();
			} catch (IOException e) {
				System.err.println(e.getMessage());
				working = false;
			}
			
			choosenOperation = chooseOperation();
		}
	}
	
	private static boolean initializeSecurityContext(String[] args) {
		if(args.length != 2) {
			System.out.println("Usage: java -jar zad1_client.jar <IP> <PORT>\n");
			return false;
		}
		
		Runtime.getRuntime().addShutdownHook(new Thread() {

			@Override
			public void run() {
				if (Client.socket != null)
					try {
						Client.socket.close();
					} catch (IOException e1) {
						System.err.println(e1.getMessage());
					}
			}
			
		});
		
		return true;
	}
	
	private static Operation chooseOperation() {
		String operationNumberString = System.console().readLine("Wybierz operacje:\n1:\tWyslij jednobajtowa liczbe\n2:\tWyslij " +
				"dwubajtowa liczbe\n4:\tWyslij czterobajtowa liczbe\n[inne]\tZakoncz\n");
		int operationNumber;
		try {
			operationNumber = Integer.parseInt(operationNumberString);
		} catch (NumberFormatException e) {
			operationNumber = 0;	//wybierz END_WORK
		}
		Operation choosenOperation = Operation.valueOfOperation(operationNumber);
		choosenOperation.obtainValueToSend();
		choosenOperation.prepareToSendOrStop();
		return choosenOperation;
	}

	public static void prepareSocketAndStreams(String[] args)
			throws UnknownHostException, IOException {
		socket = new Socket(args[0], Integer.parseInt(args[1]));	//polacz z serwerem oraz pobierz streamy
		serverIn = socket.getInputStream();
		serverOut = socket.getOutputStream();
	}

	public static void setWorking(boolean working) {
		Client.working = working;
	}

	public static void setToSend(byte toSend[]) {
		Client.toSend = toSend;
	}	
}
