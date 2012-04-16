/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

/**
 * 
 * Ta klasa służy do tworzenia pliku Lang.properties z tłumaczeniem do gry Piętnastka.
 * 
 * @author Artur Orzeł
 *
 */

public class UstawieniaJezykowe extends Properties {
	private static final long serialVersionUID = 1L;
	
	private void generuj() {
		File f = new File("Lang.properties");
		try {
			f.createNewFile();
			FileOutputStream fos = new FileOutputStream(f);
			
			setProperty("ramka", "Piętnastka"); 
			setProperty("plikMenu", "Plik"); 
			setProperty("pomocMenu", "Pomoc"); 
			setProperty("graStandardowa", "Gra Standardowa"); 
			setProperty("wczytajObraz", "Wczytaj Obraz"); 
			setProperty("zakoncz", "Zakończ"); 
			setProperty("oPomocMenu", "O..."); 
			setProperty("zasadyGry", "Zasady Gry"); 
			setProperty("oInf", "Gra Piętnastka.\nAutor: Artur Orzeł\nUwagi proszę przesyłać na: aorzel@student.agh.edu.pl"); 
			setProperty("etykietaWyniku", "Twój Wynik"); 
			setProperty("odNowa", "Zacznij od nowa"); 
			setProperty("wygralesNaglowek", "Wygrałeś!"); 
			setProperty("zasadyTytul", "Zasady Gry Piętnastka");
			setProperty("wygralesOpis", "Gratulacje! Wygrałeś wynikiem: "); 
			setProperty("zasadyGraStdNagl", "Gra Standardowa:"); 
			setProperty("zasadyGraStd", "Przesuwając klocki sąsiadujące z pus-\ntym polem, ułóż wszystkie kolejno od 1\n   do 15, od lewej do prawej i od góry\n   do dołu, pozostawiając wolne pole\n            w prawym dolnym rogu."); 
			setProperty("wczytanieObrNagl", "Wczytanie Obrazka:"); 
			setProperty("wczytanieObr", "Wybierz obrazek w formacie JPG, a nas-\ntępnie przesuwając klocki sąsiadujące\n z pustym polem, ułóż obrazek zgodnie\n  ze wzorem po prawej, pozostawiając\n   puste pole w prawym dolnym rogu."); 
			setProperty("ok", "OK");
			setProperty("obrazJPG", "Obraz JPG");
			setProperty("bladWczytywania", "Nie udało się wczytać podanego obrazu - spróbuj ponownie lub wybierz inny obraz.");
			setProperty("blad", "Błąd!");
			setProperty("gracz", "Gracz");
			setProperty("najlepszeWyniki", "Najlepsze wyniki");
			setProperty("podajNazweTytul", "Podaj nazwę");
			setProperty("superWynik", "Super wynik!\n Podaj swoją nazwę:");
			setProperty("brakNazwy", "Nie podałeś swojej nazwy!");
			
			store(fos, "");
			fos.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}		
	}
	
	/**
	 * Metoda uruchamiana ze startem programu generująca plik Lang.properties.
	 * 
	 * @param args Parametry uruchomienia programu.
	 * 
	 */
	
	public static void main(String [] args) {
		new UstawieniaJezykowe().generuj();
	}
}
