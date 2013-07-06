package pl.edu.agh.student.aorzel.chat;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

import org.jgroups.Address;
import org.jgroups.Message;
import org.jgroups.ReceiverAdapter;
import org.jgroups.View;

import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatAction;
import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatAction.ActionType;
import pl.edu.agh.dsrg.sr.chat.protos.ChatOperationProtos.ChatState;

public class ManagementReceiver extends ReceiverAdapter {

	private Chat chat;

	public ManagementReceiver(Chat chat) {
		this.chat = chat;
	}

	@Override
	public void viewAccepted(View newView) {
		List<Address> membersAddresses = newView.getMembers();
		List<String> members = new ArrayList<String>();
		for(Address memberAddress : membersAddresses) {
			members.add(memberAddress.toString());
		}
		
		Map<String, List<ChatAction>> stateMap = chat.getState();
		synchronized(stateMap) {
			for(List<ChatAction> channelActions : stateMap.values()) {
				List<ChatAction> toRemove = new ArrayList<ChatAction>();
				
				for(ChatAction action : channelActions) {
					if(!members.contains(action.getNickname())) {
						toRemove.add(action);
					}
				}
				
				channelActions.removeAll(toRemove);
			}
		}
	}

	@Override
	public void receive(Message msg) {
		try {
			ChatAction parsedAction = ChatAction.parseFrom(msg.getRawBuffer());
			Map<String, List<ChatAction>> stateMap = chat.getState();
			synchronized(stateMap) {
				if(parsedAction.getAction() == ActionType.JOIN) {
					if(stateMap.containsKey(parsedAction.getChannel())) {
						stateMap.get(parsedAction.getChannel()).add(parsedAction);
					} else {
						List<ChatAction> actions = new ArrayList<ChatAction>();
						actions.add(parsedAction);
						stateMap.put(parsedAction.getChannel(), actions);
					}
				} else {
					for(List<ChatAction> channelActions : stateMap.values()) {
						List<ChatAction> toRemove = new ArrayList<ChatAction>();
						
						for(ChatAction action : channelActions) {
							if(action.getNickname().equals(parsedAction.getNickname()) 
									&& action.getChannel().equals(parsedAction.getChannel())) {
								toRemove.add(action);
							}
						}
						
						channelActions.removeAll(toRemove);
					}
				}
			}
		} catch (Exception e) {
			Logger.getLogger(getClass().getName()).warning("Nie można sparsować akcji: " + e.getMessage());
		}
	}
	
	@Override
	public void getState(OutputStream output) throws Exception {
		Map<String, List<ChatAction>> stateMap = chat.getState();
		synchronized(stateMap) {
			ChatState.Builder builder = ChatState.newBuilder();
			for(List<ChatAction> actions : stateMap.values()) {
				builder.addAllState(actions);
			}
		    output.write(builder.build().toByteArray());
		}
	}
	
	@Override
	public void setState(InputStream input) throws Exception {
		super.setState(input);
		List<ChatAction> state = ChatState.parseFrom(input).getStateList();
		Map<String, List<ChatAction>> stateMap = new HashMap<String, List<ChatAction>>();
		for(ChatAction action : state) {
			String channelName = action.getChannel();
			if(stateMap.containsKey(channelName)) {
				List<ChatAction> actions = stateMap.get(channelName);
				actions.add(action);
			} else {
				List<ChatAction> actions = new ArrayList<ChatAction>();
				actions.add(action);
				stateMap.put(channelName, actions);
			}
		}
		chat.pushState(stateMap);
	}
}
