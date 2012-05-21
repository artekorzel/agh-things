/** 
 * Gra "Piętnastka"
 * 
 */

package pietnastka;

import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextPane;

/**
 * Okno typu JDialog, w którym gracz podaje swoją nazwę do wyświetlenia na liście najlepszych wyników.
 * 
 * @author Artur Orzeł
 *
 */

public class PodajNazwe extends JDialog {
	private static final long serialVersionUID = 1L;
	private ResourceBundle konfiguracja;
	private JLabel superWynik;
	private JTextPane naNazwe;
	private JButton ok;
	private String nazwa;
	
	/**
	 * Metoda zwracająca nazwę podaną przez gracza. Nie może być pusta.
	 * 
	 * @return Nazwa wpisana przez gracza.
	 */
	
	public String getNazwa() {
		return nazwa;
	}
	
	/**
	 * Konstruktor tworzący okno na podstawie podanej konfiguracji. W razie podania pustej nazwy gracz zostaje poinformowany,
	 * że nie może podać pustej nazwy.
	 * 
	 * @param _konfiguracja Obiekt typu ResourceBundle, z którego pobierane są wszelkie odpowiednie nazwy.
	 * 
	 */
	
	public PodajNazwe(ResourceBundle _konfiguracja) {
		konfiguracja = _konfiguracja;
		
		setTitle(konfiguracja.getString("podajNazweTytul"));	
		setModalityType(Dialog.ModalityType.APPLICATION_MODAL);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		BoxLayout bl = new BoxLayout(getContentPane(), BoxLayout.Y_AXIS);
		setLayout(bl);
		
		superWynik = new JLabel(konfiguracja.getString("superWynik"));
		superWynik.setAlignmentX(CENTER_ALIGNMENT);
		
		naNazwe = new JTextPane();
		naNazwe.setMaximumSize(new Dimension(100,25));
		naNazwe.setAlignmentX(CENTER_ALIGNMENT);
		
		ok = new JButton(konfiguracja.getString("ok"));
		ok.setPreferredSize(new Dimension(80,25));
		ok.setAlignmentX(CENTER_ALIGNMENT);
		ok.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				nazwa = naNazwe.getText();
				if(nazwa.equals("")) {
					JOptionPane.showMessageDialog(PodajNazwe.this, konfiguracja.getString("brakNazwy"), konfiguracja.getString("blad"), 
																							JOptionPane.WARNING_MESSAGE);
				} else {
					dispose();
				}
			}
		});
		
		add(Box.createRigidArea(new Dimension(10,10)));
		add(superWynik);
		add(Box.createRigidArea(new Dimension(0,10)));
		add(naNazwe);
		add(Box.createRigidArea(new Dimension(0,10)));
		add(ok);
		add(Box.createRigidArea(new Dimension(0,10)));
		
		setMinimumSize(new Dimension(300,130));
		setPreferredSize(new Dimension(300,130));
		setResizable(false);
	}
}
