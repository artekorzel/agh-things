/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.ResourceBundle;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import javax.swing.JLabel;

/**
 * Klasa przechowująca najlepsze wyniki oraz pozwalająca sprawdzić i zaktualizować te wyniki. Wyniki są przechowywane w pliku
 * Wyniki.properties.
 * 
 * @author Artur Orzeł
 *
 */

public class PlikWynikowy extends Properties {
	private static final long serialVersionUID = 1L;
	private static final int liczbaWynikow = 10;
	private static final int JEDYNKA = 1;
	private static Logger logger = Logger.getLogger("PlikWynikowy");
	private ResourceBundle konfiguracja;
	private File plik = new File("Wyniki.properties");
	
	/**
	 * Konstruktor tworzący obiekt z podanej konfiguracji. Wczytuje (ewentualnie tworzy) plik wynikowy.
	 * 
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * 
	 */
	
	public PlikWynikowy(ResourceBundle _konfiguracja) {
		konfiguracja = _konfiguracja;	
		
		if(plik.canRead()) {
			FileInputStream fis = null;
			try {
				fis = new FileInputStream(plik);					
			} catch (FileNotFoundException e) {
				logger.log(Level.WARN, "Nieudane otwieranie istniejacego pliku z wynikami", e);
			}
			try {
				load(fis);
			} catch (IOException e) {
				logger.log(Level.WARN, "Nieudane ładowanie informacji z istniejacego pliku z wynikami", e);
			} finally {
				if(fis != null) {
					try {
						fis.close();
					} catch (IOException e) {
						logger.log(Level.WARN, "Nieudane zamykanie istniejacego pliku z wynikami", e);
						fis = null;
					}
				}
			}
		} else {
			for(int i = JEDYNKA; i <= liczbaWynikow; ++i) {
				setProperty("wynikNazwa" + String.valueOf(i), konfiguracja.getString("gracz") + " " + String.valueOf(i)); 
				setProperty("wynik" + String.valueOf(i), String.valueOf(i*10 + 100)); 
			}
			
			try {
				plik.createNewFile();
			} catch (IOException e) {
				logger.log(Level.WARN, "Nieudane tworzenie pliku z wynikami", e);
			}
			
			zapiszDoPliku();
		}		
	}
	
	private void zapiszDoPliku() {
		FileOutputStream fos = null;
		try {
			fos = new FileOutputStream(plik);					
		} catch (FileNotFoundException e) {
			logger.log(Level.WARN, "Nieudane otwieranie istniejacego pliku z wynikami", e);
		}
			
		try {
			store(fos, "");
		} catch (IOException e) {
			logger.log(Level.WARN, "Nieudane skladowanie w istniejacym pliku z wynikami", e);
		} finally {
			if(fos != null) {
				try {
					fos.close();
				} catch (IOException e) {
					logger.log(Level.WARN, "Nieudane zamykanie istniejacego pliku z wynikami", e);
					fos = null;
				}
			}
		}
	}
	
	/**
	 * Metoda spawdzająca czy otrzymany wynik jest jednym z najlepszych i, jeśli tak, wpisująca go na odpowiedniej pozycji na liście.
	 * Po zaktualizowaniu wpisów wyświetla wyniki poprzez stworzenie obiektu NajlepszeWyniki.
	 * 
	 * @param wynik
	 * 
	 */
	
	public void sprawdzIDodajWynik(JLabel wynik) {
		int wynikInt = Integer.parseInt(wynik.getText());
		int najnizszy = Integer.parseInt(getProperty("wynik" + String.valueOf(liczbaWynikow)));
		
		if(wynikInt < najnizszy) {
			PodajNazwe podajNazwe = new PodajNazwe(konfiguracja);
			podajNazwe.setVisible(true);
			
			int i = liczbaWynikow-JEDYNKA;
			while(i > 0 && wynikInt < (najnizszy = Integer.parseInt(getProperty("wynik" + String.valueOf(i))))) {
				setProperty("wynik" + String.valueOf(i+JEDYNKA), String.valueOf(najnizszy));
				setProperty("wynikNazwa" + String.valueOf(i+JEDYNKA), getProperty("wynikNazwa" + String.valueOf(i)));
				i--;
			}
			i++;
				
			setProperty("wynik" + String.valueOf(i), String.valueOf(wynikInt));
			setProperty("wynikNazwa" + String.valueOf(i), podajNazwe.getNazwa());
			
			zapiszDoPliku();
			
			new NajlepszeWyniki(konfiguracja, this).setVisible(true);
		}
	}
}
