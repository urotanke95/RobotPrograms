import java.io.*;
import java.net.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.util.*;

class JuliusCliant{
    private ICore core_;
    public JuliusCliant(ICore core){
        core_ = core;
    }
    public void Run(){
        try{
            Socket client = new Socket("localhost", 10500);
            InputStream input = new DataInputStream(client.getInputStream());
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));

            PrintStream output = new PrintStream(client.getOutputStream());

            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();

            String s;
            StringBuilder sb;



            while(true){
                sb = new StringBuilder();
                sb.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
                while(true){
                    if((s = reader.readLine()) == null) continue;
                    if(s.toString().equals(".")){
                        String data = sb.toString().replaceAll("<s>", "[s]").replaceAll("</s>", "[/s]");
                        //System.out.println(data);

                        InputStream stream = new ByteArrayInputStream(data.getBytes());

                        Node root = builder.parse(stream);
                        Node first = root.getFirstChild();

                        if(first.getNodeName().equals("RECOGOUT")){
                            NodeList nL = first.getChildNodes();
                            for(int j = 0; j < nL.getLength(); j++){
                                Node n = nL.item(j);
                                if(n.getNodeName().equals("SHYPO")){

                                    StringBuilder sbWord = new StringBuilder();
                                    float cm = 0;
                                    int num = 0;

                                    NodeList wL = n.getChildNodes();
                                    List<JuliusWord> jwl = new ArrayList<JuliusWord>();

                                    for(int k = 0; k < wL.getLength(); k++){
                                        Node w = wL.item(k);
                                        if(w.getNodeName().equals("WHYPO")){
                                            Element el = (Element)w;
                                            if(el.getAttribute("WORD").equals("。")) continue;
                                            if(el.getAttribute("WORD").equals("")) continue;
                                            String word = el.getAttribute("WORD");
                                            String classId = el.getAttribute("CLASSID");
                                            String phone = el.getAttribute("PHONE");
                                            String cmstr = el.getAttribute("CM");
                                            word = ToUnicode(word);
                                            classId = ToUnicode(classId);
                                            phone = ToUnicode(phone);
                                            cmstr = ToUnicode(cmstr);
                                            System.out.println("WORD:" + word +" CLASSID: " + classId+" PHONE: "+phone + " CM:"+cmstr);
                                            JuliusWord jw = new JuliusWord(word,phone, classId);
                                            jwl.add(jw);
                                            // sbWord.append(el.getAttribute("WORD"));
                                            // cm += Float.parseFloat(el.getAttribute("CM"));
                                            // num++;
                                        }
                                    }
                                    core_.Order(jwl);
                                    // System.out.println("WORDS:"+num);
                                    // System.out.println(sbWord+":"+cm/num);

                                }
                            }
                        }
                        System.out.println(first.getNodeName());

                        break;

                    }
                    sb.append(s);
                }
                System.out.println("\n");
            }
            //
            // output.print("DIE");
            // client.close();
        }
        catch(Exception e){
            e.printStackTrace();
        }

    }

    String ToUnicode(String src){
        String s = "";
        try{
            s = new String(src.getBytes("UTF-8"),"UTF-8");
        }catch (Exception e) {
            e.printStackTrace();
        }
        return s;
    }
}
