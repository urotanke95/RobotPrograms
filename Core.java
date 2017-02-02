import java.util.List;
import java.util.ArrayList;

class Core implements ICore {
    private static IApplication nowApp_;
    private static boolean quit_ = false;
    private static boolean isRunApp_ = false;
    private static boolean isWillStopApp = false;
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
            if(!isRunApp_) continue;
            if(nowApp_==null) continue;
            if(needAvoid()){
                // 正面に何かあった場合
                System.out.println("something is in front. STOP APP");
                stopApp();
            } else if (isWillStopApp){
                // アプリケーションを終了するフラグが立っている場合
                stopApp();
                isWillStopApp = false;
            } else if(!nowApp_.IsRunning()){
                stopApp();
            }else{
                // アプリケーションが動作中
                nowApp_.Update();
            }
        }
        stopApp();
        thread.stop();
        System.out.println("BYE");
        System.exit(0);
    }

    public void Order(List<JuliusWord> jwl){
        for (JuliusWord jw: jwl) {
            String word = jw.Word_;
            if(word.equals("silE")) return;
            if(nowApp_!=null){
                if(word.equals("stop")) isWillStopApp = true;
                nowApp_.Order(word);
            }else{
                if(word.equals("end")) quitCore();
                else if(word.equals("test")) startApp(new TestApp());
                else if(word.equals("move")) startApp(new RobotMoveApp());
			    else if(word.equals("pinkyu")) startApp(new PinkyuApp());
			    else if(word.equals("shoot")) startApp(new ShootApp());
                else if(word.equals("brightness")) startApp(new BrightnessApp());
            }
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
        AudioLib.INSTANCE.play("Bye.wav");
        quit_ = true;
    }

    static boolean needAvoid(){
        return (CollisionSensor.GetLeft() <= STOP_DISTANCE) && (CollisionSensor.GetRight()<=STOP_DISTANCE);
    }
}
