public class PinkyuApp implements IApplication {
	int x,y;
	PinkyuTester pinkyu1 = PinkyuTester.INSTANCE;
	public void Start() {
		AudioLib.INSTANCE.play("ZensokuZensin.wav");
		pinkyu1.main();
		ArmLib.INSTANCE.lower();
		ArmLib.INSTANCE.arm_open();
		ArmLib.INSTANCE.arm_close();
 		ArmLib.INSTANCE.raise();
	}
	public void Quit()  {
		AudioLib.INSTANCE.play("MutekiSaikyo.wav");
		pinkyu1 = null;
	}

	public void Update() {

	}

	public int Cleanup() {
		return 0;
	}

	public void Order(String word) {
		if (word.equals("pick")) {
			//SurvoLib.INSTANCE.closeArm();
		}

	}
    public boolean IsRunning(){
        return true;
    }
}
