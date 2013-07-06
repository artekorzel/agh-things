public class Leaf extends Component {
	public Leaf() {
		name = new String("Leaf");
	}
	
	public Leaf(String s) {
		name = new String(s);
	}
	
	public void print(int depth) {
		for(int i = 0; i < depth; ++i) {
			System.out.print("	");
		}
		System.out.println(name);
	}
}
