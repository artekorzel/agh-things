package pl.edu.agh.student.aorzel.chat;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.logging.Logger;

import org.jgroups.JChannel;
import org.jgroups.Message;
import org.jgroups.ReceiverAdapter;
import org.jgroups.protocols.BARRIER;
import org.jgroups.protocols.FD_ALL;
import org.jgroups.protocols.FD_SOCK;
import org.jgroups.protocols.FRAG2;
import org.jgroups.protocols.MERGE2;
import org.jgroups.protocols.MFC;
import org.jgroups.protocols.PING;
import org.jgroups.protocols.UDP;
import org.jgroups.protocols.UFC;
import org.jgroups.protocols.UNICAST2;
import org.jgroups.protocols.VERIFY_SUSPECT;
import org.jgroups.protocols.pbcast.FLUSH;
import org.jgroups.protocols.pbcast.GMS;
import org.jgroups.protocols.pbcast.NAKACK;
import org.jgroups.protocols.pbcast.STABLE;
import org.jgroups.protocols.pbcast.STATE_TRANSFER;
import org.jgroups.stack.Protocol;
import org.jgroups.stack.ProtocolStack;

import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatAction;
import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatMessage;

public class Chat {
	private static final int GETTING_STATE_TIMEOUT = 10000;
	private static final String CHAT_MANAGEMENT_CHANNEL_NAME = "ChatManagement768264";
	private static Scanner scanner = new Scanner(System.in);
	private String userName;
	private ChatManager chatManager;
	private ChatReceiver receiver;
	private Map<String, JChannel> connectedChannels = new HashMap<String, JChannel>();
	private Map<String, List<ChatAction>> state = new HashMap<String, List<ChatAction>>();
	
	public Chat(String userName) {
		this.userName = userName;
	}
	
	public static void main(String[] args) {
		System.out.println("Podaj swój nick:");
		String userName = scanner.nextLine();
		while(userName.length() > 20) {
			System.out.println("Zbyt długi nick. Maksymalna długość to 20. Spróbuj ponownie:");
			userName = scanner.next();
		}
		
		Chat chat = new Chat(userName);
		
		try {
			chat.initManagementChannelAndReceiver();
			while(true) {
				System.out.println("Wybierz operację:\n1 - dołącz do kanału\n" +
						"2 - wyświetl kanały\n3 - wyślij wiadomość\n[inne] - wyjście");
				
				int choosenOperation = scanner.nextInt();
				scanner.nextLine();
				switch(choosenOperation) {
					case 1:
						chat.joinChannel();
						break;
					case 2:
						chat.showChannels();
						break;
					case 3:
						chat.sendMessage();
						break;
					default:
						throw new Exception();
				}
			}
		} catch (Exception e) {
			System.out.println("Kończenie działania...");
			chat.cleanUp();
		}
	}

	private void initManagementChannelAndReceiver() throws Exception {
		receiver = new ChatReceiver();
		JChannel managerChannel = buildChannel(CHAT_MANAGEMENT_CHANNEL_NAME, null, new ManagementReceiver(this));
		managerChannel.getState(null, GETTING_STATE_TIMEOUT);
		chatManager = new ChatManager(managerChannel);
	}

	private void joinChannel() {
		try {
			System.out.println("Podaj nazwę kanału:");
			String channelName = scanner.nextLine();
			
			if(connectedChannels.containsKey(channelName)) {
				System.out.println("Już podłączony do tego kanału!");
				return;
			}
			JChannel channel = buildChannel(channelName, channelName, receiver);
			connectedChannels.put(channelName, channel);
			chatManager.sendInfoAboutJoin(userName, channelName);
		} catch (Exception e) {
			Logger.getLogger(getClass().getName())
				.severe("Nie udało się połączyć: " + e.getMessage());
		}
	}

	private JChannel buildChannel(String channelName, String hostName, ReceiverAdapter receiver) throws Exception {
		JChannel channel = new JChannel(false);
		channel.setName(userName);
		channel.setReceiver(receiver);
		ProtocolStack stack = createProtocolStack(hostName);		
		channel.setProtocolStack(stack);
		stack.init();		
		channel.connect(channelName);
		return channel;
	}

	private ProtocolStack createProtocolStack(String hostName)
			throws UnknownHostException {
		ProtocolStack stack = new ProtocolStack();
		
		Protocol udpProtocol = new UDP();
		if(hostName != null) {
			udpProtocol = udpProtocol.setValue("mcast_group_addr", 
					InetAddress.getByName(hostName));
		}
		
		stack.addProtocol(udpProtocol)
				.addProtocol(new PING())
				.addProtocol(new MERGE2())
				.addProtocol(new FD_SOCK())
				.addProtocol(new FD_ALL()
							.setValue("timeout", 12000)
							.setValue("interval", 3000))
				.addProtocol(new VERIFY_SUSPECT())
				.addProtocol(new BARRIER())
				.addProtocol(new NAKACK())
				.addProtocol(new UNICAST2())
				.addProtocol(new STABLE())
				.addProtocol(new GMS())
				.addProtocol(new UFC())
				.addProtocol(new MFC())
				.addProtocol(new FRAG2())
				.addProtocol(new STATE_TRANSFER())
				.addProtocol(new FLUSH());
		return stack;
	}

	private void showChannels() {
		synchronized(state) {
			for(Map.Entry<String, List<ChatAction>> actionsEntry : state.entrySet()) {
				System.out.println("Kanał: " + actionsEntry.getKey());
				for(ChatAction action : actionsEntry.getValue()) {
					System.out.println("\t" + action.getNickname());
				}
			}
		}
		System.out.println();
	}

	private void sendMessage() {
		System.out.println("Podaj nazwę kanału:");
		String channelName = scanner.nextLine();
		if(channelName.isEmpty() || !connectedChannels.containsKey(channelName)) {
			System.out.println("Nieznany kanał");
			return;
		}

		System.out.println("Podaj wiadomość:");
		String msgContent = scanner.nextLine();
		while(msgContent.isEmpty()) {
			System.out.println("Nie można wysłać pustej wiadomości!");
			msgContent = scanner.nextLine();
		}
		Message message = new Message(null, null, 
				ChatMessage.newBuilder().setMessage(msgContent).build().toByteArray());
		try {
			connectedChannels.get(channelName).send(message);
		} catch (Exception e) {
			Logger.getLogger(getClass().getName())
				.severe("Nie udało się wysłać wiadomości: " + e.getMessage());
		}
	}

	private void cleanUp() {
		for(Map.Entry<String, JChannel> channel : connectedChannels.entrySet()) {
			try {
				chatManager.sendInfoAboutLeave(userName, channel.getKey());
				channel.getValue().close();
			} catch(Exception e) {
				Logger.getLogger(getClass().getName())
					.severe("Nie udało się zamknąć połączenia " + channel.getKey() + ": " + e.getMessage());
			}
		}
		try {
			chatManager.cleanUp();
		} catch(Exception e) {
			Logger.getLogger(getClass().getName())
				.severe("Nie udało się zamknąć połączenia chat managera: " + e.getMessage());
		}
	}

	public Map<String, List<ChatAction>> getState() {
		return state;
	}

	public void pushState(Map<String, List<ChatAction>> state) {
		synchronized(this.state) {
			for(Map.Entry<String, List<ChatAction>> entry : state.entrySet()) {
				if(this.state.containsKey(entry.getKey())) {
					this.state.get(entry.getKey()).addAll(entry.getValue());
				} else {
					this.state.put(entry.getKey(), entry.getValue());
				}
			}
		}
	}

}
