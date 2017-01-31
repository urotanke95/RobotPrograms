public class PinkyuApp implements IApplication {
	PinkyuTester pinkyu1;
	int x, y;
	public void Start() {
		pinkyu1 = new PinkyuTester();
		AudioLib.INSTANCE.play("ZensokuZensin.wav");
		pinkyu1.main(null);
		ArmLib.INSTANCE.open();
		//ArmLib.INSTANCE.lower();
		ArmLib.INSTANCE.close();
		//ArmLib.INSTANCE.raise();
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
			ArmLib.INSTANCE.close();
		}

	}
    public boolean IsRunning(){
        return true;
    }
}
