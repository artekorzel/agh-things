class Test {
	public static void main (String [] args) {
		Leaf leaf1 = new Leaf("leaf1");
		Leaf leaf2 = new Leaf("leaf2");
		Leaf leaf3 = new Leaf("leaf3");
		Leaf leaf4 = new Leaf("leaf4");
		Leaf leaf5 = new Leaf("leaf5");
 
        Composite composite1 = new Composite("composite1");
        Composite composite2 = new Composite("composite2");
        Composite composite3 = new Composite("composite3");
        Composite composite4 = new Composite("composite4");
		Composite composite5 = new Composite("composite5");
 
        composite1.add(leaf1);
        composite1.add(leaf3);
        composite2.add(leaf4);
        composite3.add(leaf2);
		composite5.add(leaf5);
		composite5.add(composite4);
        
        composite1.add(composite2);
        composite2.add(composite3);
		composite1.add(composite5);
 
        composite1.print(0);
	}		
}
