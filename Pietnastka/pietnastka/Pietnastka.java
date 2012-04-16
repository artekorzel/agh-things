/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.io.File;
import java.util.Locale;
import java.util.ResourceBundle;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.KeyStroke;

/**
 * Okno główne gry.
 * 
 * Ta klasa to główne okno gry. Przy uruchomieniu najpierw przygotowuje plik log, następnie tworzy pasek menu. Na pasku umieszcza menu Plik
 * z możliwością uruchomienia gry standardowej - z liczbami od 1 do 15 (Gra Standardowa, skróŧ CTRL+S), gry niestandardowej na podstawie 
 * wczytanego obrazka (Wczytaj Obraz, skróŧ CTRL+O) oraz zamknięcia aplikacji (Zakończ, skróŧ CTRL+W). Ponadto dodaje menu Pomoc, w którym 
 * znajdują się informacje podstawowe o grze (O..., skróŧ CTRL+A), a także Zasady Gry (skróŧ CTRL+Z). Do okna aplikacji trafiają również 
 * przyciski uruchamiające oba tryby gry. Po wybraniu któregoś z nich pojawia się informacja o aktualnym wyniku oraz przycisk 
 * wznawiający grę.
 * 
 * @author Artur Orzeł
 * 
 */

public class Pietnastka {
	private static ResourceBundle konfiguracja = ResourceBundle.getBundle("Lang", Locale.getDefault());
	private static JFrame ramka;
	private static JMenuBar pasekMenu;
	private static JMenu plikMenu;
	private static JMenu pomocMenu;
	private static JMenuItem graStandardowaPlikMenu;
	private static JMenuItem wczytajObrazPlikMenu;
	private static JMenuItem zakonczPlikMenu;
	private static JMenuItem najlepszeWynikiPlikMenu;
	private static JMenuItem oPomocMenu;
	private static JMenuItem zasadyGryPomocMenu;
	private static JPanel przyciski;
	private static JButton przyciskGryStandardowej;
	private static JButton przyciskWczytaniaObrazka;
	private static JButton przyciskNajlepszeWyniki;
	private static Podzielony obrazekLewy;
	private static Obraz obrazekPrawy;
	private static JLabel etykietaWyniku;
	private static JLabel wynik;
	private static JButton przyciskRozpoczeciaOdNowa;
	private static JPanel panelWyniku;
	private static PlikWynikowy plikWynikowy;
	
	private Pietnastka() {}
	
