public class Robot {
    private static MoveLib moveLib_;
    static int speed_ = 500;
    static int turnSpeed_ = 300;

    public enum FB{
        Front,
        Back,
    }

    public enum LR{
        Left,
        Right,
    }

    public static void Init(){
        moveLib_ = MoveLib.INSTANCE;
    }

    public static void Move(FB dir){
        if(dir == FB.Front) moveLib_.g_go_straight(1,(char)speed_);
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
