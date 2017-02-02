import java.util.Scanner;

class BrightnessLibTester {
    public static void main(String[] args) {
        System.out.println("BrightnessLibTester");
        BrightnessLib brightnessLib = BrightnessLib.INSTANCE;

        BrightnessLib.INSTANCE.start_brightness();
        while(true){
            BrightnessLib.INSTANCE.update_brightness();
            int x = BrightnessLib.INSTANCE.get_vec_x();
            int y = BrightnessLib.INSTANCE.get_vec_y();
            System.out.println("x = " + x + ", y = "+ y);
            // try{
            //     Thread.sleep(1000);
            // }catch(Exception e){
            //     System.out.println(e);
            // }
        }
    }
}
