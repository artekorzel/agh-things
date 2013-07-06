import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Library {
	private File f = new File("plik");
	private Integer counter = 0;
	private Boolean czyPisarz = false;
	
	private void set(String s) {
		FileWriter fw = null;
		try {
			fw = new FileWriter(f, true);
			fw.write(s);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if(fw != null) {
				try {
					fw.close();
				} catch (IOException e) {
					e.printStackTrace();
					fw = null;
				}
			}
		}
	}
	
	private String get() {
		FileReader fr = null;
		char [] s = new char [100];
		try {
			fr = new FileReader(f);
			fr.read(s);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if(fr != null) {
				try {
					fr.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return new String(s);
	}
	
	public void read(Reader r) {		
		synchronized(this) {
			if(!czyPisarz) {
				++counter;
			} else while(czyPisarz) {
				try {
					wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		r.s = get();
		synchronized(this) {
			--counter;
			if(counter == 0) {
				notifyAll();
			}
		}
		
	}
	
	public void write(Writer w) {			
		synchronized(this) {
			czyPisarz = true;
			while(counter > 0) {
				try {
					wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		
		set(w.s);
		
		synchronized(this) {
			czyPisarz = false;
			notifyAll();
		}		
	}
}
