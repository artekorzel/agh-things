package pl.edu.agh.student.aorzel.server.mycommunicator;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import Common.Session;
import Common.UnknownCredentials;
import Ice.Current;
import MyCommunicator.Message;
import MyCommunicator.UserCallbackPrx;
import MyCommunicator.UserCallbackPrxHelper;
import MyCommunicator._RoomDisp;

public class RoomI extends _RoomDisp {
	public static final String ROOMS_FILE_PREFIX = "chat/rooms/";
	private static final long serialVersionUID = -7396619649532176631L;
	private final Map<String, UserInformations> loggedUsers = new ConcurrentHashMap<String, UserInformations>();

	private String roomName;

	public RoomI(String roomName) {
		this.roomName = roomName;
	}

	@Override
	public Session logIn(String userName, String password,
			UserCallbackPrx callback, Current __current)
			throws UnknownCredentials {
		UserInformations details = ChatManagerI.verifyAuthority(userName,
				password);

		Ice.ObjectPrx base = __current.con.createProxy(callback
				.ice_getIdentity());
		UserCallbackPrx callbackProxy = UserCallbackPrxHelper
				.uncheckedCast(base.ice_oneway());
		details.setCallback(callbackProxy);

		loggedUsers.put(details.getSessionId(), details);
		return new Session(details.getSessionId(), details.getSecureKey());
	}

	@Override
	public Message[] getRoomHistory(Session credentials, Current __current)
			throws UnknownCredentials {
		verifyAuthority(credentials);

		BufferedReader reader = null;
		List<Message> messages = new LinkedList<Message>();
		try {
			reader = new BufferedReader(new FileReader(ROOMS_FILE_PREFIX
					+ roomName));
			String line = reader.readLine();
			while (line != null) {
				messages.add(parseMessage(line));
				line = reader.readLine();
			}
		} catch (IOException e) {
			System.err.println("Cannot read file!");
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e) {
					// nothing can be done
				}
			}
		}
		return messages.toArray(new Message[0]);
	}

	private Message parseMessage(String line) {
		try {
			String[] messageElements = line.split(":");
			System.out.println(Arrays.toString(messageElements));
			Message message = new Message(Long.parseLong(messageElements[0]),
					messageElements[1], messageElements[2]);
			return message;
		} catch (Throwable e) {
			System.err.println("Cannot parse message!");
		}
		return new Message();
	}

	@Override
	public void sendMessage(Session credentials, Message msg, Current __current)
			throws UnknownCredentials {
		verifyAuthority(credentials);

		PrintWriter writer = null;
		try {
			writer = new PrintWriter(new BufferedWriter(new FileWriter(
					ROOMS_FILE_PREFIX + roomName, true)));
			writer.format("%d:%s:%s\n", msg.time, msg.userName, msg.content);
		} catch (IOException e) {
			System.err.println("Cannot read file!");
		} finally {
			if (writer != null) {
				writer.close();
			}
		}

		List<String> loggedOut = new ArrayList<String>();
		for (Map.Entry<String, UserInformations> user : loggedUsers.entrySet()) {
			UserCallbackPrx callback = user.getValue().getCallback();
			try {
				callback.sendNewMessage(msg);
			} catch (Throwable e) {
				loggedOut.add(user.getKey());
			}
		}
		for (String user : loggedOut) {
			loggedUsers.remove(user);
		}

		broadcastLoggedOut(loggedOut);
	}

	private void broadcastLoggedOut(List<String> loggedOut) {
		while (!loggedOut.isEmpty()) {
			List<String> loggedOut2 = new ArrayList<String>();
			for (Map.Entry<String, UserInformations> user : loggedUsers
					.entrySet()) {
				try {
					for (String userLoggedOut : loggedOut) {
						UserCallbackPrx callback = user.getValue()
								.getCallback();
						callback.sendNewMessage(new Message(System
								.currentTimeMillis() / 1000L, "SYSTEM",
								userLoggedOut.split(".")[0] + " logged out."));
					}
				} catch (Throwable e) {
					loggedOut2.add(user.getKey());
				}
			}
			for (String user : loggedOut2) {
				loggedUsers.remove(user);
			}

			loggedOut = loggedOut2;
		}
	}

	private void verifyAuthority(Session credentials) throws UnknownCredentials {
		if (!loggedUsers.containsKey(credentials.sessionId)
				|| !loggedUsers.get(credentials.sessionId).getSecureKey()
						.equals(credentials.secureKey)) {
			throw new UnknownCredentials();
		}
	}

	@Override
	public void logOut(Session credentials, Current __current)
			throws UnknownCredentials {
		verifyAuthority(credentials);
		loggedUsers.remove(credentials.sessionId);
		List<String> userId = new ArrayList<String>();
		userId.add(credentials.sessionId);
		broadcastLoggedOut(userId);
	}

}
