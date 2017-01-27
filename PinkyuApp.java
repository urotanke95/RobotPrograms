public class PinkyuApp implements IApplication {
	PinkyuTester pinkyu1;
	int x, y;
	public void Start() {
		pinkyu1 = new PinkyuTester();
		AudioLib.INSTANCE.play("ZensokuZensin.wav");
		pinkyu1.main(null);
		SurvoLib.INSTANCE.setup_survo();
		SurvoLib.INSTANCE.openArm(); //後で消す
		LiftLib.INSTANCE.setup_lift();
	}
	
	public void Quit()  {
		AudioLib.INSTANCE.play("EndTestMove.wav");
		pinkyu1 = null;  
		SurvoLib.INSTANCE.stop();
		LiftLib.INSTANCE.stop();
	}  
	
	public void Update() {
		
	}
	
	public int Cleanup() {
		return 0;
	}
	
	public void Order(String word) {
		if (word.equals("pick")) {
			SurvoLib.INSTANCE.close();
			//LiftLib.INSTANCE.down();
		}
		
	}
}
