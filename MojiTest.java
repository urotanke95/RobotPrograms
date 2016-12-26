import java.nio.charset.Charset;
class MojiTest {
    public static void main(String[] args) {
        String s = "あいうえお";//shift-jis ??????鐃緒申???????
        try{
            System.out.println("shift-jis s = " + s);
            System.out.println("1 "+s.getBytes("UTF-8"));
            System.out.println("2 " + new String(s.getBytes("UTF-8"),"UTF-8"));
            System.out.println("3 " + new String(s.getBytes("Shift-JIS"),"UTF-8"));
            System.out.println("4 " + new String(s.getBytes("UTF-8"),"Shift-JIS"));
            System.out.println("5 " + s.getBytes("Shift-JIS"));
            System.out.println("6 " + new String(s.getBytes("Shift-JIS"),"Shift-JIS"));
            System.out.println("7 " + s.getBytes("UTF-16"));
            System.out.println("8 " + new String(s.getBytes("UTF-16"),"UTF-16"));
            System.out.println("9 " + s.getBytes(Charset.forName("UTF-32")));
            System.out.println(new String(s.getBytes(Charset.forName("UTF-32")),Charset.forName("UTF-32")));
            System.out.println(s.getBytes(Charset.forName("Windows-31j")));
            System.out.println(new String(s.getBytes(Charset.forName("Windows-31j")),Charset.forName("Windows-31j")));
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
