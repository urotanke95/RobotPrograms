import java.util.List;
class CliantTester implements ICore {
    public static void main(String[] args){
        CliantTester cl = new CliantTester();
        cl.Start();
    }

    public void Start(){
        System.out.println("Ready Cliant ...");
        JuliusCliant juliusCliant = new JuliusCliant(this);
        juliusCliant.Run();
    }

    public void Order(List<JuliusWord> jwl){
        for (JuliusWord jw : jwl) {
            System.out.println("CliantTester: " + jw.Word_);
        }
    }
}
