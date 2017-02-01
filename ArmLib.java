import com.sun.jna.Library;
import com.sun.jna.Native;


public interface ArmLib extends Library {
    String path = "/home/pi/work/robot/RobotPrograms/libarm_api.so";
    ArmLib INSTANCE = (ArmLib) Native.loadLibrary(path, ArmLib.class);

    // 基本的に正常:0 エラー:-1
	int init();
	int arm_open();
	int arm_close(); 
	int arm_fclose(); 
	int raise();
	int lower();
	int lower_t(int time);
	int stop();
	int quit();
}
