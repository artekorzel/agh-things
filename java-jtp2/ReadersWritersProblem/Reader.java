
public class Reader extends Thread {
	private int nr;
	private Library l;
	public String s = null;
	
	public Reader(int i, Library _l) {
		nr = i;
		l = _l;
	}
	
	public String toString() {
		return String.valueOf(nr);
	}
	
	public void run() {
		l.read(this);
		System.out.println("Czytelnik " + nr + " przeczytal");
	}
}
