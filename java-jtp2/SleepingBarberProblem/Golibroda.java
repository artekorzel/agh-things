import java.util.LinkedList;

public class Golibroda extends Thread {
		private int maxdlugosc = 10;
		private boolean spi = false;
		private LinkedList<Klient> kolejka = new LinkedList<Klient>();
		
		private boolean pelnaKolejka() {
			return kolejka.size() >= maxdlugosc;
		}
		
		public synchronized void dodajDoKolejki(Klient k) {
			if(pelnaKolejka()) {
				System.out.println("Nie można dodać do kolejki");
				return;
			}
			System.out.println("Dodano do kolejki: " + k);
			kolejka.add(k);
			if(spi) {
				notifyAll();
				System.out.println("Golibroda obudzony");
			}
			while(kolejka.contains(k)) {
				try {
					wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		
		public synchronized void wypuscDoDomu(Klient k) {
			kolejka.remove(k);
			notifyAll();
		}
		
		public synchronized Klient pobierzDoGolenia() {
			while(kolejka.isEmpty()) {
				try {
					System.out.println("Nie ma co robic - golibroda idzie spac");
					spi = true;
					wait();
					spi = false;
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			return kolejka.element();
		}
		
		public void golenie(Klient k) {
			System.out.println("Zaczynamy golenie klienta: " + k);
			try {
				sleep(500);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			System.out.println("Konczymy golenie klienta: " + k);
		}
		
		public void run() {
			while(true) {
				Klient k;
				if((k = pobierzDoGolenia()) == null) {
					continue;
				}
				golenie(k);
				wypuscDoDomu(k);
			}
		}	
	}