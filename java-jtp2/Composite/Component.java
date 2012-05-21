public abstract class Component {
	public Component() {
		name = new String("figura");
	}
	
	public Component(String s) {
		name = new String(s);
	}
	
	public abstract void print(int depth);
	
	protected String name;
}
