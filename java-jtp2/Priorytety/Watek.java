
public class Watek extends Thread {
	private int priorytet;
	private int obecnyPriorytet;
	private int numer;
	private Obiekt obiekt;
	
	public Watek(int pr, int nr, Obiekt o) {
		priorytet = pr;
		obecnyPriorytet = pr;
		numer = nr;
		obiekt = o;
	}
	
	public int getNumer() {
		return numer;
	}
	
	public void run() {
		if(priorytet > 100)
			return;
		while(obecnyPriorytet > 0) {
			obiekt.dodaj(this);							
			obiekt.czekaj(this);			
			obiekt.wypisz(this);			
			--obecnyPriorytet;			
			obiekt.zwolnij();		
		}
	}
	
	public static void main(String [] args) {
		Obiekt o = new Obiekt();
		new Watek(5, 1, o).start();
		new Watek(2, 2, o).start();
		new Watek(4, 3, o).start();
	}
}
