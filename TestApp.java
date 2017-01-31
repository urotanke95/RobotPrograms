class TestApp implements IApplication {
    public void Start(){
        System.out.println("Start");
    }

    public void Update(){
        System.out.println("Update");
    }

    public void Quit(){
        System.out.println("Quit");
    }

    public int Cleanup(){
        System.out.println("Cleanup done");
        return 0;
    }

    public void Order(String word){
        System.out.println(word);
    }
    public boolean IsRunning(){
        return true;
    }
}
