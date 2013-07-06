package pl.edu.agh.student.aorzel.server.mybank;

public class AccountDetails {
	private String personId;
	private String password;
	private String sessionId;
	private String secureKey;
	private double balance;
	private AccountI accountServant;
	
	public AccountDetails(String personId, String password, double balance) {
		this.personId = personId;
		this.password = password;
		this.balance = balance;
	}
	
	public String getPersonId() {
		return personId;
	}
	
	public void setPersonId(String personId) {
		this.personId = personId;
	}
	
	public String getPassword() {
		return password;
	}
	
	public void setPassword(String password) {
		this.password = password;
	}

	public AccountI getAccountServant() {
		return accountServant;
	}

	public void setAccountServant(AccountI accountServant) {
		this.accountServant = accountServant;
	}

	public double getBalance() {
		return balance;
	}

	public void setBalance(double balance) {
		this.balance = balance;
	}

	public String getSessionId() {
		return sessionId;
	}

	public void setSessionId(String sessionId) {
		this.sessionId = sessionId;
	}

	public String getSecureKey() {
		return secureKey;
	}

	public void setSecureKey(String secureKey) {
		this.secureKey = secureKey;
	}
}
