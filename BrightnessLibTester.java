import java.util.Scanner;

class BrightnessLibTester {
    public static void main(String[] args) {
        System.out.println("BrightnessLibTester");
        BrightnessLib brightnessLib = BrightnessLib.INSTANCE;

        brightnessLib.start_brightness();
        while(true){
            brightnessLib.update_brightness();
            int x = brightnessLib.get_vec_x();
            int y = brightnessLib.get_vec_y();
            System.out.println("x = " + x + ", y = "+ y);
            // try{
            //     Thread.sleep(1000);
            // }catch(Exception e){
            //     System.out.println(e);
            // }
        }
    }
}
