package pl.edu.agh.student.aorzel.server.mybank.multiservant;

import pl.edu.agh.student.aorzel.server.mybank.AccountManagerI;

public class Server extends Thread {

	private Ice.Communicator ic = null;
	private String[] args;

	public Server(String[] args) {
		this.args = args;
	}

	@Override
	public void run() {
		try {
			ic = Ice.Util.initialize(args);

			Ice.ObjectAdapter adapter = ic.createObjectAdapter("MyBankMulti");			
			adapter.add(new AccountManagerI("multiservant"), ic.stringToIdentity("MyBankMulti"));
			
			adapter.addServantLocator(new MyServantEvictor(10), "Accounts");
			adapter.activate();
			ic.waitForShutdown();
		} finally {
			if(ic != null) {
				ic.destroy();
			}
		}		
	}

	public Ice.Communicator getIc() {
		return ic;
	}

}
