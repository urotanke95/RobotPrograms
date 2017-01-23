class RobotMoveApp implements IApplication {
    public void Start(){
        Robot.Init();
        System.out.println("Robot Ready !");
    }

    public void Quit(){
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
}
