import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;


public class Rekord implements Serializable {
	private static final long serialVersionUID = 1L;
	private String str;
	private Integer in;
	
	public Rekord() {}
	public Rekord(String s, int i) {
		str = s;
		in = new Integer(i);
	}
	
	public String toString() {
		StringBuffer wyn = new StringBuffer();
		wyn.append("[");
		wyn.append(str);
		wyn.append(", ");
		wyn.append(in.toString());
		wyn.append("]");
		return wyn.toString();
	}
	
	private void writeObject(ObjectOutputStream stream) throws IOException {
		stream.writeObject(str);
		stream.writeObject(in);
	}
	
	private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException {	
		str = (String)stream.readObject();
		in = (Integer)stream.readObject();
	}
}
