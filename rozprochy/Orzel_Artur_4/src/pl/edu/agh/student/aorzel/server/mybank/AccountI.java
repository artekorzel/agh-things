package pl.edu.agh.student.aorzel.server.mybank;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import Common.Session;
import Common.UnknownCredentials;
import Ice.Current;
import MyBank.BalanceToLow;
import MyBank.OperationNotAllowed;
import MyBank._AccountDisp;

public class AccountI extends _AccountDisp {
	private static final long serialVersionUID = -1606371069471446561L;
	private static final Map<String, AccountDetails> loggedIn = new ConcurrentHashMap<String, AccountDetails>(); 
	private String bankType;

	public AccountI(String bankType) {
		this.bankType = bankType;
	}

	@Override
	public Session logIn(String personId, String password, Current __current)
			throws UnknownCredentials {
		AccountDetails details = AccountManagerI.verifyAuthority(personId, password, bankType);
		loggedIn.put(details.getSessionId(), details);
		return new Session(details.getSessionId(), details.getSecureKey());
	}

	@Override
	public double getBalance(Session credentials, Current __current) throws UnknownCredentials {
		verifyAuthority(credentials);
		return loggedIn.get(credentials.sessionId).getBalance();
	}

	@Override
	public void withdrawFromAccount(Session credentials, double amount,
			Current __current) throws BalanceToLow, UnknownCredentials, OperationNotAllowed {
		double balance = getBalance(credentials, __current);
		if(amount <= 0.0) {
			throw new OperationNotAllowed();
		}
		
		if(balance < amount) {
			throw new BalanceToLow();
		}
		
		AccountDetails details = loggedIn.get(credentials.sessionId);
		details.setBalance(balance - amount);
		writeNewBalance(bankType, details.getPersonId(), details.getPassword(), balance - amount);
	}

	@Override
	public void putOnAccount(Session credentials, double amount,
			Current __current) throws UnknownCredentials, OperationNotAllowed {
		double balance = getBalance(credentials, __current);
		if(amount <= 0.0) {
			throw new OperationNotAllowed();
		}
		
		AccountDetails details = loggedIn.get(credentials.sessionId);
		details.setBalance(balance + amount);
		writeNewBalance(bankType, details.getPersonId(), details.getPassword(), balance + amount);
	}

	public static void writeNewBalance(String bankType, String personId, String password, double balance){
		PrintWriter writer = null;
		try {
			writer = new PrintWriter(AccountManagerI.ACCOUNTS_PREFIX + bankType + "/" + personId);
			writer.printf("%.2f:%s:%s\n", balance, password, personId);
		} catch (IOException e) {
			System.err.println("Cannot write to file!");
		} finally {
			if(writer != null) {
				writer.close();
			}
		}
	}

	private void verifyAuthority(Session credentials) throws UnknownCredentials {
		if(!loggedIn.containsKey(credentials.sessionId)
				|| !loggedIn.get(credentials.sessionId).getSecureKey().equals(credentials.secureKey)) {
			throw new UnknownCredentials();
		}
	}

	@Override
	public void logOut(Session credentials, Current __current)
			throws UnknownCredentials {
		verifyAuthority(credentials);
		loggedIn.remove(credentials.sessionId);
		
	}

}
