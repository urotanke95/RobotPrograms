import com.sun.jna.Library;
import com.sun.jna.Native;

public class HelloWorld {
    public interface CLibrary extends Library {
        CLibrary INSTANCE = (CLibrary)
                Native.loadLibrary("c" , CLibrary.class);

        void printf(String format, Object... args);
    }

    public static void main(String[] args) {
        CLibrary.INSTANCE.printf("Hello, World\n");
    }
}