import java.util.List;
class Core implements ICore {

    public static void main(String[] args){
        Core core = new Core();
        
        SubThread sub = new SubThread(core);
        
        Thread thread = new Thread(sub);
        thread.start();
    }

    public void Order(List<JuliusWord> jwl){
		String[] words = new String[30];
		int i = 0, j = 0;
        i = 0;
		while(words[j] != "silE") {
			if (words[j].equals("GO")) {
				PinkyuTester pinkyu1 = new PinkyuTester();
				pinkyu1.main(null);
				j = 0;
				break;
			} else if (words[j].equals("back")) {
				GomiTester gomi = new GomiTester();
				gomi.main(null);
				j = 0;
				break;
			} else if (words[i].equals("SHOT")) {
				Shooter shoot = new Shooter();
				shoot.main(null);
				j = 0;
				break;
			} else {
				j++;
			}
		}
		return;
    }
}
