public class Robot {
    private MoveLib moveLib_;
    int speed_ = 500;
    int turnSpeed_ = 300;

    public enum FB{
        Forword,
        Back,
    }

    public enum LR{
        Left,
        Right,
    }

    public Robot(){
        moveLib_ = MoveLib.INSTANCE;
    }

    public void Move(FB dir){
        if(dir == FB.Forword) moveLib_.g_go_straight(1,(char)speed_);
        if(dir == FB.Back) moveLib_.g_go_straight(0,(char)speed_);
    }

    public void Move(FB dir, int speed){
        speed_ = speed;
        if(dir == FB.Forword) moveLib_.g_go_straight(1,(char)speed_);
        if(dir == FB.Back) moveLib_.g_go_straight(0,(char)speed_);
    }

    public void Turn(LR lr){
        if(lr == LR.Left) moveLib_.g_turn(1,(char)turnSpeed_);
        if(lr == LR.Right) moveLib_.g_turn(0,(char)turnSpeed_);
    }

    public void Turn(LR lr, int speed){
        turnSpeed_ = speed;
        if(lr == LR.Left) moveLib_.g_turn(1,(char)turnSpeed_);
        if(lr == LR.Right) moveLib_.g_turn(0,(char)turnSpeed_);
    }

    public void Stop(){
        moveLib_.g_stop();
    }

}
