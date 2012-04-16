/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.util.ResourceBundle;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 * Okno wyboru pliku z obrazem.
 * 
 * Ta klasa zawiera standardowy układ wczytujący plik z filtrem na pliki graficzne o rozszerzeniu JPG.
 * 
 * @author Artur Orzeł
 *
 */

public class WczytajObraz extends JPanel {
	private static final long serialVersionUID = 1L;
	private ResourceBundle konfiguracja;
	private JFileChooser wybieracz;
	
	/**
	 * Metoda ta zwraca aktualnie przechowywany obiekt wczytujący plik.
	 * 
	 * @return Obiekt typu JFileChooser zawierający okno wczytujące plik.
	 */
	
	public JFileChooser getWybieracz() {
		return wybieracz;
	}
	
	/**
	 * Ten konstruktor tworzy panel dodając obiekt typu JFileChooser z filtrem ograniczającym możliwość wczytywania plików
	 * tylko na te z rozszerzeniem JPG.
	 * 
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * 
	 */
	
	public WczytajObraz(ResourceBundle _konfiguracja) {
		konfiguracja = _konfiguracja;
		wybieracz = new JFileChooser();
		wybieracz.setFileFilter(new FileNameExtensionFilter(konfiguracja.getString("obrazJPG"), "JPG"));
		add(wybieracz);
	}
}
