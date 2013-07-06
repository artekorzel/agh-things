class Test {   
	public static void main(String[] args) {
		AbstractFactoryIF ford = new FordFactory();
		AbstractFactoryIF honda = new HondaFactory();
		
        ford.createEconomyCar().driveSlow();
        honda.createEconomyCar().driveSlow();
        
        ford.createSportsCar().driveFast();
        honda.createSportsCar().driveFast();
    }
}