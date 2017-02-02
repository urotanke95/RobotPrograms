import com.sun.jna.Library;
import com.sun.jna.Native;


public interface SurvoLib extends Library {
	// loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
	String path = "/home/pi/work/robot/RobotPrograms/libsurvo12_ex.so";
	SurvoLib INSTANCE = (SurvoLib) Native.loadLibrary(path, SurvoLib.class);
	
	// Cの関数名と一致させる
	void setup_survo();
	void openArm();
	void closeArm();
	void stop();
	void end();
	void automatic();
}
