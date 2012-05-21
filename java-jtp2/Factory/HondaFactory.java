class HondaFactory implements AbstractFactoryIF {
	public SportsCarIF createSportsCar() {
		return new HondaS2000();
	}
	
	public EconomyCarIF createEconomyCar() {
		return new HondaCivicHybrid();
	}
}
