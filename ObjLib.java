import com.sun.jna.Library;
import com.sun.jna.Native;


public interface ObjLib extends Library {
    String path = "/home/pi/work/robot/RobotPrograms/libobj_cv.so";
    ObjLib INSTANCE = (ObjLib) Native.loadLibrary(path, ObjLib.class);

    // 基本的に正常:0 エラー:-1
	int searchObj(char *obj);
	int searchUser(int uid);
	int init();
}
