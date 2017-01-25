public class PinkyuApp implements IApplication {
	PinkyuTester pinkyu1;
	SurvoLib survolib;
	int x, y;
	public void Start() {
		pinkyu1 = new PinkyuTester();
		survolib = new SurvoLib();
		AudioLib.INSTANCE.play("ZensokuZensin.wav");
		pinkyu1.main(null);
		survolib.main(null);
	}
	
	public void Quit()  {
		pinkyu1 = null;  
		survolib = null;
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
