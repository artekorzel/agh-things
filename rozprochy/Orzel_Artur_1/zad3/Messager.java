import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Messager {
	private static final String HASH_DELIMITER = "/0/0"; 
	// po tej sekwencji  wystepuje hash
	
	private static final String MESSAGE_DELIMITER = "/0"; 
	// sekwencja rozdzielajaca elementy wiadomosci
	
	private static final SimpleDateFormat dateFormat = 
			new SimpleDateFormat("hh:mm:ss");
	
	private static String nick; 
	// charakterystyczny dla danego hosta, wiec ustawiamy raz

	public static void setNick(String nick) {
		Messager.nick = nick;
	}

	public static String prepareMessage(String message) {
		// przygotuj wiadomosc
		StringBuilder builder = new StringBuilder(nick);
		builder.append(MESSAGE_DELIMITER)
				.append(dateFormat.format(new Date()))
				.append(MESSAGE_DELIMITER).append(message);
		String hash = Integer.toString(evaluateHash(builder.toString()));
		
		// oblicz hash i dodaj do wiadomosci
		builder.append(HASH_DELIMITER).append(hash);
		return builder.toString();
	}

	public static void checkAndPrintMessage(byte[] messageContent) {
		String rawMessage;
		try {
			rawMessage = new String(messageContent, "ASCII"); 
			// pobierz wiadomosc do stringa
			
		} catch (UnsupportedEncodingException e) {
			System.err
					.println("SYSTEM: Problem z kodowaniem, uzycie defaultowego");
			rawMessage = new String(messageContent);
		}

		// sprawdz czy tylko jeden raz wystepuje sekwencja przezd hashem
		String[] splitedRawMessage = rawMessage.split(HASH_DELIMITER);
		if (splitedRawMessage.length != 2) {
			System.err.println("SYSTEM: Bledna wiadomosc, pominieto.");
			return;
		}

		checkMessageHash(splitedRawMessage); // sprawdz hash
	}

	private static void checkMessageHash(String[] splitedRawMessage) {
		int receivedHash; // pobierz hash ucinajac zera na koncu tablicy
		try {
			receivedHash = Integer.parseInt(splitedRawMessage[1].replace("\0",
					""));
		} catch (NumberFormatException e) {
			System.err.println("SYSTEM: Bledna wiadomosc, pominieto.");
			return;
		}

		if (receivedHash == evaluateHash(splitedRawMessage[0])) {
			// jesli prawidlowy hash to sprawdz poprawnosc zawartosci samej
			// wiadomosci - czy wszystkie wymagane pola
			String[] splitedMessage = splitedRawMessage[0]
					.split(MESSAGE_DELIMITER);

			if (splitedMessage.length != 3) {
				System.err
						.println("SYSTEM: Bledna zawartosc wiadomosci, pominieto.");
				return;
			}

			// jesli nie naszego autorstwa to wypisujemy
			if (!splitedMessage[0].equals(nick)) {
				System.out.println(String
						.format("%s %s: %s", splitedMessage[1],
								splitedMessage[0], splitedMessage[2]));
			}
		} else {
			System.err.println("SYSTEM: Bledny hash wiadomosci, pominieto.");
			return;
		}
	}

	private static int evaluateHash(String messageContent) {
		// oblicz hash jako sume wszystkich znakow modulo 1000
		int hash = 0;
		byte[] content;

		try {
			content = messageContent.getBytes("ASCII");
		} catch (UnsupportedEncodingException e) {
			System.err.println("SYSTEM: Problem " +
					"z kodowaniem, uzycie defaultowego");
			content = messageContent.getBytes();
		}

		for (byte c : content) {
			hash = (hash + c) % 1000;
		}

		return hash;
	}
}
