public class PinkyuApp implements IApplication {
	PinkyuTester pinkyu1;
	int x, y;
	public void Start() {
		pinkyu1 = new PinkyuTester();
		pinkyu1.main(null);
	}
	
	public void Quit() {
		pinkyu1 = null;
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
