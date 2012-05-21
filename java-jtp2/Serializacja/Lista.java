import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.io.IOException;
import java.io.Serializable;


class Lista implements Serializable {
	private static final long serialVersionUID = 1L;

	public Lista() {
		lista = new ArrayList<Rekord>();
		liczbaEl = 0;
	}

	public List<Rekord> lista;
	public int liczbaEl;
	
	public void add(Rekord o) {
		lista.add(o);
		liczbaEl++;
	}
	
	public String toString() {
		Iterator<Rekord> it = lista.iterator();
		StringBuffer wyn = new StringBuffer();
		wyn.append("{");
		while(it.hasNext()) {
			wyn.append(it.next().toString());
			wyn.append(" ");
		}
		wyn.append("}");
		return wyn.toString();
	}
	
	private void writeObject(ObjectOutputStream stream) throws IOException {
		stream.writeInt(liczbaEl);
		Iterator<Rekord> it = lista.iterator();
		while(it.hasNext()) {
			stream.writeObject(it.next());
		}
	}
	
	private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException {	
		int i = stream.readInt();
		liczbaEl += i;
		while(i > 0) {			
			add((Rekord)stream.readObject());
			i--;
		}
	}
	
	public static void main(String [] args) {
		Lista nowa = new Lista();
		Lista nowa2 = new Lista();
		
		nowa.add(new Rekord("tekst jakis", 10));
		nowa.add(new Rekord("cos tam", 15));
		nowa.add(new Rekord("inny tekst", 12));		
		nowa.add(new Rekord("teweqvkis", 9));
		nowa.add(new Rekord("bla bla", 3));
		nowa.add(new Rekord("inabwrarnt", 7));
		
		System.out.println(nowa.toString());
		System.out.println(nowa2.toString());
		
		FileOutputStream plik;
		ObjectOutputStream str = null;
		FileInputStream plik2;
		ObjectInputStream str2 = null;
		try {
			plik = new FileOutputStream("D:\\plik.txt");
			str = new ObjectOutputStream(plik);
			nowa.writeObject(str);
			
			
			plik2 = new FileInputStream("D:\\plik.txt");
			str2 = new ObjectInputStream(plik2);
		
			nowa2.readObject(str2);
			
		} catch(IOException e) {
			System.err.println("Blad strumienia");
		} catch(ClassNotFoundException e) {
			System.err.println("Brak klasy");
		} finally {
			if(str != null) {
				try {
					str.close();
				} catch(IOException e) {
					System.err.println("Blad strumienia");
					str = null;
				}
			}
			
			if(str2 != null) {
				try {
					str2.close();
				} catch(IOException e) {
					System.err.println("Blad strumienia");
					str = null;
				}
			}
		}		
		System.out.println(nowa2.toString());
	}
}
