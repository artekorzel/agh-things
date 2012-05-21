import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.io.FileInputStream;
import java.io.IOException;


class CSV {
	private ArrayList<HashMap<String, String> > rekordy;
	private ArrayList<String> naglowki;
	private int ileRekordow;
	
	public String getNaglowki() {
		return naglowki.toString();
	}
	
	public String getRekordy() {
		return rekordy.toString();
	}
	
	public int getIleRekordow() {
		return ileRekordow;
	}
	
	public CSV() {
		rekordy = new ArrayList<HashMap<String, String>>();
		naglowki = new ArrayList<String>();
		ileRekordow = 0;
	}

	public void naglowek(FileInputStream plik) throws IOException {
		int i;
		i = plik.read();
		StringBuffer pole = new StringBuffer();
		while(i != 13) {
			if(i == ',') {
				naglowki.add(pole.toString());
				pole = new StringBuffer();
			} else {
				pole.append((char)i);
			}
			i = plik.read();
		}
		naglowki.add(pole.toString());
		plik.skip(1L);
	}
	
	public boolean rekord(FileInputStream plik, int licz) throws IOException{
		int i;
		Iterator<String> it = naglowki.iterator();
		StringBuffer wart;
		rekordy.add(licz, new HashMap<String, String>());
		while(it.hasNext()) {
			wart = new StringBuffer();			
			i = plik.read();
			if(i == '"') {
				do {
					i = plik.read();
					while(i != '"') {
						wart.append((char)i);				
						i = plik.read();								
					}
					if(plik.available() != 0) {
						i = plik.read();
						if(i == '"') {
							wart.append((char)i);
						}
					} else {
						i = 0;
					}
				} while(i == '"');				
			} else {
				while(plik.available() != 0 && i != ',' && i != 13) {
					wart.append((char)i);				
					i = plik.read();								
				}
			}
			rekordy.get(licz).put(it.next().toString(), wart.toString());
			if(i == 13) plik.skip(1L);
		}
		return plik.available() != 0;
	}
	
	public void czytajCSV(FileInputStream plik) throws IOException {
		naglowek(plik);
		int licz = 0;
		while(rekord(plik, licz)) {
			licz++;
		}
		ileRekordow = licz;
	}
	
	public static void main(String [] args) {
		CSV csv = new CSV();
		FileInputStream plik = null;
		try {
			plik = new FileInputStream("D:\\plik.csv");
			csv.czytajCSV(plik);
			
			System.out.println(csv.getNaglowki());
			System.out.println(csv.getRekordy());
		} catch(Exception e) {
			System.err.println("Blad!");
		} finally {
			if(plik != null) {
				try {
					plik.close();
				} catch(IOException e) {
					System.err.println("Blad!");
					plik = null;
				}
			}
		}
	}
}