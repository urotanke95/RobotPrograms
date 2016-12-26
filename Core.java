import java.util.List;
import java.util.ArrayList;

class Core implements ICore {
    private static IApplication nowApp_;
    private static boolean quit = false;

    public static void main(String[] args){
        Core core = new Core();

        SubThread sub = new SubThread(core);

        Thread thread = new Thread(sub);
        thread.start();

        while(!quit){
            if(nowApp_==null) continue;
            nowApp_.Update();
        }

        System.out.println("BYE");
    }

    public void Order(List<JuliusWord> jwl){
        for (JuliusWord jw: jwl) {
            String word = jw.Word_;
            if(word.equals("silE")) return;
            else if(word.equals("end")) quitCore();
            else if(word.equals("test")) startApp(new TestApp());
            else if(word.equals("stop")) stopApp();
    	}
    	return;
    }

    void startApp(IApplication app){
        app.Start();
        nowApp_ = app;
    }

    void stopApp(){
        if(nowApp_.Cleanup() != 0)System.out.println("Cleanup Error");

        nowApp_.Quit();
        nowApp_ = null;
    }

    void quitCore(){
        quit = true;
    }
}
