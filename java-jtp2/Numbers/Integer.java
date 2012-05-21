public class Integer extends NumberExample {

	int intValue() {
		return val;
	}
	
	long longValue() {
		return (long)val;
	}
	
	public Integer() {}
	
	public Integer(int a) {
		val = a;
	}
	
	public Integer(Integer a) {
		val = a.intValue();
	}
	
	public boolean equals(Integer a) {
		if(val == a.intValue()) return true;
		return false;
	}
	
	public int compareTo(Integer a) {
		if(super.equals(a)) return 0;
		if(val > a.intValue()) return 1;
		else return -1;
	}	
	
	public static void main(String [] args) {
		Integer moj = new Integer(5);
		Integer moj2 = new Integer(moj);
		System.out.println(moj.intValue());
		System.out.println(moj2.intValue());
		
		if(moj.equals(moj2)) System.out.println("rowne");
		else System.out.println("nierowne");
		
		moj = new Integer(10);
		System.out.println(moj.intValue());
		System.out.println(moj2.intValue());
		
		System.out.println(moj.compareTo(moj2));
	}
	
	private int val;
}
