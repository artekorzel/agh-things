package pl.edu.agh.student.aorzel.server;

public class Server {

	public static void main(String[] args) {
		final pl.edu.agh.student.aorzel.server.mybank.oneservant.Server bankOneThread = 
				new pl.edu.agh.student.aorzel.server.mybank.oneservant.Server(args);
		final pl.edu.agh.student.aorzel.server.mybank.multiservant.Server bankMultiThread = 
				new pl.edu.agh.student.aorzel.server.mybank.multiservant.Server(args);
		final pl.edu.agh.student.aorzel.server.mycommunicator.Server communicatorThread = 
				new pl.edu.agh.student.aorzel.server.mycommunicator.Server(args);
		
		Runtime.getRuntime().addShutdownHook(new Thread() {
			@Override
			public void run() {
				bankOneThread.getIc().shutdown();
				bankMultiThread.getIc().shutdown();
				communicatorThread.getIc().shutdown();
			}
		});
		
		bankOneThread.start();
		bankMultiThread.start();
		communicatorThread.start();
		
		try {
			bankOneThread.join();
			bankMultiThread.join();
			communicatorThread.join();
		} catch (InterruptedException e) {
			System.err.println("Thread interrupted!");
		}
	}

}
