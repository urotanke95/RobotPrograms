
public enum FB{
    Front,
    Back,
}

public enum LR{
    Left,
    Right,
}


public class Robot {
    private static MoveLib moveLib_;
    static int speed_ = 500;
    static int turnSpeed_ = 300;
    static final int SPEED = 500;
    static final int TURN_SPEED = 300;

    public static void Init(){
        moveLib_ = MoveLib.INSTANCE;
        moveLib_.g_init();
    }

    public static void Move(FB dir){
				System.out.println("Robot go straight");
        if(dir == FB.Front) moveLib_.g_go_straight(1,(char)500);
        if(dir == FB.Back) moveLib_.g_go_straight(0,(char)speed_);
    }

    public static void Move(FB dir, int speed){
        speed_ = speed;
        if(dir == FB.Front) moveLib_.g_go_straight(1,(char)speed_);
        if(dir == FB.Back) moveLib_.g_go_straight(0,(char)speed_);
    }

    public static void Turn(LR lr){
        if(lr == LR.Left) moveLib_.g_turn(1,(char)turnSpeed_);
        if(lr == LR.Right) moveLib_.g_turn(0,(char)turnSpeed_);
    }

    public static void Turn(LR lr, int speed){
        turnSpeed_ = speed;
        if(lr == LR.Left) moveLib_.g_turn(1,(char)turnSpeed_);
        if(lr == LR.Right) moveLib_.g_turn(0,(char)turnSpeed_);
    }

    public static void Quit(){
        moveLib_.g_quit();
    }

    public static void Stop(){
        moveLib_.g_stop();
    }

}
