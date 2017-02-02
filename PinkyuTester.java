import com.sun.jna.Library;
import com.sun.jna.Native;

public interface PinkyuTester extends Library {
       // loadLibraryの第一引数はあとで作成するlib***.soの***と一致させる。
      String path = "/home/pi/work/robot/RobotPrograms/libpinkyu1.so";

	PinkyuTester INSTANCE = (PinkyuTester) Native.loadLibrary(path, PinkyuTester.class);

        // Cの関数名と一致させる
      int main();
  		int getX();
  		int getY();
		
}
