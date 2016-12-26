import java.util.List;
import java.util.ArrayList;

class Core implements ICore {

    public static void main(String[] args){
        Core core = new Core();
        
        SubThread sub = new SubThread(core);
        
        Thread thread = new Thread(sub);
        thread.start();
    }

    public void Order(List<JuliusWord> jwl){
		List<String> words = new ArrayList<String>();
		int j = 0;
    for (JuliusWord jw: jwl) {
			words.add(jw.Word_);
		}
		while(!words.get(j).equals("silE")) {
			if (words.get(j).equals("go")) {
				PinkyuTester pinkyu1 = new PinkyuTester();
				pinkyu1.main(null);
				j = 0;
				break;
			} else if (words.get(j).equals("back")) {
				GomiTester gomi = new GomiTester();
				gomi.main(null);
				j = 0;
				break;
			} else {
				j++;
			}
		}
		return;
    }
}
