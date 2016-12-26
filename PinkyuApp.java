public class PinkyuApp implements IApplication {
	PinkyuTester pinkyu1;
	int x, y;
	void Start() {
		pinkyu1 = new PinkyuTester();
		pinkyu1.main();
	}
	
	void Quit() {
		pinkyu1 = null;
	}
	
	void Update() {
		x = pinkyu1.getX();
		y = pinkyu1.getY();
		System.out.println(x + " " + y);
	}
	
	int CleanUp() {
		return 0;
	}
	
	void Order(String word) {
		System.out.println(word);
	}
}