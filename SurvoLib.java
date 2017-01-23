import com.sun.jna.Library;
import com.sun.jna.Native;


public class SurvoLib {
    public interface OpencvLib extends Library {
        // loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
        String path = "/home/pi/work/robot/RobotPrograms/libsurvo12_ex.so";
        OpencvLib INSTANCE = (OpencvLib) Native.loadLibrary(path, OpencvLib.class);

        // Cの関数名と一致させる
        void main();
    }
	
	public static void main(String[] args){
		OpencvLib opencvLib = OpencvLib.INSTANCE;    
        System.out.println("SurvoLib");
        opencvLib.main();
    }
}
