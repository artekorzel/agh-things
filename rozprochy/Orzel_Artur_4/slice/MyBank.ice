#ifndef __MY_BANK_ICE__
#define __MY_BANK_ICE__

#include"Common.ice"

module MyBank {
	exception BalanceToLow {};
	exception OperationNotAllowed {};
	
	interface Account {
		Common::Session logIn(string personId, string password) throws Common::UnknownCredentials;
		double getBalance(Common::Session credentials) throws Common::UnknownCredentials;
		void withdrawFromAccount(Common::Session credentials, double amount) throws BalanceToLow, Common::UnknownCredentials, OperationNotAllowed; 
		void putOnAccount(Common::Session credentials, double amount) throws Common::UnknownCredentials, OperationNotAllowed;
		void logOut(Common::Session credentials) throws Common::UnknownCredentials;
	};

	interface AccountsManager {
		void register(string personId, string password) throws Common::UserAlreadyExists;
	};
};

#endif