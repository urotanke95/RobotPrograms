public class GetObjApp implements IApplication {

	void Start() {
		if (ArmLib.INSTANCE.open() < 0) {
			printf("Error\n");
		}

		if (ArmLib.INSTANCE.raise() < 0) {
			printf("Error\n");
		}
	}
    
	void Quit() {
		if (ArmLib.INSTANCE.open() < 0) {
			printf("Error\n");
		}

		if (ArmLib.INSTANCE.raise() < 0) {
			printf("Error\n");
		}
	}

    void Update(){
	
	}
    
	int Cleanup(){
	
	}
    
	void Order(String word){
	
	}

	void search() {
	
	}

	void pickUp() {
		if (ArmLib.INSTANCE.lower() < 0) {
			printf("Error\n");		
		}
		if (ArmLib.INSTANCE.close() < 0) {
			printf("Error\n");		
		}
		if (ArmLib.INSTANCE.raise() < 0) {
			printf("Error\n");		
		}
	}

	void putDown() {
		if (ArmLib.INSTANCE.lower() < 0) {
			printf("Error\n");		
		}
		if (ArmLib.INSTANCE.open() < 0) {
			printf("Error\n");		
		}
		if (ArmLib.INSTANCE.raise() < 0) {
			printf("Error\n");		
		}
	}
}
