import java.util.Scanner;

public class ShooterLibTester {

	public static void main(String[] args) {
		System.out.println("GUN GUN Shoot!");

		ShooterLib shooter = ShooterLib.INSTANCE;
		shooter.start_moter();

		while (true) {
			System.out.println("殺戮をやめるには1を");
			Scanner scan = new Scanner(System.in);
			String str = scan.next();
			if (str.equals("1")) {
				shooter.stop_moter();
				break;
				}
		}

	}
}
