public class PinkyuApp implements IApplication {
	int x, y;
	public static void main(String[] args) {
		PinkyuTester pinkyu1 = new PinkyuTester();
		//AudioLib.INSTANCE.play("ZensokuZensin.wav");
		pinkyu1.main(null);
	  SurvoLib.INSTANCE.openArm();	
		//ArmLib.INSTANCE.lower();
		SurvoLib.INSTANCE.closeArm();
		//ArmLib.INSTANCE.raise();
	}
	public void Start(){}
	public void Quit()  {
		AudioLib.INSTANCE.play("MutekiSaikyo.wav");
		//pinkyu1 = null;
	}

	public void Update() {

	}

	public int Cleanup() {
		return 0;
	}

	public void Order(String word) {
		if (word.equals("pick")) {
			SurvoLib.INSTANCE.closeArm();
		}

	}
    public boolean IsRunning(){
        return true;
    }
}
