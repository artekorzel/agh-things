package pietnastka;

import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.util.Random;
import java.util.ResourceBundle;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * Ta klasa abstrakcyjna zawiera elementy konieczne do stworzenia panelu własciwej części gry, w szczególności układ 16 fragmentów - obiektów klasy 
 * Obraz, do ułożenia w odpowiedniej kolejności.
 * 
 * @author Artur Orzeł
 *
 */

public abstract class Podzielony extends JPanel {
	private static final long serialVersionUID = 1L;
	private PlikWynikowy plikWynikowy;
	private ResourceBundle konfiguracja;
	
	/**
	 * Stała typu int co do wartości równa jeden.  
	 * 
	 */
	
	protected static final int JEDYNKA = 1;
	
	/**
	 * Obiekt typu BufferedImage do ewentualnego podziału na fragmenty.
	 * 
	 */
	protected BufferedImage obrazek;
	
	/**
	 * Wysokość całego panelu zawierającego fragmenty (nie licząc odstępów między fragmentami).
	 * 
	 */
	protected int wysokoscObrazka;
	
	/**
	 * Szerokość całego panelu zawierającego fragmenty (nie licząc odstępów między fragmentami).
	 * 
	 */
	protected int szerokoscObrazka;
	
	/**
	 * Wysokość każdego z fragmentów - obiektów klasy Obraz.
	 * 
	 */
	protected int wysokoscFragmentu;
	
	/**
	 * Szerokość każdego z fragmentów - obiektów klasy Obraz.
	 *  
	 */
	protected int szerokoscFragmentu;
	
	/**
	 * Obiekt klasy JFrame, na którym pojawiają się wszystkie elementy gry - okno główne aplikacji.
	 * 
	 */
	protected JFrame ramka;
	
	/**
	 * Obiekt klasy JLabel wyświetlający aktualny wynik gry.
	 * 
	 */
	protected JLabel wynik;
	
	/**
	 * Tablica obiektów klasy Obraz zawierająca fragmenty w aktualnym momencie gry.
	 * 
	 */
	protected Obraz [][] tablicaFragmentow;
	
	/**
	 * Tablica obiektów klasy Obraz zawierająca fragmenty w początkowym momencie gry - stan docelowy.
	 * 
	 */
	protected Obraz [][] tablicaUlozonychFragmentow;
	
	/**
	 * Współrzędna pozioma (druga) w tablicy tablicaFragmentow pola pustego.
	 * 
	 */
	protected int wolnePoleX;
	
	/**
	 * Współrzędna pionowa (pierwsza) w tablicy tablicaFragmentow pola pustego.
	 * 
	 */
	protected int wolnePoleY;
	
	/**
	 * Stała opisująca liczbę fragmentów przypadających na jeden wymiar.
	 * 
	 */	
	protected final static int LICZBA = 4;

	/**
	 * Ten konstruktor wywoływany przy tworzeniu obiektów dziedziczących z tej klasy abstrakcyjnej tworzy podstawowe, niezależne od trybu gry elementy.
	 * W szczególności tworzy poprzez wywołanie metody stworzTabliceFragmentow układ elementów do ułożenia.
	 * Układ ten początkowo jest ułożony w nominalnej kolejności. Następnie element po prawej na dole jest zastąpiony elementem
	 * pustym, układ zostaje zapamiętany oraz pomieszany. Ponadto każdy taki fragment jest przygotowany do ewentualnej zamiany
	 * z elementem pustym (jest to wykonanie ruchu).
	 * 
	 * @param _obrazek Obraz typu BufferedImage do podziału (jeśli potrzebny, jeśli nie to null)
	 * @param _ramka Główny obiekt klasy JFrame aplikacji, na której wyświetlany jest ten panel
	 * @param _wynik Obiekt klasy JLabel zawierający aktualny wynik gry
	 * @param _plik Obiekt typu PlikWynikowy zawierający najlepsze wyniki.
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * 
	 */
	
