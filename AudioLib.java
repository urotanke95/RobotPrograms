import com.sun.jna.Library;
import com.sun.jna.Native;


public interface AudioLib extends Library {
    String path = "/home/pi/work/robot/RobotPrograms/libaudio_api.so";
    AudioLib INSTANCE = (AudioLib) Native.loadLibrary(path, AudioLib.class);

    // Cの関数名と一致させる
    void play(String filename);
}
