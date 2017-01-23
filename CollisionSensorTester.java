class CollisionSensorTester{
    public static void main(String[] args) {
        CollisionSensor collisionSensor = new CollisionSensor();
        Thread sensorThread = new Thread(collisionSensor);
        sensorThread.start();

        try{
        Thread.sleep(3000); //3000ミリ秒Sleepする
        }catch(InterruptedException e){}

        System.out.println("Sensor Left =" + CollisionSensor.GetLeft());
        System.out.println("Sensor Right =" + CollisionSensor.GetRight());
    }

}
