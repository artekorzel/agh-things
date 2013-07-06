
public class Writer extends Thread {
	private int nr;
	private Library l;
	public String s;
	
	public Writer(int i, Library _l) {
		nr = i;
		l = _l;
		s = "Pisarz " + String.valueOf(nr) + " zapisuje do pliku.\n";
	}
	
	public String toString() {
		return String.valueOf(nr);
	}
	
	public void run() {
		l.write(this);
		System.out.println("Pisarz " + nr + " zapisal");
	}
}
