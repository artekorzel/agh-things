package pl.edu.agh.student.aorzel.server.mybank.oneservant;

import pl.edu.agh.student.aorzel.server.mybank.AccountI;

public class MyServantLocator implements Ice.ServantLocator {
	
	private AccountI account = null;

	@Override
	public Ice.Object locate(Ice.Current c,
			Ice.LocalObjectHolder cookie) {
	    synchronized(this) {
	    	if(account == null) {
	    		System.out.println("Creating new servant");
	    		account = new AccountI("oneservant");
	    	}
	    }
	    return account;
	}

	@Override
	public void finished(Ice.Current c, Ice.Object o,
			java.lang.Object cookie) {
		System.out.println("Got account servant");
	}

	@Override
	public void deactivate(String category) {
		System.out.println("Shutting down...");
	}
}
