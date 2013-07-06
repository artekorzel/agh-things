#ifndef __MY_COMMUNICATOR_ICE__
#define __MY_COMMUNICATOR_ICE__

#include"Common.ice"

module MyCommunicator {	
	struct Message {
		long time;
		string userName;
		string content;
	};
	
	sequence<Message> RoomHistory;
	
	interface UserCallback {
		void sendNewMessage(Message msg);	
	};

	interface Room {
		Common::Session logIn(string userName, string password, UserCallback* callback) throws Common::UnknownCredentials;
		RoomHistory getRoomHistory(Common::Session credentials) throws Common::UnknownCredentials;	
		void sendMessage(Common::Session credentials, Message msg) throws Common::UnknownCredentials;
		void logOut(Common::Session credentials) throws Common::UnknownCredentials;
	};
		
	interface ChatManager {
		void register(string userName, string password) throws Common::UserAlreadyExists;
		void hello();
	};
};

#endif