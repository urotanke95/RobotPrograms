class SubThread implements Runnable{
    Core core_;
    public SubThread(Core core){
        core_ = core;
    }
    public void run(){
        System.out.println("Ready Cliant ...");
        JuliusCliant juliusCliant = new JuliusCliant(core_);
        juliusCliant.Run();
    }
}
