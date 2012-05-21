import java.util.Date;
import java.lang.StringBuffer;

class Secretary extends Employee {
	public Secretary() {}
	
	public Secretary(int year, int month, int day, double s, String n) {
		super(year, month, day, s, n);
	}
	
	public Secretary(Secretary old) {
		super(old);
	}
	
	public static void main(String [] args)
	{
		Engineer nowy = new Engineer(78, 10, 19, 2000.0, "Viera Als");
		System.out.println(nowy.getDetails());
		
		nowy.setBirthDate(85, 4, 16);
		nowy.setName("Kala Ul");
		nowy.setSalary(3000.0);
		System.out.println(nowy.getDetails());
		
		Employee moj = new Engineer(81, 3, 2, 3200.0, "Takie jakies");
		System.out.println(moj.getDetails()); 
	} 
}