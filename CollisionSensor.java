class CollisionSensor implements Runnable{
    private SensorLib sensorLib_;
    public void run(){
        System.out.println("Ready Sensor ...");
        sensorLib_=SensorLib.INSTANCE;
        sensorLib_.main();
    }

    public int GetLeft(){
        return sensorLib_.get_left();
    }

    public int GetRight(){
        return sensorLib_.get_right();
    }
}
