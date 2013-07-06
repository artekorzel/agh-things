package pl.edu.agh.student.aorzel.server.mybank.multiservant;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import pl.edu.agh.student.aorzel.server.mybank.AccountDetails;
import pl.edu.agh.student.aorzel.server.mybank.AccountI;
import pl.edu.agh.student.aorzel.server.mybank.AccountManagerI;

public class MyServantEvictor implements Ice.ServantLocator {

	private int size;
	private final List<String> accountIds = new LinkedList<String>();
	private final Map<String, AccountDetails> accounts;

	public MyServantEvictor(int size) {
		this.size = size;
		this.accounts = AccountManagerI.getAccounts();
	}

	@Override
	public Ice.Object locate(Ice.Current c,
			Ice.LocalObjectHolder cookie) {
	    synchronized(this) {
	    	if(accounts.containsKey(c.id.name)) {
	    		accountIds.remove(c.id.name);
	    		accountIds.add(0, c.id.name);
	    		AccountDetails accountDetails = accounts.get(c.id.name);
				AccountI servant = accountDetails.getAccountServant();
	    		if(servant == null) {
	    			System.out.println("Creating new servant");
	    			servant = new AccountI("multiservant");
	    			accountDetails.setAccountServant(servant);
	    		}
	    		cookie.value = accountDetails;
	    		return servant;
	    	}
	    }
	    
	    return null;
	}

	@Override
	public void finished(Ice.Current c, Ice.Object o,
			java.lang.Object cookie) {
		synchronized(this) {
			evictServants();	
		}
	}

	@Override
	public void deactivate(String category) {
		synchronized(this) {
			size = 0;
			evictServants();
		}
	}

	private void evictServants() {
		for(int i = size, n = accountIds.size(); i < n; ++i) {
			String name = accountIds.remove(i);
			accounts.remove(name);
		}
	}
}
