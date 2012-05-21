import java.util.Properties;
import java.io.FileInputStream;
import java.io.File;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.lang.IllegalArgumentException;
import java.lang.Integer;
import java.util.logging.ErrorManager;

public class Singleton2 {
	private static Singleton2 _soleInstance [];
	private static int aktN = 0;
	private static int i = 0;
	
	private Singleton2() {}
	
	public static int getAktN() {
		return aktN;
	}
	
	public static int getI() {
		return i;
	}
		
	public static Singleton2 getInstance() {		
		if(_soleInstance == null) {
			Properties nowe = new Properties();
			FileInputStream ustawienia = null;
			
			try {
				ustawienia = new FileInputStream(new File("D:\\nowy.txt"));
			}
			catch(FileNotFoundException e) {
				ErrorManager blad = new ErrorManager();
				blad.error("Brak takiego pliku!!!", e, 1);
			}
			
			try {
			nowe.load(ustawienia);
			} 
			catch (IOException e) {
				ErrorManager blad = new ErrorManager();
				blad.error("Brak takiego pliku!!!", e, 1);
			}
			catch (IllegalArgumentException e) {
				ErrorManager blad = new ErrorManager();
				blad.error("Plik jest nieprawidlowy!!!", e, 2);
			}
			
			try {
				ustawienia.close();
			}
			catch(IOException e) {
				ErrorManager blad = new ErrorManager();
				blad.error("Brak takiego pliku!!!", e, 1);
			}
						
			int n = Integer.parseInt(nowe.getProperty("n"));
			
			_soleInstance = new Singleton2[n];
			aktN = n;
		}
		if(i >= aktN) {
			i = 0;
		}
		i++;
		return _soleInstance[i-1];
	}
}