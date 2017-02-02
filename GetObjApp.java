public class GetObjApp implements IApplication {

	private boolean working = false; //Application working
	private boolean running = false; //Method running
	private int status = 0; //status: obj_f:1 obj:2 get:3 user_f:4 user:5 put:6 else:0
	private String target;
	private int lowtime = 0; //Lower time
	private final int MASTER = 1; //User master

	void Start() {
		ArmLib.INSTANCE.init();
	//	AudioLib.INSTANCE.play("");
	}
    
	void Quit() {
		working = false;
		running = false;
		ArmLib.INSTANCE.quit();
	}

    void Update(){
		System.out.println("");
		if (!running) {
			running = true;
			if (status == 1) {
				ObjLib.INSTANCE.searchObj(target);
			} else if (status == 2) {
				lowtime = ArmLib.INSTANCE.lower();
				ArmLib.INSTANCE.arm_close();
				ArmLib.INSTANCE.raise();
				status = 3;
			} else if (status == 3) {
				ObjLib.INSTANCE.searchUser(target);
			 else if (status == 4) {
				if (lowtime != 0) {
					ArmLib.INSTANCE.lower_t(lowtime);
				} else {
					ArmLib.INSTANCE.lower();
				}
				ArmLib.INSTANCE.open();
				ArmLib.INSTANCE.raise();
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
	}
	
}
