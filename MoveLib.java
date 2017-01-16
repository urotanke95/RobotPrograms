import com.sun.jna.Library;
import com.sun.jna.Native;


public interface MoveLib extends Library {
    String path = "/home/pi/work/robot/RobotPrograms/libmove_api.so";
    MoveLib INSTANCE = (MoveLib) Native.loadLibrary(path, MoveLib.class);

    // Cの関数名と一致させる
    void g_init();
    void g_go_straight(int front, char speed);
    void g_left_wheel(char speed);
    void g_right_wheel(char speed);
    void g_turn(int left, char speed);
    void g_stop();
    void g_quit();
}
