public class GetObjApp implements IApplication {

	private boolean working;

	void Start() {
		ArmLib.INSTANCE.init();
	//	AudioLib.INSTANCE.play("");
		wroking = false;
	}
    
	void Quit() {
	
	}

    void Update(){
	
	}
    
	int Cleanup(){
	
	}
    
	void Order(String word){
		if (word.equals("green")) {
			ObjLib.INSTANCE.searchObj("green");
		} else if (word.equals("red")) {
			ObjLib.INSTANCE.searchObj("red");
		} else if (word.equals("blue")) {
			ObjLib.INSTANCE.searchObj("blue");
		} else {
			if (working) {
				
			} else {
			
			}
		} 
	}
	
}
