import java.util.List;
import java.util.ArrayList;

class Core implements ICore {
    private static IApplication nowApp_;
    private static boolean quit_ = false;
    private static boolean isRunApp_ = false;

    public static void main(String[] args){
        Core core = new Core();

        SubThread sub = new SubThread(core);

        Thread thread = new Thread(sub);
        thread.start();

        while(!quit_){
            if(nowApp_==null) continue;
            if(!isRunApp_) continue;
            nowApp_.Update();
        }
        thread.stop();
        System.out.println("BYE");
    }

    public void Order(List<JuliusWord> jwl){
        for (JuliusWord jw: jwl) {
            String word = jw.Word_;
            if(word.equals("silE")) return;
            else if(word.equals("end")) quitCore();
            else if(word.equals("test")) startApp(new TestApp());
            else if(word.equals("move")) startApp(new RobotMoveApp());
            else if(word.equals("stop")) stopApp();
						else if(word.equals("pinkyu")) startApp(new PinkyuApp());
            if(nowApp_!=null)nowApp_.Order(word);
    	}
    	return;
    }

    void startApp(IApplication app){
        app.Start();
        nowApp_ = app;
        isRunApp_ = true;
    }

    void stopApp(){
        isRunApp_ = false;

        if(nowApp_.Cleanup() != 0)System.out.println("Cleanup Error");
        nowApp_.Quit();
        nowApp_ = null;
    }

    void quitCore(){
        quit_ = true;
    }
}
