import java.util.Scanner;

class BrightnessLibTester {
    public static void main(String[] args) {
        System.out.println("BrightnessLibTester");
        BrightnessLib brightnessLib = BrightnessLib.INSTANCE;

        while(1){
            int x = brightnessLib.get_vec_x();
            int y = brightnessLib.get_vec_y();
            System.out.println("x = " + x + ", y = "+ y);
            Sleep(1000);
        }
    }
}
