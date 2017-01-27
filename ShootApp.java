public class ShootApp implements IApplication {

	public void Start() {
		AudioLib.INSTANCE.play("Hassha.wav");
	}

	public void Quit() {
		return 0;
	}

	public void Update() {
		return 0;
	}

	public int Cleanup() {
		return 0;
	}

	public void Order(String word) {
		System.out.println(word);
		if (word.equals("uchikorose"))
			Shooter.shoot();

		if (word.equals("yamete"))
			Shooter.stop_shoot();
	}
}
