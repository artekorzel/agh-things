/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextArea;

/**
 * Okno z zasadami gry.
 * 
 * Ta klasa zawiera okno z zasadami gry powiązane z obiektem typu JFrame bedącym głównym oknem gry.
 * 
 * @author Artur Orzeł
 *
 */

public class ZasadyGry extends JDialog {
	private static final long serialVersionUID = 1L;
	private static ResourceBundle konfiguracja;
	private static JLabel graStd;
	private static JTextArea graStandardowa;
	private static JLabel wczytanieObr;
	private static JTextArea wczytanieObrazka;
	private static JButton ok;
	
	/**
	 * Ten konstruktor tworzy obiekt, nadając mu tytuł, ustawiając operację zamknięcia oraz dodając nagłówki i zasady gry
	 * dla każdego z jej trybów. Ponadto dodaje przycisk zamykający to okno.
	 * 
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 *
	 */
	
	public ZasadyGry(ResourceBundle _konfiguracja) {
		konfiguracja = _konfiguracja;
		
		setTitle(konfiguracja.getString("zasadyTytul"));		
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setLayout(new FlowLayout(FlowLayout.CENTER, 10,10));
		
		graStd = new JLabel(konfiguracja.getString("zasadyGraStdNagl"));
		add(graStd);
		graStandardowa = new JTextArea(konfiguracja.getString("zasadyGraStd"), 5, 22);
		graStandardowa.setLineWrap(true);
		graStandardowa.setEditable(false);
		add(graStandardowa);
		
		wczytanieObr = new JLabel(konfiguracja.getString("wczytanieObrNagl"));
		add(wczytanieObr);
		wczytanieObrazka = new JTextArea(konfiguracja.getString("wczytanieObr"), 5, 22);
		wczytanieObrazka.setLineWrap(true);
		wczytanieObrazka.setEditable(false);
		add(wczytanieObrazka);
		
		ok = new JButton(konfiguracja.getString("ok"));
		ok.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				dispose();
			}
		});
		add(ok);
		
		setMinimumSize(new Dimension(290, 300));
		setResizable(false);
	}	
}
