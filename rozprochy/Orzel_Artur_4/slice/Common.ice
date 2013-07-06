#ifndef __COMMON_ICE__
#define __COMMON_ICE__

module Common {
	exception UnknownCredentials {};
	exception UserAlreadyExists {};
	
	struct Session {
		string sessionId;
		string secureKey;
	};
};

#endif