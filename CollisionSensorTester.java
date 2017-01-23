class CollisionSensorTester{
    public static void main(String[] args) {
        CollisionSensor collisionSensor = new CollisionSensor();
        Thread sensorThread = new Thread(collisionSensor);
        sensorThread.start();

        System.out.println("Sensor Left =" + CollisionSensor.GetLeft());
        System.out.println("Sensor Right =" + CollisionSensor.GetRight());
    }

}
