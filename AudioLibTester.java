public class AudioLibTester{
    public static void main(String[] args) {
        System.out.println("AudioLibTester");
        AudioLib audioLib = AudioLib.INSTANCE;
        String s = "Hello_jp.wav";
        audioLib.play(s);

    }
}
