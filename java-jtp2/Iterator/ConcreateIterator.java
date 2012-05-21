public class ConcreateIterator implements IteratorIF {
	private List list;
	private int index;
	
	public ConcreateIterator(List list) {
		this.list = list;
		index = 0;
	}
	
	public Object next() {
		return (Object)list.get(index++);
	}
	
	public boolean hasNext() {
		return index < list.size();
	}
}
