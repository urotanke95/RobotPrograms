import com.sun.jna.Library;
import com.sun.jna.Native;

public interface LiftLib extends Library {
	String path = "/home/pi/work/robot/RobotPrograms/liblift_motor.so";
	LiftLib INSTANCE = (LiftLib) Native.loadLibrary(path, LiftLib.class);

	void up();
	void down();
	void stop();
	void setup_lift();

}












