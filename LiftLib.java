import com.sun.jna.Library;
import com.sun.jna.Native;


public interface LiftLib extends Library {
	// loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
	String path = "/home/pi/work/robot/RobotPrograms/liblift_motor.so";
	LiftLib INSTANCE = (LiftLib) Native.loadLibrary(path, LiftLib.class);
	
	// Cの関数名と一致させる
	void setup_lift();
	void up();
	void down();
	void stop();
}
