package pl.edu.agh.student.aorzel.server.mycommunicator;

import MyCommunicator.UserCallbackPrx;

public class UserInformations {
	private String userName;
	private String password;
	private String sessionId;
	private String secureKey;
	private UserCallbackPrx callback;
	
	public UserInformations(String userName, String password) {
		this.userName = userName;
		this.password = password;
	}
	
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public UserCallbackPrx getCallback() {
		return callback;
	}
	public void setCallback(UserCallbackPrx callback) {
		this.callback = callback;
	}
	public String getSecureKey() {
		return secureKey;
	}
	public void setSecureKey(String secureKey) {
		this.secureKey = secureKey;
	}
	public String getSessionId() {
		return sessionId;
	}
	public void setSessionId(String sessionId) {
		this.sessionId = sessionId;
	}

}
