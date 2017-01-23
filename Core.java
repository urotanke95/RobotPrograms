import java.util.List;
import java.util.ArrayList;

class Core implements ICore {
    private static IApplication nowApp_;
    private static boolean quit_ = false;
    private static boolean isRunApp_ = false;
    private static final int STOP_DISTANCE = 50;

    public static void main(String[] args){
        Core core = new Core();

        SubThread sub = new SubThread(core);
        Thread thread = new Thread(sub);
        thread.start();

        CollisionSensor collisionSensor = new CollisionSensor();
        Thread sensorThread = new Thread(collisionSensor);
        sensorThread.start();

        while(!quit_){
            if(CollisionSensor.GetLeft() <= STOP_DISTANCE && CollisionSensor.GetRight()<=STOP_DISTANCE){
                System.out.println("something is in front. STOP APP");
                stopApp();
            }
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

    static void startApp(IApplication app){
        if(nowApp_!=null)stopApp();
        app.Start();
        nowApp_ = app;
        isRunApp_ = true;
    }

    static void stopApp(){
        if(nowApp_==null){
            System.out.println("No Application runnnig now");
            return;
        }

        isRunApp_ = false;

        if(nowApp_.Cleanup() != 0)System.out.println("Cleanup Error");
        nowApp_.Quit();
        nowApp_ = null;
    }

    static void quitCore(){
        quit_ = true;
    }
}
