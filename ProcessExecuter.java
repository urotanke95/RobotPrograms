import com.sun.jna.Library;
import com.sun.jna.Native;


public class ProcessExecuter {
    public interface HelloLib extends Library {
        // loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
        String path = "/Users/imada_akihiro/Documents/Documents/GitRepositories/RobotPrograms/RobotPrograms/libhello.so";
        HelloLib INSTANCE = (HelloLib) Native.loadLibrary(path, HelloLib.class);

        // Cの関数名と一致させる
        void hello();
    }
    public static void main(String[] args){
        HelloLib hello = HelloLib.INSTANCE;
        hello.hello();
    }
}
