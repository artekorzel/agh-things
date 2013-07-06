package pl.edu.agh.student.aorzel.server.mycommunicator;

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

			Ice.ObjectAdapter adapter = ic.createObjectAdapter("MyCommunicator");			
			adapter.add(new ChatManagerI(), ic.stringToIdentity("MyCommunicator"));			
			adapter.addServantLocator(new MyServantLocator(), "Rooms");
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
