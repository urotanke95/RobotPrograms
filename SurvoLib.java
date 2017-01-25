import com.sun.jna.Library;
import com.sun.jna.Native;


public interface OpencvLib extends Library {
	// loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
	String path = "/home/pi/work/robot/RobotPrograms/libsurvo12_ex.so";
	OpencvLib INSTANCE = (OpencvLib) Native.loadLibrary(path, OpencvLib.class);
	
	// Cの関数名と一致させる
	void setup_survo();
	void open();
	void close();
	void stop();
	void end();
	void auto();
}
