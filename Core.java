import java.util.List;
class Core implements ICore {

    public static void main(String[] args){
        Core core = new Core();
        /* 別スレッドとして動作させるオブジェクトを作成 */
        SubThread sub = new SubThread(core);
        /* 別のスレッドを作成し、スレッドを開始する */
        Thread thread = new Thread(sub);
        thread.start();
    }

    public void Order(List<JuliusWord> jwl){
        for (JuliusWord jw : jwl) {
            System.out.println("CliantTester: " +" WORD="+ jw.Word_ + " PHONE=" + jw.Phone_);
        }
    }
}
