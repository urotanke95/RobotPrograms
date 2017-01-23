class CollisionSensor implements Runnable{
    private static SensorLib sensorLib_;
    public void run(){
        System.out.println("Ready Sensor ...");
        sensorLib_=SensorLib.INSTANCE;
        sensorLib_.main();
    }

    public static int GetLeft(){
        return sensorLib_.get_left();
    }

    public static int GetRight(){
        return sensorLib_.get_right();
    }
}
