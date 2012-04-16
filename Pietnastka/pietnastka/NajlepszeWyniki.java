/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.awt.BorderLayout;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * Klasa ta pozwala wyświetlić informacje o najlepszych wynikach osiągniętych w grze na podstawie obiektu klasy PlikWynikowy.
 * 
 * @author Artur Orzeł
 *
 */

public class NajlepszeWyniki extends JDialog {
	private static final long serialVersionUID = 1L;
	private static final int JEDYNKA = 1;
	private static final int liczbaWierszy = 10;
	private static final int liczbaKolumn = 3;
	private ResourceBundle konfiguracja;
	private PlikWynikowy plikWynikowy;
	private JPanel panelNaglowka;
	private JLabel naglowek;
	private JPanel pusty;
	private JPanel pusty2;
	private JPanel panelWynikowy;
	private JPanel panelNumer;
	private JPanel panelGracz;
	private JPanel panelWynik;
	private JPanel przycisk;
	private JLabel [][] wyniki;
	private JButton ok;
	
	/**
	 * Konstruktor tworzący okno z wynikami gry. Na podstawie konfiguracji z obiektu typu ResourceBundle oraz pliku (obiekt PlikWynikowy)
	 * powstaje okno z 10 najlepszymi rezultatami.
	 * 
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * @param _plik Obiekt typu PlikWynikowy zawierający najlepsze wyniki.
	 */
	
	public NajlepszeWyniki(ResourceBundle _konfiguracja, PlikWynikowy _plik) {
		konfiguracja = _konfiguracja;
		plikWynikowy = _plik;
		
		setTitle(konfiguracja.getString("najlepszeWyniki"));
		setModalityType(Dialog.ModalityType.APPLICATION_MODAL);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setLayout(new BorderLayout(0,0));
		panelNumer = new JPanel(new GridLayout(liczbaWierszy,liczbaKolumn));
		panelGracz = new JPanel(new GridLayout(liczbaWierszy,liczbaKolumn));
		panelWynik = new JPanel(new GridLayout(liczbaWierszy,liczbaKolumn));
		
		wyniki = new JLabel[liczbaWierszy][liczbaKolumn];
		
		for(int i = 0; i < liczbaWierszy; i++) {
			wyniki[i][0] = new JLabel(String.valueOf(i+JEDYNKA) + ".");
			panelNumer.add(wyniki[i][0]);
			
			wyniki[i][1] = new JLabel((String)plikWynikowy.getProperty("wynikNazwa" + String.valueOf(i+JEDYNKA)));
			panelGracz.add(wyniki[i][1]);
			
			wyniki[i][2] = new JLabel((String)plikWynikowy.getProperty("wynik" + String.valueOf(i+JEDYNKA)));
			panelWynik.add(wyniki[i][2]);
		}
		
		panelNaglowka = new JPanel(new FlowLayout(FlowLayout.CENTER));
		naglowek = new JLabel(konfiguracja.getString("najlepszeWyniki"));
		panelNaglowka.add(naglowek);
		
		przycisk = new JPanel(new FlowLayout(FlowLayout.CENTER));
		ok = new JButton(konfiguracja.getString("ok"));
		ok.setPreferredSize(new Dimension(80,25));
		ok.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				dispose();
			}
		});
		przycisk.add(ok);
		
		pusty = new JPanel();
		pusty.setPreferredSize(new Dimension(15, 250));
		
		pusty2 = new JPanel();
		pusty2.setPreferredSize(new Dimension(15, 250));
		
		panelNumer.setPreferredSize(new Dimension(40, 250));
		panelGracz.setPreferredSize(new Dimension(100, 250));
		panelWynik.setPreferredSize(new Dimension(30, 250));
		
		panelWynikowy = new JPanel(new FlowLayout(FlowLayout.LEADING));
		panelWynikowy.add(panelNumer);
		panelWynikowy.add(panelGracz);
		panelWynikowy.add(panelWynik);
		
		add(panelNaglowka, BorderLayout.PAGE_START);
		add(pusty, BorderLayout.LINE_START);
		add(panelWynikowy, BorderLayout.CENTER);
		add(pusty2, BorderLayout.LINE_END);
		add(przycisk, BorderLayout.PAGE_END);
		
		setMinimumSize(new Dimension(220, 350));
		setResizable(false);
	}
}
