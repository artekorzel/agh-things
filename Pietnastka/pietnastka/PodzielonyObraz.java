/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.awt.image.BufferedImage;
import java.util.ResourceBundle;

import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 * Panel z fragmentami obrazu.
 * 
 * Ta klasa zawiera panel składający się z odpowiedniej ilości obiektów klasy Obraz (16 w ukladzie 4x4) powstałych poprzez podział pliku graficznego. 
 * 
 * @author Artur Orzeł
 *
 */

public class PodzielonyObraz extends Podzielony {
	private static final long serialVersionUID = 1L;
	
	/**
	 * Tworzy panel z 16 fragmentami wskazanego obrazu poprzez konstruktor klasy Podzielony i wywołanie w nim metody stworzTabliceFragmentow,
	 * a następnie miesza zawartość przygotowując do gry.
	 * 
	 * @param _obrazek Obiekt klasy BufferedImage do podziału
	 * @param _ramka Główny obiekt klasy JFrame aplikacji, na której wyświetlany jest ten panel
	 * @param _wynik Obiekt klasy JLabel zawierający aktualny wynik gry
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * @param _plik Obiekt typu PlikWynikowy zawierający najlepsze wyniki.
	 * 
	 */
	
	public PodzielonyObraz(BufferedImage _obrazek, JFrame _ramka, JLabel _wynik, ResourceBundle _konfiguracja, PlikWynikowy _plik) {
		super(_obrazek, _ramka, _wynik, _plik, _konfiguracja);	
	}
	
	/**
	 * Metoda wywoływana w konstruktorze. Ustawia wartości wymiarów obrazka i fragmentów oraz tworzy każdy fragment typu Obraz poprzez wywołanie
	 * odpowiedniego konstruktora. Następnie w miejsce ostatniego elementu wstawia fragment pusty.
	 * 
	 */
	
	protected void stworzTabliceFragmentow() {
		wysokoscObrazka = obrazek.getHeight();
		szerokoscObrazka = obrazek.getWidth();
		wysokoscFragmentu = wysokoscObrazka/LICZBA-JEDYNKA;
		szerokoscFragmentu = szerokoscObrazka/LICZBA-JEDYNKA;
		
		for(int i = 0; i < LICZBA; ++i) {
			for(int j = 0; j < LICZBA; ++j) {
				tablicaFragmentow[i][j] = new Obraz(obrazek.getSubimage(j*szerokoscFragmentu+JEDYNKA, i*wysokoscFragmentu+JEDYNKA,
																						szerokoscFragmentu, wysokoscFragmentu));
				tablicaFragmentow[i][j].addMouseListener(new ReakcjaNaRuch(j, i));
				add(tablicaFragmentow[i][j]);
			}
		}
		remove(tablicaFragmentow[LICZBA-JEDYNKA][LICZBA-JEDYNKA]);
		//Graphics g = tablicaFragmentow[LICZBA-JEDYNKA][LICZBA-JEDYNKA].getObrazek().createGraphics();
		//g.setColor(getBackground());
		//g.fillRect(0, 0, szerokoscFragmentu, wysokoscFragmentu);
		BufferedImage wolnePole = new BufferedImage(szerokoscFragmentu, wysokoscFragmentu, BufferedImage.TYPE_INT_ARGB);
		for(int i = 0; i < szerokoscFragmentu; ++i) {
			for(int j = 0; j < wysokoscFragmentu; ++j) {
				wolnePole.setRGB(i,j,0);
			}
		}
		tablicaFragmentow[LICZBA-JEDYNKA][LICZBA-JEDYNKA] = new Obraz(wolnePole);
		add(tablicaFragmentow[LICZBA-JEDYNKA][LICZBA-JEDYNKA]);
	}	
}

