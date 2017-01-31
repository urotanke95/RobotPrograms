import com.sun.jna.Library;
import com.sun.jna.Native;

public interface ShooterLib extends Library {
        // loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
        String path = "/home/pi/work/robot/RobotPrograms/libshoot.so";
        ShooterLib INSTANCE = (ShooterLib) Native.loadLibrary(path, ShooterLib.class);

        // Cの関数名と一致させる
        void start_moter();
        void stop_moter();
}
