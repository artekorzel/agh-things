
public class ReadersWritersProblem {
	public static void main(String [] args) {
		Library l = new Library();
		new Writer(1, l).start();
		new Reader(1, l).start();
		new Reader(2, l).start();
		new Writer(2, l).start();
		new Writer(3, l).start();
		new Reader(3, l).start();
		new Reader(4, l).start();
		new Writer(4, l).start();
		new Reader(5, l).start();
		new Reader(6, l).start();
	}
}
