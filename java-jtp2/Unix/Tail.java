import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Timer;
import java.util.TimerTask;

public class Tail {
	private String nazwaPliku;
	private Timer t;
	private RandomAccessFile raf;
	private long rozmiarPliku = 0;
	private long wskaznikWPliku = 0;
	
	
	public Tail() {}
	
	public Tail(String n) {
		ustawNazwePliku(n);
	}
	
	public void ustawNazwePliku(String n) {
		nazwaPliku = (n != null ? n : "");
	}
	
	public void sprawdzaj() {
		t = new Timer();
		t.schedule(new Sprawdzacz(), 0, 15);
		Runtime.getRuntime().addShutdownHook(new Thread() {
			public void run() {
				t.cancel();
				System.out.println("koniec podgladania");
			}
		} );
	}
	
	private class Sprawdzacz extends TimerTask {
		public void run() {
			try {
				raf = new RandomAccessFile(nazwaPliku, "r");
				long obecnyRozmiarPliku = raf.length();
				if(obecnyRozmiarPliku == rozmiarPliku) {
					return;
				} else  if(obecnyRozmiarPliku < rozmiarPliku){
					System.out.println("Plik zosta³ obciêty!!");
					rozmiarPliku = raf.length();
					wskaznikWPliku = rozmiarPliku - 1;
				} else {
					raf.seek(wskaznikWPliku);
					
					String linia;
					while((linia = raf.readLine()) != null) {
						System.out.println(linia);
					}
					
					rozmiarPliku = raf.length();
					wskaznikWPliku = raf.getFilePointer();
				}			
			} catch(IOException e) {
				System.err.println("Blad czytania pliku");
			} finally {
				if(raf != null) {
					try {
						raf.close();
					} catch (IOException e) {
						System.err.println("Nie mozna zamknac pliku");
						raf = null;
					}
				}
			}
		}
	}
	
	public static void main(String [] args) {
		if(args.length == 1) {
			Tail f = new Tail(args[0]);
			f.sprawdzaj();
		} else {
			System.out.println("Zle argumenty");
		}
	}
}