	protected Podzielony(BufferedImage _obrazek, JFrame _ramka, JLabel _wynik, PlikWynikowy _plik, ResourceBundle _konfiguracja) {
		super(new GridLayout(LICZBA,LICZBA,JEDYNKA,JEDYNKA));
		
		obrazek = _obrazek;
		ramka = _ramka;
		wynik = _wynik;
		plikWynikowy = _plik;
		konfiguracja = _konfiguracja;
		
		tablicaFragmentow = new Obraz[LICZBA][LICZBA];
		
		stworzTabliceFragmentow();
		
		wolnePoleX = wolnePoleY = LICZBA - JEDYNKA;
		
		tablicaUlozonychFragmentow = new Obraz[LICZBA][LICZBA];
		for(int i = 0 ; i < LICZBA; ++i) { 
			for(int j = 0; j < LICZBA; ++j) { 
				tablicaUlozonychFragmentow[i][j] = tablicaFragmentow[i][j];
			}
		}
				
		pomieszaj();
	}
	
	/**
	 * Metoda abstrakcyjna implementowana w klasach dziedziczących, stwarzająca tablicę fragmentów zależnie od potrzeb.
	 * 
	 */
	
	abstract protected void stworzTabliceFragmentow();
	
	/**
	 * Metoda mieszająca nowo powstały układ fragmentów, przygotowuje układ do rozpoczęcia gry.
	 * 
	 */
	
	public void pomieszaj() {
		Random maszynaLosujaca = new Random();
		//kierunek: 0 - w lewo, 1 - w gore, 2 - w prawo, 3 - w dol
		MouseListener[] ml;
		int i = 50*LICZBA*LICZBA;
		while(i > 0) {
			switch(maszynaLosujaca.nextInt(LICZBA)) {
				case 0: {
					if(wolnePoleX > 0) {
						ml = tablicaFragmentow[wolnePoleY][wolnePoleX-JEDYNKA].getMouseListeners();
						((ReakcjaNaRuch) ml[0]).wykonajRuch();
						i--;
					}
					break;
				}
				case 1: {
					if(wolnePoleY > 0) {
						ml = tablicaFragmentow[wolnePoleY-JEDYNKA][wolnePoleX].getMouseListeners();
						((ReakcjaNaRuch) ml[0]).wykonajRuch();
						i--;
					}
					break;
				}
				case 2: {
					if(wolnePoleX < LICZBA-1) {
						ml = tablicaFragmentow[wolnePoleY][wolnePoleX+JEDYNKA].getMouseListeners();
						((ReakcjaNaRuch) ml[0]).wykonajRuch();
						i--;
					}
					break;
				}
				case 3: {
					if(wolnePoleY < LICZBA-1) {
						ml = tablicaFragmentow[wolnePoleY+JEDYNKA][wolnePoleX].getMouseListeners();
						((ReakcjaNaRuch) ml[0]).wykonajRuch();
						i--;
					}
					break;
				}
			}
		}
		ramka.pack();
	}	
	
	/**
	 * Klasa wewnętrzna opisująca reakcję fragmentu obrazu na kliknięcie na niego myszką.
	 * 
	 * @author Artur Orzeł
	 *
	 */
	
	public class ReakcjaNaRuch implements MouseListener {	
		private int x;
		private int y;
		
		/**
		 * Konstruuje obiekt zapamiętując aktualne współrzędne obiektu, na rzecz którego dany obiekt tej klasy zostaje
		 * tworzony.
		 * 
		 * @param _x Współrzędna pozioma względem lewego górnego rogu.
		 * @param _y Współrzędna pionowa względem lewego górnego rogu.
		 */
		
		public ReakcjaNaRuch(int _x, int _y) {
			x = _x;
			y = _y;
		}
		
