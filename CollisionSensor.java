class CollisionSensor implements Runnable{
    private static SensorLib sensorLib_;
    private static int INF = 1000;
    public void run(){
        System.out.println("Ready Sensor ...");
        sensorLib_=SensorLib.INSTANCE;
        sensorLib_.main();
    }

    public static int GetLeft(){
        if(sensorLib_==null)return INF;
        return sensorLib_.get_left();
    }

    public static int GetRight(){
        if(sensorLib_==null)return INF;
        return sensorLib_.get_right();
    }
}
