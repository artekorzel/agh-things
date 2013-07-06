package pl.edu.agh.student.aorzel.server.mycommunicator;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;

import Common.UnknownCredentials;
import Common.UserAlreadyExists;
import Ice.Current;
import MyCommunicator._ChatManagerDisp;

public class ChatManagerI extends _ChatManagerDisp {
	private static final String USER_FILE_PREFIX = "chat/users/";
	private static final long serialVersionUID = 8266554404091679834L;

	private static final Map<String, UserInformations> users = new ConcurrentHashMap<String, UserInformations>();

	private static UserInformations readPersonFile(File file) {
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(file));
			String line = reader.readLine();
			String[] details = line.split(":");
			System.out.println(Arrays.toString(details));
			return new UserInformations(details[0], details[1]);
		} catch (IOException e) {
			System.err.println("Cannot read file!");
		} finally {
			if(reader != null) {
				try {
					reader.close();
				} catch (IOException e) {
					//nothing can be done
				}
			}
		}
		return null;
	}
	
	@Override
	public void register(String userName, String password, Current __current)
			throws UserAlreadyExists {
		if (users.containsKey(userName)) {
			throw new UserAlreadyExists();
		}

		UserInformations userInformations = new UserInformations(userName, password);
		File file = new File(USER_FILE_PREFIX + userName);
		if(file.exists()) {
			throw new UserAlreadyExists();
		} else {
			PrintWriter writer = null;
			try {
				file.createNewFile();
				writer = new PrintWriter(file);
				writer.printf("%s:%s\n", userName, password);
			} catch (IOException e) {
				System.err.println("Cannot write to file!");
			} finally {
				if(writer != null) {
					writer.close();
				}
			}
		}
		users.put(userName, userInformations);
	}

	@Override
	public void hello(Current __current) {
		System.out.println("Notified");
	}

	public static UserInformations verifyAuthority(String userName,
			String password) throws UnknownCredentials {
		if(users.containsKey(userName)) {
			UserInformations details = users.get(userName);
			if(details.getPassword().equals(password)) {
				prepareCredentials(details);
				return details;
			}
		} else {
			File file = new File(USER_FILE_PREFIX + userName);
			UserInformations readDetails = readPersonFile(file);
			if(readDetails != null) {
				users.put(userName, readDetails);
				prepareCredentials(readDetails);
				return readDetails;
			}
		}
		throw new UnknownCredentials();
	}
	
	private static void prepareCredentials(UserInformations details) {
		details.setSessionId(details.getUserName() + "." + System.currentTimeMillis());
		details.setSecureKey(String.valueOf(new Random().nextLong()));
	}

}
