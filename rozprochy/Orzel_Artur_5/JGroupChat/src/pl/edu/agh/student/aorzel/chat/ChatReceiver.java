package pl.edu.agh.student.aorzel.chat;

import java.util.logging.Logger;

import org.jgroups.Message;
import org.jgroups.ReceiverAdapter;
import org.jgroups.View;

import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatMessage;

public class ChatReceiver extends ReceiverAdapter {

	@Override
	public void viewAccepted(View newView) {
		//nothing to do here
	}

	@Override
	public void receive(Message msg) {
		try {
			ChatMessage parsedMessage = ChatMessage.parseFrom(msg.getRawBuffer());
			System.out.println(msg.getSrc() + ": " + parsedMessage.getMessage());
		} catch (Exception e) {
			Logger.getLogger(getClass().getName()).warning("Nie można sparsować wiadomości: " + e.getMessage());
		}
	}
}
