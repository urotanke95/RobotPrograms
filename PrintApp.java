class PrintApp implements IApplication {
    int count = 0;
    public void OnEnable(){
        System.out.println("PrintApp:OnEnable");
    }
    public void OnDisable(){
        System.out.println("PrintApp:OnDisable");
    }
    public void Update(){
        System.out.println("PrintApp:Update");
    }
    public int Cleanup(){
        Thread.sleep(0);
        count++;
        if(count < 100) return 0;
        return 1
    }
}
