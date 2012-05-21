class FordFactory implements AbstractFactoryIF {
	public SportsCarIF createSportsCar() {
		return new FordMustang();
	}
	
	public EconomyCarIF createEconomyCar() {
		return new FordFocus();
	}
}
