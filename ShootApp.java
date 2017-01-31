public class ShootApp implements IApplication {

	public void Start() {
	//	AudioLib.INSTANCE.play("Hassha.wav");
	}

	public void Quit() {
		ShooterLib.INSTANCE.stop_moter();
	}

	public void Update() {
		return;
	}

	public int Cleanup() {
		return 0;
	}

	public void Order(String word) {
		System.out.println(word);
		if (word.equals("uchikorose"))
			ShooterLib.INSTANCE.start_moter();
	}
}
