public class PinkyuApp implements IApplication {
	PinkyuTester pinkyu1;
	ServoLib servolib;
	int x, y;
	public void Start() {
		pinkyu1 = new PinkyuTester();
		servolib = new ServoLib();
		pinkyu1.main(null);
		servolib.main(null);
	}
	
	public void Quit() {
		pinkyu1 = null;
		servolib = null;
	}
	
	public void Update() {
		
	}
	
	public int Cleanup() {
		return 0;
	}
	
	public void Order(String word) {
		System.out.println(word);
	}
}
