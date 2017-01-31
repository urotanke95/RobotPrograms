class BrightnessApp implements IApplication {
    static final int threshold = 10;
    private boolean quit = false;
    public void Start(){
        Robot.Init();
        System.out.println("Brightness Ready !");
        AudioLib.INSTANCE.play("Brightness.wav");
    }

    public void Quit(){
        AudioLib.INSTANCE.play("EndBrightness.wav");
        Robot.Stop();
        Robot.Quit();
    }

    public void Update(){
        int x = BrightnessLib.INSTANCE.get_vec_x();
        int y = BrightnessLib.INSTANCE.get_vec_y();
        if(x > threshold){
            Robot.Turn(LR.right, x);
        }else if(x < -threshold){
            Robot.Turn(LR.left, -x);
        }else if(y < threshold){

        }else{
            Robot.Move(FB.front, y);
        }
    }

    public int Cleanup(){
        System.out.println("Cleanup Robot...");
        return 0;
    }

    public void Order(String word){
    }

    public boolean IsRunning(){
        return !quit;
    }
}
