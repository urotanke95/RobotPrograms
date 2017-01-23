import com.sun.jna.Library;
import com.sun.jna.Native;


public interface SensorLib extends Library {
    String path = "/home/pi/work/robot/RobotPrograms/libcollision_sensor.so";
    SensorLib INSTANCE = (SensorLib) Native.loadLibrary(path, SensorLib.class);

    // Cの関数名と一致させる
    void main();
    int get_left();
    int get_right();
    void quit_func();
}
