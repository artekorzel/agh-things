import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;


public class CAT {
	private static final int BUF = 2048;
	
	public static void wypisz(String [] args){
		FileInputStream plik = null;
		byte [] buf = new byte [BUF];
		for(String i:args) {
			try {
				plik = new FileInputStream(i);
				
				int licz;			
				while((licz = plik.read(buf,0,BUF)) != -1) {
					System.out.write(buf, 0, licz);
				}
				System.out.println();
			} catch(IOException e) {
				System.err.println("Blad strumienia");
			} finally {
				if(plik != null){
					try {
						plik.close();
					} catch(IOException e) {
						System.err.println("Blad zamykania strumienia");
						plik = null;
					}
				}
			}
		}		
	}
	
	public static void polacz(String [] args, int l) {		
			FileInputStream plik = null;
			FileOutputStream plik2 = null;
			
		try {
			plik2 = new FileOutputStream(args[l+1]);
			
			byte [] buf = new byte [BUF];
			for(int i = 0; i < l; ++i) {
				try {
					plik = new FileInputStream(args[i]);
					
					int licz;			
					while((licz = plik.read(buf,0,BUF)) != -1) {
						plik2.write(buf, 0, licz);
					}
				} catch(IOException e) {
					System.err.println("Blad strumienia");
				} finally {
					if(plik != null){
						try {
							plik.close();
						} catch(IOException e) {
							System.err.println("Blad zamykania strumienia");
							plik = null;
						}
					}
				}
			}
		} catch(IOException e) {
				System.err.println("Blad strumienia");
		} finally {
			if(plik2 != null){
				try {
					plik2.close();
				} catch(IOException e) {
					System.err.println("Blad zamykania strumienia");
					plik2 = null;
				}
			}
		}		
	}
	
	public static void main(String [] args){
		if(args.length > 0) {
			if(args.length > 1 && args[args.length - 2].equals(">")) {
				polacz(args, args.length - 2);
				String [] s = new String [1];
				s[0] = args[args.length - 1];
				wypisz(s);
			} else {
				wypisz(args);
			}
		} else {
			System.out.println("brak argumentow");
		}
	}
}
