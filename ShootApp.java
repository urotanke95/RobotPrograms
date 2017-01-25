public class ShootApp implements IApplication {
	//ArmApp armer;
	Shooter shooter;
	
	public void Start() {
		//armup
		shooter = new Shooter();
		AudioLib.INSTANCE.play("Hassha.wav");
		shooter.main(null);
	}
	
	public void Quit() {
		shooter = null;
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
