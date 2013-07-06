class Test {
	public static void main(String [] args) {
		//Singleton1 moj = new Singleton1();
		Singleton1 moj2 = Singleton1.getInstance();
		Singleton1 moj3 = Singleton1.getInstance();
		System.out.println(moj2 == moj3);
		
		System.out.println(Singleton2.getAktN());
		System.out.println(Singleton2.getI());
		Singleton2 n1 = Singleton2.getInstance();
		
		System.out.println(Singleton2.getAktN());
		System.out.println(Singleton2.getI());
		Singleton2 n2 = Singleton2.getInstance();
		
		System.out.println(Singleton2.getAktN());
		System.out.println(Singleton2.getI());
		Singleton2 n3 = Singleton2.getInstance();
		
		System.out.println(Singleton2.getAktN());
		System.out.println(Singleton2.getI());
		Singleton2 n4 = Singleton2.getInstance();
		
		System.out.println(Singleton2.getAktN());
		System.out.println(Singleton2.getI());
		Singleton2 n5 = Singleton2.getInstance();
		
		System.out.println(Singleton2.getAktN());
		System.out.println(Singleton2.getI());
		Singleton2 n6 = Singleton2.getInstance();
		
		System.out.println(n1 == n2);
		System.out.println(n1 == n3);
		System.out.println(n1 == n4);
		System.out.println(n1 == n5);
		System.out.println(n1 == n6);
		System.out.println(n2 == n6);
	}
}
