public class Test {
	public static void main(String [] args) {
		List lista = new List();
		lista.add(new Rekord(15, "ja"));
		lista.add(new Rekord(10, "ktos"));
		lista.add(new Rekord(4, "ktosdfksb fsfd"));
		lista.add(new Rekord(6, "gsbsr esrs"));
		lista.add(new Rekord(123, "ermso rbsjguv eygs"));
		
		System.out.println(lista.toString());
		for(ConcreateIterator it = new ConcreateIterator(lista); it.hasNext(); ) {
			System.out.println(it.next().toString());
		}
		
		lista.remove(3);		
		System.out.println(lista.toString());
		
		lista.clear();
		System.out.println(lista.toString());
	}
}
