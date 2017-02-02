public class GetObjApp implements IApplication {

	private boolean working = false; //Application working
	private boolean running = false; //Method running
	private int status = 0; //status: obj:1 get:2 user:3 put:4 else:0
	private String target;
	private int lowtime = 0; //Lower time
	private final int MASTER = 1; //User master

	void Start() {
		ArmLib.INSTANCE.init();
		AudioLib.INSTANCE.play("whichbox.wav");
	}
    
	void Quit() {
		working = false;
		running = false;
		status = 0;
		ArmLib.INSTANCE.quit();
	}

    void Update(){
		System.out.println("");
		if (!working) {
			return;
		}
		if (!running) {
			running = true;
			if (status == 1) {
				if (ObjLib.INSTANCE.searchObj(target) < 0) {
					AudioLib.INSTANCE.play("error.wav");
					status = 0;
					working = false;
					running = false;
					return;
				}
				status = 2;
			} else if (status == 2) {
				lowtime = ArmLib.INSTANCE.lower();
				ArmLib.INSTANCE.arm_close();
				ArmLib.INSTANCE.raise();
				status = 3;
			} else if (status == 3) {
				ObjLib.INSTANCE.searchUser(target);
				status = 4;
			 else if (status == 4) {
				if (lowtime != 0) {
					ArmLib.INSTANCE.lower_t(lowtime);
				} else {
					ArmLib.INSTANCE.lower();
				}
				ArmLib.INSTANCE.open();
				ArmLib.INSTANCE.raise();
				AudioLib.INSTANCE.play("giveyou.wav");
				status = 0;
			} else {
				working = false;
			}
			running = false;
		}
	}
    
	int Cleanup(){
		
	}
    
	void Order(String word){
		if (!working) {
			return;
		}
		working = true;
		status = 1;
		target = word;
		AudioLib.INSTANCE.play("ok.wav");
	}
	
}
