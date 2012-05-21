public class List {
	private Rekord head;
	private Rekord tail;
	private int siz;
	
	public List() {
		head = null;
		tail = null;
	}
	
	public void add(Rekord r) {
		if(head == null) {
			head = r;
		} else {
			tail.next = r;
		}
		r.prev = tail;
		tail = r;
		siz++;
	}
	
	public Rekord get(int ind) {
		Rekord r = head;
		while(ind > 0 && r != null) {
			r = r.next;
			ind--;
		}
		return r;
	}
	
	public void remove(int ind) {
		Rekord r = get(ind);
		if(r != null) {
			if(r.prev != null) {
				r.prev.next = r.next;
			} else {
				head = r.next;
			}
			if(r.next != null) {
				r.next.prev = r.prev;
			}
			r = null;
			siz--;
		}
	}
	
	public void clear() {
		while(head != null) {
			remove(0);			
		}
	}
	
	public boolean isEmpty() {
		return head == null;
	}
	
	public Rekord getHead() {
		return head;
	}	
	
	public Rekord getTail() {
		return tail;
	}
	
	public int size() {
		return siz;
	}
	
	public String toString() {
		StringBuffer wyn = new StringBuffer();
		wyn.append("{");
		int i = 0;
		while(i < siz) {
			wyn.append(get(i).toString());
			i++;
		}
		wyn.append("}");
		return wyn.toString();
	}
}
