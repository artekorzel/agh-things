public class Rekord {
	private int liczba;
	private String zdanie;
	public Rekord next;
	public Rekord prev;
	
	
	public Rekord() {
		liczba = 0;
		zdanie = " ";
		next = null;
		prev = null;
	}
	
	public Rekord(int i, String s) {
		liczba = i;
		zdanie = new String(s);
	}
	
	public Rekord(int i, String s, Rekord r, Rekord p) {
		this(i, s);
		next = r;
		prev = p;
	}
	
	public Rekord(Rekord r) {
		this(r.liczba, r.zdanie, r.next, r.prev);
	}
	
	public String toString() {
		StringBuffer wyn = new StringBuffer();
		wyn.append("[");
		wyn.append(liczba);
		wyn.append(", ");
		wyn.append(zdanie);
		wyn.append("]");
		return wyn.toString();
	}
}
