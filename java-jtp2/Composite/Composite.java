import java.util.ArrayList;

public class Composite extends Component {
	public Composite() {
		_children = new ArrayList<Component>();
		name = new String("Composite");
	}
	
	public Composite(String s) {
		_children = new ArrayList<Component>();
		name = new String(s);
	}
	
	public void print(int depth) {
		for(int i = 0; i < depth; ++i) {
			System.out.print("	");
		}
		System.out.println(name);
		for(Component c: _children) {
			c.print(depth + 1);
		}
	}
	
	public void add(Component c) {
		_children.add(c);
	}
	
	public void remove(Component c) {
		_children.remove(c);
	}
	
	private ArrayList<Component> _children;	
}
