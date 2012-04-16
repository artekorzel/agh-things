package pl.edu.agh.student.aorzel;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

import android.widget.TextView;

public class ResultsFile extends Properties {
	private static final long serialVersionUID = 1L;
	private static final int LICZBA_WYNIKOW = 10;
	private static Logger logger = Logger.getLogger(ResultsFile.class.getName());
	private String fileName = "Results.properties";
	private File plik = new File(fileName);
	private Pietnacha myActivity;
	
	public ResultsFile(Pietnacha activity) {
		myActivity = activity;		
		
		InputStream fis = null;
		try {
			fis = myActivity.openFileInput(fileName);					
			try {
				load(fis);
			} catch (IOException e) {
				logger.log(Level.WARNING, "Nieudane ładowanie informacji z istniejacego pliku z wynikami", e);
			} finally {
				if(fis != null) {
					try {
						fis.close();
					} catch (IOException e) {
						logger.log(Level.WARNING, "Nieudane zamykanie istniejacego pliku z wynikami", e);
						fis = null;
					}
				}
			}
				
		} catch (IOException e) {
			logger.log(Level.WARNING, "Nieudane otwieranie istniejacego pliku z wynikami", e);
				
			for(int i = 1; i <= LICZBA_WYNIKOW; ++i) {
				setProperty("wynikNazwa" + String.valueOf(i), myActivity.getResources().getString(R.string.player) 
																						+ " " + String.valueOf(i)); 
				setProperty("wynik" + String.valueOf(i), String.valueOf(i*10 + 100)); 
			}				
			try {
				plik.createNewFile();
			} catch (IOException e2) {
				logger.log(Level.WARNING, "Nieudane tworzenie pliku z wynikami", e2);
			}				
			saveToFile();
		}	
	}
	
	private void saveToFile() {
		OutputStream fos = null;
		try {
			fos = myActivity.openFileOutput(fileName, 0);
		} catch (IOException e) {
			logger.log(Level.WARNING, "Nieudane otwieranie istniejacego pliku z wynikami", e);
		}
			
		try {
			store(fos, "Results");
		} catch (IOException e) {
			logger.log(Level.WARNING, "Nieudane skladowanie w istniejacym pliku z wynikami", e);
		} finally {
			if(fos != null) {
				try {
					fos.close();
				} catch (IOException e) {
					logger.log(Level.WARNING, "Nieudane zamykanie istniejacego pliku z wynikami", e);
					fos = null;
				}
			}
		}
	}
	
	public void checkAndAddResult(TextView wynik, String name) {
		int wynikInt = Integer.parseInt(wynik.getText().toString());
		int najnizszy = Integer.parseInt(getProperty("wynik" + String.valueOf(LICZBA_WYNIKOW)));
		
		if(wynikInt < najnizszy) {			
			int i = LICZBA_WYNIKOW-1;
			while(i > 0 && wynikInt < (najnizszy = Integer.parseInt(getProperty("wynik" + String.valueOf(i))))) {
				setProperty("wynik" + String.valueOf(i+1), String.valueOf(najnizszy));
				setProperty("wynikNazwa" + String.valueOf(i+1), getProperty("wynikNazwa" + String.valueOf(i)));
				i--;
			}
			i++;
				
			setProperty("wynik" + String.valueOf(i), String.valueOf(wynikInt));
			setProperty("wynikNazwa" + String.valueOf(i), name);
			
			saveToFile();
		}
	}
}
