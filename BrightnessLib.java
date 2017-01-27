import com.sun.jna.Library;
import com.sun.jna.Native;


public interface BrightnessLib extends Library {
    String path = "/home/pi/work/robot/RobotPrograms/libbrightness.so";
    BrightnessLib INSTANCE = (BrightnessLib) Native.loadLibrary(path, BrightnessLib.class);

    // Cの関数名と一致させる
    int start_capture();
    int get_vec_x();
    int get_vec_y();
}
