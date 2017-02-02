import java.util.Timer;
import java.util.TimerTask;

public class Avoid {
	static int first_left, first_right, left_spin, right_spin;
	static int pass = 0;
	final static int straight = 500;

	static class Ret extends TimerTask {
		public void run() {
			return;
		}
	}

	static class Start extends TimerTask {
		public void run() {
			pass++;
			left_spin = pass * straight / 1000;
			right_spin = pass * straight / 1000;
			Robot.Move(FB.Front, pass * straight / 1000);
		}
	}

	public static void AvoidCollision() {
		int left_sensor, right_sensor, low_sensor;
		final int BOTTOM = 10, TOP = 80, THR = 80;
		Timer ret_timer = new Timer();
		Timer start_timer = new Timer();

			first_left = Robot.GetLeft();
			first_right = Robot.GetRight();
		do {
			left_sensor = CollisionSensor.GetLeft();
			right_sensor = CollisionSensor.GetRight();

			if (left_sensor < right_sensor) {
				left_sensor = CollisionSensor.GetLeft();
				right_sensor = CollisionSensor.GetRight();

				Robot.SetLeft((left_sensor - BOTTOM) / (TOP - BOTTOM) * first_left);
				Robot.SetRight((left_sensor - (TOP - BOTTOM) / 2) / (TOP - (TOP - BOTTOM) / 2) * first_right);
			} else {
				left_sensor = CollisionSensor.GetLeft();
				right_sensor = CollisionSensor.GetRight();
	
				Robot.SetLeft((right_sensor - BOTTOM) / (TOP - BOTTOM) * first_left);
				Robot.SetRight((right_sensor - (TOP - BOTTOM) / 2) / (TOP - (TOP - BOTTOM) / 2) * first_right);
			}
		} while(left_sensor < THR || right_sensor < THR);

		if (left_sensor >= THR && right_sensor >= THR) {
			// if < THR, interupt
			ret_timer.schedule(new Ret(), (long) (2.0 * 1000));
			start_timer.schedule(new Start(), (long)0.0, (long)1.0);
			while (left_sensor >= THR && right_sensor >= THR) {}
		}
	}
}
