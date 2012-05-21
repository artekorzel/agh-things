package pietnastka;

import java.awt.Dimension;
import java.util.ResourceBundle;

import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 * Ta klasa zawiera panel 16 obiektów klasy Obraz z kolejnymi liczbami wypisanymi w obiektach JLabel.
 * 
 * @author Artur Orzeł
 *
 */

public class Liczby extends Podzielony {
	private static final long serialVersionUID = 1L;
	private static final int WYMIAR = 320;
	
	/**
	 * Tworzy panel z 16 fragmentami typu JLabel zawierającymi liczby od 1 do 15 oraz fragment pusty poprzez konstruktor klasy 
	 * Podzielony, po czym miesza zawartość przygotowując do gry.
	 * 
	 * @param _ramka Główny obiekt klasy JFrame aplikacji, na której wyświetlany jest ten panel
	 * @param _wynik Obiekt klasy JLabel zawierający aktualny wynik gry
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * @param _plik Obiekt typu PlikWynikowy zawierający najlepsze wyniki.
	 * 
	 */
	
	public Liczby(JFrame _ramka, JLabel _wynik, ResourceBundle _konfiguracja, PlikWynikowy _plik) {
		super(null, _ramka, _wynik, _plik, _konfiguracja);
	}
	
	/**
	 * Metoda wywoływana w konstruktorze. Ustawia wartości wymiarów panelu głównego oraz paneli z liczbami, tworzy każdy fragment 
	 * typu Obraz poprzez wywołanie odpowiedniego konstruktora. Następnie w miejsce ostatniego elementu wstawia fragment pusty.
	 * 
	 */

	protected void stworzTabliceFragmentow() {
		wysokoscObrazka = WYMIAR;
		szerokoscObrazka = WYMIAR;
		wysokoscFragmentu = wysokoscObrazka/LICZBA-JEDYNKA;
		szerokoscFragmentu = szerokoscObrazka/LICZBA-JEDYNKA;
		
		for(int i = 0; i < LICZBA; ++i) {
			for(int j = 0; j < LICZBA; ++j) {
				tablicaFragmentow[i][j] = new Obraz(String.valueOf(i*LICZBA + j + JEDYNKA), new Dimension(szerokoscFragmentu, 
																											wysokoscFragmentu));
				tablicaFragmentow[i][j].addMouseListener(new ReakcjaNaRuch(j, i));
				add(tablicaFragmentow[i][j]);
			}
		}
		remove(tablicaFragmentow[LICZBA-JEDYNKA][LICZBA-JEDYNKA]);
		tablicaFragmentow[LICZBA-JEDYNKA][LICZBA-JEDYNKA] = new Obraz("", new Dimension(szerokoscFragmentu, wysokoscFragmentu));
		add(tablicaFragmentow[LICZBA-JEDYNKA][LICZBA-JEDYNKA]);
	}	
}
