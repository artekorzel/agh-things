/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ResourceBundle;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import javax.imageio.ImageIO;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

/**
 * Panel z obrazem/obrazkiem.
 * 
 * Ta klasa, zależnie od potrzeb, pozwala stworzyć panel z obrazkiem (obiektem klasy BufferedImage)
 * bezpośrednio z pliku graficznego lub obiektu klasy BufferedImage oraz panel z obiektem klasy JLabel o podanej treści.
 * 
 * @author Artur Orzeł
 *
 */

public class Obraz extends JPanel {
	private static final long serialVersionUID = 1L;
	private static Logger logger = Logger.getLogger("Obraz");
	private ResourceBundle konfiguracja = null;
	private BufferedImage obrazek;
	private JLabel liczba;
	
	/** 
	 * Zwraca aktualnie przechowywany obrazek.
	 * 
	 * @return Aktualnie przechowywany obrazek - obiekt klasy BufferedImage.
	 * 
	 */
	
	public BufferedImage getObrazek() {
		return obrazek;
	}
	
	/** 
	 * Tworzy obiekt tej klasy z obrazkiem wczytanym z podanego pliku.
	 * W razie problemów z plikiem, zapisuje informację o błędzie do pliku log.
	 * 
	 * @param _obrazek Plik graficzny, na podstawie którego ma być wygenerowany panel z obrazkiem.
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * 
	 */
	
	public Obraz(File _obrazek, ResourceBundle _konfiguracja) {
		super();
		
		konfiguracja = _konfiguracja;
		try {
			obrazek = ImageIO.read(_obrazek);			
		} catch (IOException e) {
			logger.log(Level.WARN, "Wczytanie nieudane", e);
			JOptionPane.showMessageDialog(this, konfiguracja.getString("bladWczytywania"), konfiguracja.getString("blad"), 
																								JOptionPane.WARNING_MESSAGE);
		}
		
		setPreferredSize(new Dimension(obrazek.getWidth(), obrazek.getHeight()));		
	}
	
	/**
	 * Tworzy obiekt tej klasy na podstawie podanego obiektu klasy BufferedImage.
	 * 
	 * @param _obrazek obiekt klasy BufferedImage, który zostanie namalowany na panelu.
	 */
	
	public Obraz(BufferedImage _obrazek) {
		super();
		
		obrazek = _obrazek;
		setPreferredSize(new Dimension(obrazek.getWidth(), obrazek.getHeight()));
	}
	
	/**
	 * Tworzy panel z obiektem klasy JDialog o podanych wymiarach, zawierającym podany tekst (w zamierzeniu tekst zawierający liczbę).
	 * 
	 * @param tekst Podany String do umieszczenia w panelu.
	 * @param wymiary Obiekt klasy Dimension przechowujący wymiary powstającego panelu.
	 */
	
	public Obraz(String tekst, Dimension wymiary) {
		super();
		
		obrazek = null;
		liczba = new JLabel(tekst, SwingConstants.CENTER);
		liczba.setHorizontalAlignment(SwingConstants.CENTER);
		liczba.setFont(liczba.getFont().deriveFont(Font.BOLD, 40));
		add(liczba);
		setPreferredSize(wymiary);
	}
		
	/**
	 * Metoda wywoływana przy tworzeniu lub odświerzaniu okna programu.
	 * 
	 * @param g Obiekt typu Graphics.
	 * 
	 */
	public void paintComponent(Graphics g) {
		Graphics2D g2d = (Graphics2D) g;
		g2d.drawImage(obrazek, 0, 0, this);
	}
}
