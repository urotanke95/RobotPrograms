import java.util.Scanner;

class MoveLibTester {
    public static void main(String[] args) {
        System.out.println("MoveLibTester");
        MoveLib moveLib = MoveLib.INSTANCE;

        moveLib.g_init();
        moveLib.g_go_straight(1,(char)500);
        System.out.println("止まるにはEnter");
        Scanner scan = new Scanner(System.in);
        String str = scan.next();
        System.out.println("BYE");
        moveLib.g_quit();
    }
}
