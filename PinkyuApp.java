public class PinkyuApp implements IApplication {
	PinkyuTester pinkyu1;
	int x, y;
	public void Start() {
		pinkyu1 = new PinkyuTester();
		pinkyu1.main();
	}
	
	public void Quit() {
		pinkyu1 = null;
	}
	
	public void Update() {
		x = pinkyu1.getX();
		y = pinkyu1.getY();
		System.out.println(x + " " + y);
	}
	
	public int CleanUp() {
		return 0;
	}
	
	public void Order(String word) {
		System.out.println(word);
	}
}
