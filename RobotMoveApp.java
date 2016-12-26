class RobotMoveApp implements IApplication {
    public void Start(){
        Robot.Init();
    }

    public void Quit(){
        Robot.Quit();
    }

    public void Update(){

    }

    public int Cleanup(){
        System.out.println("Cleanup Robot...");
        return 0;
    }

    public void Order(String word){
        if(word.equals("front"))Robot.Move(Robot.FB.Front);
        if(word.equals("back"))Robot.Move(Robot.FB.Back);
        if(word.equals("left"))Robot.Turn(Robot.LR.Left);
        if(word.equals("right"))Robot.Turn(Robot.LR.Right);
    }
}
