public class Long extends NumberExample {
	
	public int intValue() {
		return (int)val;
	}
	
	public long longValue() {
		return val;
	}
	
	public Long() {}
	
	public Long(long a) {
		val = a;
	}
	
	public Long(Long a) {
		val = a.longValue();
	}
	
	public boolean equals(Long a) {
		if(val == a.longValue()) return true;
		return false;
	}
	
	public int compareTo(Long a) {
		if(super.equals(a)) return 0;
		if(val > a.longValue()) return 1;
		else return -1;
	}	
	
	public static void main(String [] args) {
		Long pierwszy = new Long(15L);
		Long drugi = new Long(pierwszy);
		System.out.println(pierwszy.longValue());
		System.out.println(drugi.longValue());
		
		pierwszy = new Long(20L);
		System.out.println(pierwszy.longValue());
		System.out.println(drugi.longValue());+
		
		if(pierwszy.equals(drugi)) System.out.println("rowne");
		else System.out.println("nierowne");
		
		pierwszy = new Long(10L);
		System.out.println(pierwszy.longValue());
		System.out.println(drugi.longValue());
		
		System.out.println(pierwszy.compareTo(drugi));
	}
	
	private long val;	
}