	private static void start() {		
		JFrame.setDefaultLookAndFeelDecorated(true);
		ramka = new JFrame(konfiguracja.getString("ramka"));
		ramka.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		plikWynikowy = new PlikWynikowy(konfiguracja);
		pasekMenu = new JMenuBar();
		plikMenu = new JMenu(konfiguracja.getString("plikMenu"));
		pomocMenu = new JMenu(konfiguracja.getString("pomocMenu"));
		graStandardowaPlikMenu = new JMenuItem(konfiguracja.getString("graStandardowa"));
		graStandardowaPlikMenu.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, InputEvent.CTRL_DOWN_MASK));
		wczytajObrazPlikMenu = new JMenuItem(konfiguracja.getString("wczytajObraz"));
		wczytajObrazPlikMenu.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, InputEvent.CTRL_DOWN_MASK));
		najlepszeWynikiPlikMenu = new JMenuItem(konfiguracja.getString("najlepszeWyniki"));
		najlepszeWynikiPlikMenu.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_B, InputEvent.CTRL_DOWN_MASK));
		zakonczPlikMenu = new JMenuItem(konfiguracja.getString("zakoncz"));
		zakonczPlikMenu.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, InputEvent.CTRL_DOWN_MASK));
		oPomocMenu = new JMenuItem(konfiguracja.getString("oPomocMenu"));
		oPomocMenu.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, InputEvent.CTRL_DOWN_MASK));
		zasadyGryPomocMenu = new JMenuItem(konfiguracja.getString("zasadyGry"));
		zasadyGryPomocMenu.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Z, InputEvent.CTRL_DOWN_MASK));
		plikMenu.add(graStandardowaPlikMenu);
		plikMenu.add(wczytajObrazPlikMenu);
		plikMenu.add(najlepszeWynikiPlikMenu);
		plikMenu.add(zakonczPlikMenu);
		pomocMenu.add(zasadyGryPomocMenu);
		pomocMenu.add(oPomocMenu);
		pasekMenu.add(plikMenu);
		pasekMenu.add(pomocMenu);
		ramka.add(pasekMenu, BorderLayout.PAGE_START);
		
		graStandardowaPlikMenu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				przygotujGreStandardowa();
			}
		});
		
		wczytajObrazPlikMenu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				wczytajObrazekIZagraj();
			}
		});
		
		najlepszeWynikiPlikMenu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				new NajlepszeWyniki(konfiguracja, plikWynikowy).setVisible(true);
			}
		});
		
		zakonczPlikMenu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				ramka.dispose();				
			}
		});
		
		oPomocMenu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				JOptionPane.showMessageDialog(ramka, konfiguracja.getString("oInf"), konfiguracja.getString("oPomocMenu"),
																						JOptionPane.INFORMATION_MESSAGE);
			}
		});
		
		zasadyGryPomocMenu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				new ZasadyGry(konfiguracja).setVisible(true);
			}
		});
		
		przyciski = new JPanel();
		FlowLayout ukladPrzyciskow = new FlowLayout(2,10,10);
		ukladPrzyciskow.setAlignment(FlowLayout.CENTER);
		przyciski.setLayout(ukladPrzyciskow);
		
		przyciskGryStandardowej = new JButton(konfiguracja.getString("graStandardowa"));
		przyciskGryStandardowej.setMinimumSize(new Dimension(180,25));	
		przyciskGryStandardowej.setPreferredSize(new Dimension(180,25));
		przyciskGryStandardowej.setMaximumSize(new Dimension(180,25));
		przyciski.add(przyciskGryStandardowej);		
		
		przyciskWczytaniaObrazka = new JButton(konfiguracja.getString("wczytajObraz"));
		przyciskWczytaniaObrazka.setMinimumSize(new Dimension(180,25));	
		przyciskWczytaniaObrazka.setPreferredSize(new Dimension(180,25));
		przyciskWczytaniaObrazka.setMaximumSize(new Dimension(180,25));
		przyciski.add(przyciskWczytaniaObrazka);
		
		przyciskGryStandardowej.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				przygotujGreStandardowa();
			}
		});
		
		przyciskWczytaniaObrazka.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				wczytajObrazekIZagraj();
			}
		});
		
		ramka.add(przyciski, BorderLayout.PAGE_END);		
		
		ramka.pack();
		ramka.setVisible(true);
	}
	
	private static void wczytajObrazekIZagraj() {
		WczytajObraz wczytaj = new WczytajObraz(konfiguracja);
		JFileChooser wybieracz = wczytaj.getWybieracz();
		if(wybieracz.showOpenDialog(ramka) == JFileChooser.APPROVE_OPTION) {
			File obrazek = wybieracz.getSelectedFile();
			przygotujGre(obrazek);
		}
	}
	
	private static void przygotujWstepnieGre() {
		if(obrazekLewy != null) {
			ramka.remove(obrazekLewy);
			wynik.setText("0");
		} else {
			etykietaWyniku = new JLabel(konfiguracja.getString("etykietaWyniku"));
			etykietaWyniku.setPreferredSize(new Dimension(180,25));
			etykietaWyniku.setAlignmentX(Component.CENTER_ALIGNMENT);
			
			wynik = new JLabel("0");
			wynik.setAlignmentX(Component.CENTER_ALIGNMENT);
			
			panelWyniku = new JPanel();
			panelWyniku.setLayout(new BoxLayout(panelWyniku, BoxLayout.Y_AXIS));
			
			panelWyniku.add(Box.createRigidArea(new Dimension(0,50)));
			panelWyniku.add(etykietaWyniku);
			panelWyniku.add(Box.createRigidArea(new Dimension(0,20)));
			panelWyniku.add(wynik);
			panelWyniku.add(Box.createRigidArea(new Dimension(0,30)));
			
			przyciskRozpoczeciaOdNowa = new JButton(konfiguracja.getString("odNowa"));
			przyciskRozpoczeciaOdNowa.setAlignmentX(Component.CENTER_ALIGNMENT);
			przyciskRozpoczeciaOdNowa.setMinimumSize(new Dimension(160,25));
			przyciskRozpoczeciaOdNowa.setPreferredSize(new Dimension(160,25));
			przyciskRozpoczeciaOdNowa.setMaximumSize(new Dimension(160,25));
			przyciskRozpoczeciaOdNowa.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					wynik.setText("0");
					obrazekLewy.pomieszaj();
				}
			});
			
			przyciskNajlepszeWyniki = new JButton(konfiguracja.getString("najlepszeWyniki"));
			przyciskNajlepszeWyniki.setAlignmentX(Component.CENTER_ALIGNMENT);
			przyciskNajlepszeWyniki.setMinimumSize(new Dimension(160,25));
			przyciskNajlepszeWyniki.setPreferredSize(new Dimension(160,25));
			przyciskNajlepszeWyniki.setMaximumSize(new Dimension(160,25));
			przyciskNajlepszeWyniki.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent ae) {
					new NajlepszeWyniki(konfiguracja, plikWynikowy).setVisible(true);
				}
			});
			
			panelWyniku.add(przyciskRozpoczeciaOdNowa);
			panelWyniku.add(Box.createRigidArea(new Dimension(0,20)));
			panelWyniku.add(przyciskNajlepszeWyniki);
			ramka.add(panelWyniku, BorderLayout.LINE_START);
		}
		
		if(obrazekPrawy != null) {
			ramka.remove(obrazekPrawy);
		}
	}
	
	private static void przygotujGre(File obrazek) {
		przygotujWstepnieGre();
		
		obrazekPrawy = new Obraz(obrazek, konfiguracja);
		obrazekLewy = new PodzielonyObraz(obrazekPrawy.getObrazek(), ramka, wynik, konfiguracja,  plikWynikowy);	
		
		ramka.add(obrazekLewy, BorderLayout.CENTER);
		ramka.add(obrazekPrawy, BorderLayout.LINE_END);
		ramka.pack();
	}
	
	private static void przygotujGreStandardowa() {
		przygotujWstepnieGre();
		
		obrazekPrawy = null;
		obrazekLewy = new Liczby(ramka, wynik, konfiguracja, plikWynikowy);
		
		ramka.add(obrazekLewy, BorderLayout.CENTER);
		ramka.pack();
	}
	
	/**
	 * Metoda inicjująca działanie gry poprzez stworzenie wątku generującego interfejs graficzny.
	 * 
	 * @param args Tablica argumentów uruchomienia programu.
	 */
	
	public static void main(String [] args) {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				start();
			}
		});
	}
}
