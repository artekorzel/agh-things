import java.util.Date;
import java.lang.StringBuffer;

class Employee {

	public Employee() {}
	
	public Employee(int year, int month, int day, double s, String n) {
		birthDate = new Date(year, month, day);
		salary = s;
		name = new String(n);
	}
	
	public Employee(Employee old) {
		birthDate = new Date(old.getBirthDate().toString());
		salary = old.getSalary();
		name = new String(old.getName());
	}

	public void setBirthDate(int day, int month, int year) {
		birthDate = new Date(day, month, year);
	}
	
	public void setSalary(double s) {
		salary = s;
	}
	
	public void setName(String n) {
		name = n;
	}
	
	public Date getBirthDate() {
		return birthDate;
	}
	
	public double getSalary() {
		return salary;
	}
	
	public String getName() {
		return name;
	}
	
	public String getDetails() {
		StringBuffer moj = new StringBuffer(name);
		moj.append(", ");
		moj.append(birthDate.toString());
		moj.append(", ");
		moj.append(salary);
		return moj.toString();
	}	

	private Date birthDate;
	private double salary;
	private String name;
	
	
	public static void main(String [] args)
	{
		Employee nowy = new Employee(91, 10, 11, 2000.0, "No Name");
		System.out.println(nowy.getDetails());
		
		nowy.setBirthDate(90, 11, 9);
		nowy.setName("Ala Sas");
		nowy.setSalary(3000.0);
		System.out.println(nowy.getDetails());
	} 
}
