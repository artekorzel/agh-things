import java.util.Date;
import java.lang.StringBuffer;

class Manager extends Employee {
	
	public Manager() {}
	
	public Manager(int year, int month, int day, double s, String n, String d) {
		super(year, month, day, s, n);
		department = d;
	}
	
	public Manager(Manager old) {
		super(old);
		department = new String(old.getDepartment());
	}
	
	public void setDepartment(String d) {
		department = d;
	}
	
	public String getDepartment() {
		return department;
	}
	
	public String getDetails() {
		StringBuffer nowy = new StringBuffer(super.getDetails());
		nowy.append(", ");
		nowy.append(department);
		return nowy.toString();
	}
	
	private String department;
	
	
	public static void main(String [] args)
	{
		Manager nowy = new Manager(91, 10, 11, 2000.0, "No Name", "dzial jakis");
		System.out.println(nowy.getDetails());
		
		nowy.setBirthDate(90, 11, 9);
		nowy.setName("Ala Sas");
		nowy.setSalary(3000.0);
		nowy.setDepartment("inny");
		System.out.println(nowy.getDetails());
		
		Employee moj = new Manager(51, 1, 2, 5000.0, "Inne imie", "kadrowy");
		System.out.println(moj.getDetails());
	} 
}
