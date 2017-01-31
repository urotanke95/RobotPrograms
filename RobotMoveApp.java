class RobotMoveApp implements IApplication {
    public void Start(){
        Robot.Init();
        System.out.println("Robot Ready !");
        AudioLib.INSTANCE.play("TestMove.wav");
    }

    public void Quit(){
        AudioLib.INSTANCE.play("EndTestMove.wav");
        Robot.Stop();
        Robot.Quit();
    }

    public void Update(){

    }

    public int Cleanup(){
        System.out.println("Cleanup Robot...");
        return 0;
    }

    public void Order(String word){
        if(word.equals("front"))Robot.Move(FB.Front, 300);
        if(word.equals("back"))Robot.Move(FB.Back, 300);
        if(word.equals("left"))Robot.Turn(LR.Left, 300);
        if(word.equals("right"))Robot.Turn(LR.Right, 300);
    }
    public boolean IsRunning(){
        return true;
    }
}
