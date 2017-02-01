import com.sun.jna.Library;
import com.sun.jna.Native;


public interface UserLib extends Library {
    String path = "/home/pi/work/robot/RobotPrograms/libuser_cv.so";
    UserLib INSTANCE = (ObjLib) Native.loadLibrary(path, UserLib.class);

    // 基本的に正常:0 エラー:-1
	int search(int uid);
	int init();
}
