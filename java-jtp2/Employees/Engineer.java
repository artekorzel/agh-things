import java.util.Date;
import java.lang.StringBuffer;

class Engineer extends Employee {
	public Engineer() {}
	
	public Engineer(int year, int month, int day, double s, String n) {
		super(year, month, day, s, n);
	}
	
	public Engineer(Engineer old) {
		super(old);
	}
	
	public static void main(String [] args)
	{
		Engineer nowy = new Engineer(91, 10, 11, 2000.0, "No Name");
		System.out.println(nowy.getDetails());
		
		nowy.setBirthDate(85, 4, 16);
		nowy.setName("Al Bigi");
		nowy.setSalary(3000.0);
		System.out.println(nowy.getDetails());
		
		Employee moj = new Engineer(81, 3, 2, 4000.0, "Inne imie");
		System.out.println(moj.getDetails()); 
	} 
	
}