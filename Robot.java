public final class Robot {
    private static MoveLib moveLib_;
    private static CollisionSensor collisionSensor_;
    private static int left_wheel_ = 0;
    private static int right_wheel_ = 0;

    public static void Init(){
        moveLib_ = MoveLib.INSTANCE;
        moveLib_.g_init();
        /* Init Sensor Thread */
        collisionSensor_ = new CollisionSensor();
        Thread sensorThread = Thread(collisionSensor_);
        sensorThread.start();
    }

    public static void Move(FB dir, int speed){
        left_wheel_ = speed;
        right_wheel_ = speed;

        if(dir == FB.Front) moveLib_.g_go_straight(1,(char)speed);
        if(dir == FB.Back) moveLib_.g_go_straight(0,(char)speed);
    }

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

    public static void SetLeft(int speed){
        left_wheel_ = speed;
        moveLib_.g_left_wheel((char)left_wheel_);
    }

    public static void SetRight(int speed){
        right_wheel_ = speed;
        moveLib_.g_right_wheel((char)right_wheel_);
    }

    public static int GetLeftSensorValue(){
        // TODO create later
        return collisionSensor_.GetLeft();
    }
    public static int GetRightSensorValue(){
        // TODO create later
        return collisionSensor_.GetRight();
    }

    public static void Quit(){
        left_wheel_ = 0;
        right_wheel_ = 0;

        moveLib_.g_quit();
    }

    public static void Stop(){
        left_wheel_ = 0;
        right_wheel_ = 0;
        moveLib_.g_stop();
    }

}
