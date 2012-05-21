public class Singleton1 {
	private static Singleton1 _soleInstance = null;
	
	private Singleton1() {}
	
	public static Singleton1 getInstance() {
		if(_soleInstance == null) {
			_soleInstance = new Singleton1();
		}
		return _soleInstance;
	}
}