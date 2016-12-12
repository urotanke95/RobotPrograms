import java.util.Scanner;

class ThreadTester {
    public static void main(String[] args) {
        System.out.println("ThreadTester");
        Scanner scan = new Scanner(System.in);
        String str;
        Process thread = new Process();
        thread.start();
        while(true){
            System.out.println("Please Input :");
            str = scan.next();
            if(!str.equals("q"))continue;
            System.out.println("Exit");
            thread.Stop();

            break;
        }
        return;
    }
}

class Process extends Thread {
    private boolean running = true;
    public void start(){
        new Thread(this).start();
    }
    @Override
    public void run (){
        System.out.println("Process:running....");
        while(running){
            System.out.print("");
        }
        System.out.println("Process:EXIT");
    }
    public void Stop(){
        running = false;
        System.out.println("Process.Stop():running = " + running);
    }
}
