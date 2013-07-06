package pl.edu.agh.student.aorzel.server.mybank;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;

import Common.UnknownCredentials;
import Common.UserAlreadyExists;
import Ice.Current;
import MyBank._AccountsManagerDisp;

public class AccountManagerI extends _AccountsManagerDisp {
	public static final String ACCOUNTS_PREFIX = "accounts/";
	private static final long serialVersionUID = 4685149648612800987L;
	private static final Map<String, AccountDetails> accounts = new ConcurrentHashMap<String, AccountDetails>();
	private String bankType;

	public AccountManagerI(String bankType) {
		this.bankType = bankType;
	}

	private static AccountDetails readPersonFile(File file) {
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(file));
			String line = reader.readLine();
			String[] details = line.split(":");
			System.out.println(Arrays.toString(details));
			double balance = Double.parseDouble(details[0].replace(",", "."));
			return new AccountDetails(details[2], details[1], balance);
		} catch (IOException e) {
			System.err.println("Cannot read file!");
		} catch (NumberFormatException e) {
			System.err.println("Incorrect balance!");
		} finally {
			if(reader != null) {
				try {
					reader.close();
				} catch (IOException e) {
					//nothing can be done
				}
			}
		}
		return null;
	}

	@Override
	public void register(String personId, String password,
			Current __current) throws UserAlreadyExists {
		if(accounts.containsKey(personId)) {
			throw new UserAlreadyExists();
		}
		
		AccountDetails details = new AccountDetails(personId, password, 0.0);
		File file = new File(ACCOUNTS_PREFIX + bankType + "/" + personId);
		if(file.exists()) {
			throw new UserAlreadyExists();
		} else {
			AccountI.writeNewBalance(bankType, personId, password, 0.0);
		}
		accounts.put(personId, details);
	}
	
	public static AccountDetails verifyAuthority(String personId, String password, String bankType) throws UnknownCredentials {
		if(accounts.containsKey(personId)) {
			AccountDetails details = accounts.get(personId);
			if(details.getPassword().equals(password)) {
				prepareCredentials(details);
				return details;
			}
		} else {
			File file = new File(ACCOUNTS_PREFIX + bankType + "/" + personId);
			AccountDetails readDetails = readPersonFile(file);
			if(readDetails != null) {
				accounts.put(personId, readDetails);
				prepareCredentials(readDetails);
				return readDetails;
			}
		}
		throw new UnknownCredentials();
	}
	
	private static void prepareCredentials(AccountDetails details) {
		details.setSessionId(details.getPersonId() + "." + System.currentTimeMillis());
		details.setSecureKey(String.valueOf(new Random().nextLong()));
	}

	public static Map<String, AccountDetails> getAccounts() {
		return accounts;
	}
}
