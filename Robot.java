public final class Robot {
    private static MoveLib moveLib_;
    //左のホイールの回転速度
    private static int left_wheel_ = 0;
    //左のホイールの回転速度
    private static int right_wheel_ = 0;

    //モーターの初期化．必ず最初に呼ぶ．
    public static void Init(){
        moveLib_ = MoveLib.INSTANCE;
        moveLib_.g_init();
    }
    //直線移動．FBはfront-backの略　speedは最大500辺りが妥当
    public static void Move(FB dir, int speed){
        left_wheel_ = speed;
        right_wheel_ = speed;

        if(dir == FB.Front) moveLib_.g_go_straight(1,(char)speed);
        if(dir == FB.Back) moveLib_.g_go_straight(0,(char)speed);
    }
    //回転．speedは最大300辺りが妥当
    public static void Turn(LR lr, int speed){
        if(LR.Left == lr){
            left_wheel_ = -speed;
            right_wheel_ = speed;
        }else if(LR.Right == lr){
            left_wheel_ = speed;
            right_wheel_ = -speed;
        }
        moveLib_.g_left_wheel((char)left_wheel_);
        moveLib_.g_right_wheel((char)right_wheel_);
    }
    //左のホイールの回転速度を指定する．移動中でも上書きされる．
    public static void SetLeft(int speed){
        left_wheel_ = speed;
        moveLib_.g_left_wheel((char)left_wheel_);
    }
    //左のホイールの回転速度を返す．
    public static int GetLeft(){
        return left_wheel_;
    }
    //右のホイールの回転速度を指定する．移動中でも上書きされる．
    public static void SetRight(int speed){
        right_wheel_ = speed;
        moveLib_.g_right_wheel((char)right_wheel_);
    }
    //右のホイールの回転速度を返す．
    public static int GetRight(){
        return right_wheel_;
    }
    //終了処理．ロボットを使い終わったら必ず呼ぶ．
    public static void Quit(){
        left_wheel_ = 0;
        right_wheel_ = 0;

        moveLib_.g_quit();
    }
    //ホイールを止めたいときに．
    public static void Stop(){
        left_wheel_ = 0;
        right_wheel_ = 0;
        moveLib_.g_stop();
    }

}
