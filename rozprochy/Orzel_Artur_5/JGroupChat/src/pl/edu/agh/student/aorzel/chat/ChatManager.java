package pl.edu.agh.student.aorzel.chat;

import java.util.logging.Logger;

import org.jgroups.JChannel;
import org.jgroups.Message;

import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatAction;
import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatAction.ActionType;

public class ChatManager {
	
	private JChannel chatManagementChannel;
	
	public ChatManager(JChannel chatManagementChannel) {
		this.chatManagementChannel = chatManagementChannel;
	}

	public void cleanUp() {
		if(chatManagementChannel != null) {
			chatManagementChannel.close();
		}
	}
	
	public void sendInfoAboutJoin(String userName, String channelName) {
		sendInfo(userName, channelName, ActionType.JOIN);
	}
	
	public void sendInfoAboutLeave(String userName, String channelName) {
		sendInfo(userName, channelName, ActionType.LEAVE);
	}
	
	public void sendInfo(String userName, String channelName, ActionType actionType) {
		ChatAction.Builder builder = ChatAction.newBuilder();
		ChatAction action = builder.setNickname(userName).setChannel(channelName).setAction(actionType).build();
		Message message = new Message(null, null, action.toByteArray());
		try {
			chatManagementChannel.send(message);
		} catch (Exception e) {
			Logger.getLogger(getClass().getName()).severe("Nie udało się wysłać wiadomości: " + e.getMessage());
		}
	}
}