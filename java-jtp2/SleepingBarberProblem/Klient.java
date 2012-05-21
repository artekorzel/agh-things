public class Klient extends Thread {
		private int nr;
		private Golibroda g;
		
		public Klient(int i, Golibroda _g) {
			nr = i;
			g = _g;
		}
		
		public String toString() {
			return String.valueOf(nr);
		}
		
		public void run() {
			System.out.println("Klient: " + this + " prosi o golenie");
			g.dodajDoKolejki(this);
			try {
				sleep(500);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}