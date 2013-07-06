import java.util.LinkedList;

public class Obiekt {
	private LinkedList<Watek> q = new LinkedList<Watek>();
	
	public synchronized void wypisz(Watek p) {
		q.remove();
		System.out.println("Watek " + p.getNumer() + " otrzymal dostep do obiektu");
	}
	
	public synchronized void dodaj(Watek p) {
		q.add(p);
	}
	
	public synchronized void czekaj(Watek p) {
		while(p != q.element()) {
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public synchronized void zwolnij() {
		notifyAll();
	}
}
