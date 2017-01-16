import com.sun.jna.Library;
import com.sun.jna.Native;


public class PinkyuTester {
    public interface OpencvLib extends Library {
        // loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
        String path = "/home/pi/work/robot/RobotPrograms/libpinkyu1.so";
        OpencvLib INSTANCE = (OpencvLib) Native.loadLibrary(path, OpencvLib.class);

        // Cの関数名と一致させる
        void main();
		int getX();
		int getY();
    }
	
	public static void main(String[] args){
		Opencvlib opencvLib = OpencvLib.INSTANCE;    
        System.out.println("OpencvTester");
        opencvLib.main();
    }
}