		private void wykonajRuch() {
			int tmp1 = getComponentZOrder(tablicaFragmentow[y][x]);
			remove(tablicaFragmentow[y][x]);
			int tmp2 = getComponentZOrder(tablicaFragmentow[wolnePoleY][wolnePoleX]);
			remove(tablicaFragmentow[wolnePoleY][wolnePoleX]);
			add(tablicaFragmentow[y][x], tmp2);
			add(tablicaFragmentow[wolnePoleY][wolnePoleX], tmp1);
			
			Obraz tmp3 = tablicaFragmentow[y][x];
			tablicaFragmentow[y][x] = tablicaFragmentow[wolnePoleY][wolnePoleX];
			tablicaFragmentow[wolnePoleY][wolnePoleX] = tmp3;
			
			tmp1 = wolnePoleX;
			wolnePoleX = x;
			x = tmp1;
			
			tmp2 = wolnePoleY;
			wolnePoleY = y;
			y = tmp2;
		}
		
		/**
		 * Metoda wywoływana automatycznie po kliknięciu myszą na danym fragmencie.
		 * Jeśli kliknięty fragment znajduje się w sąsiedztwie elementu pustego, to zostaje wykonany ruch (zamiana 
		 * obiektu danego i pustego), aktualizacja wyniku oraz sprawdzenie czy gra się skończyła. Jeśli tak, to
		 * wyświetlony zostaje odpowiedni komunikat.
		 * 
		 * @param me Obiekt klasy MouseEvent.
		 * 
		 */
		
		public void mouseClicked(MouseEvent me) {
			if(((y == wolnePoleY) && (Math.abs(x-wolnePoleX) == JEDYNKA)) || 
											((x == wolnePoleX) && (Math.abs(y-wolnePoleY) == JEDYNKA))) {
				wykonajRuch();
				
				tablicaFragmentow[y][x].revalidate();
				tablicaFragmentow[wolnePoleY][wolnePoleX].revalidate();
				
				wynik.setText(String.valueOf(Integer.parseInt(wynik.getText()) + JEDYNKA));
				
				boolean czyRowne = true;
				for(int i = 0; i < LICZBA; ++i) {
					for(int j = 0; j < LICZBA; ++j) {
						if(tablicaUlozonychFragmentow[i][j] != tablicaFragmentow[i][j]) {
							czyRowne = false;
						}
					}
				}
			
				if(czyRowne) {
					JOptionPane.showMessageDialog(ramka, konfiguracja.getString("wygralesOpis") + wynik.getText(), 
											konfiguracja.getString("wygralesNaglowek"), JOptionPane.INFORMATION_MESSAGE);
					
					plikWynikowy.sprawdzIDodajWynik(wynik);
					
					wynik.setText("0");
					pomieszaj();
				}
			}
		}

		/**
		 * Metoda wywoływana automatycznie po naciśnięciu przycisku myszy na danym fragmencie.
		 * Nie robi nic.
		 * 
		 * @param me Obiekt klasy MouseEvent.
		 * 
		 */
		
		public void mousePressed(MouseEvent me) {}
		
		/**
		 * Metoda wywoływana automatycznie po puszczeniu przycisku myszy na danym fragmencie.
		 * Nie robi nic.
		 * 
		 * @param me Obiekt klasy MouseEvent.
		 * 
		 */
		
		public void mouseReleased(MouseEvent me) {}
		
		/**
		 * Metoda wywoływana automatycznie po wejściu do danego fragmencie.
		 * Nie robi nic.
		 * 
		 * @param me Obiekt klasy MouseEvent.
		 * 
		 */
		
		public void mouseEntered(MouseEvent me) {}
		
		/**
		 * Metoda wywoływana automatycznie po wyjściu z danego obiektu.
		 * Nie robi nic.
		 * 
		 * @param me Obiekt klasy MouseEvent.
		 * 
		 */
		
		public void mouseExited(MouseEvent me) {}
	}
}
