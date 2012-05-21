public class SleepingBarberProblem {	
	public static void main(String [] args) {
		Golibroda g = new Golibroda();
		int liczbaKlientow = 10;
		Klient [] k = new Klient [liczbaKlientow];
		
		g.start();
		for(int i = 0; i < liczbaKlientow; ++i) {
			k[i] = new Klient(i, g);
			k[i].start();
		}
	}
}
