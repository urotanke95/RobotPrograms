import java.util.Timer;
import java.util.TimerTask;

public class Avoid {
	static int first_left, first_right, left_spin, right_spin;
	static int pass = 0;
	final static int straight = 500;

	class Ret extends TimerTask {
		public void run() {
			return;
		}
	}

	class Start extends TimerTask {
		public void run() {
			pass++;
			left_spin = pass * straight / 1000;
			right_spin = pass * straight / 1000;
			Robot.Move(Robot.FB.Front, pass * straight / 1000);
		}
	}

	public static void AvoidCollision() {
		int left_sensor, right_sensor, low_sensor;
		final int BOTTOM = 10, TOP = 80, THR = 80;
		Timer ret_timer = new Timer();
		Timer start_timer = new Timer();

		do {
		first_left = Robot.LeftWheel;
		first_right = Robot.RightWheel;

		left_sensor = Collision.Left;
		right_sensor = Collision.Right;

		if (left_sensor < right_sensor) {
			left_sensor = Collision.Left;
			right_sensor = Collision.Right;

			//left_spin = (left_sensor - BOTTOM) / (TOP - BOTTOM) * first_left;
			//right_spin = (left_sensor - (TOP - BOTTOM) / 2) / (TOP - (TOP - BOTTOM) / 2) * first_right;

			SetLeftWheel((left_sensor - BOTTOM) / (TOP - BOTTOM) * first_left);
			SetRightWheel((left_sensor - (TOP - BOTTOM) / 2) / (TOP - (TOP - BOTTOM) / 2) * first_right);
		} else {
			left_sensor = Robot.LeftWheel;
			right_sensor = Robot.RightWheel;

			//right_spin = (right_sensor - BOTTOM) / (TOP - BOTTOM) * first_left;
			//left_spin = (right_sensor - (TOP - BOTTOM) / 2) / (TOP - (TOP - BOTTOM) / 2) * first_right;

			SetLeftWheel((right_sensor - BOTTOM) / (TOP - BOTTOM) * first_left);
			SetRightWheel((right_sensor - (TOP - BOTTOM) / 2) / (TOP - (TOP - BOTTOM) / 2) * first_right);
		}


		} while(left_sensor < THR || right_sensor < THR);


		if (left_sensor >= THR && right_sensor >= THR) {
			// if < THR, interupt
			ret_timer.schedule(new Ret(), (long) (2.0 * 1000));
			start_timer.schedule(new Start(), (long)0.0, (long)1.0);
			while (left_sensor >= THR && right_sensor >= THR) {
			}
		}

		// search destination
	}
}
