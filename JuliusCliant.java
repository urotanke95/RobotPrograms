import java.io.*;
import java.net.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;

class JuliusCliant{
    public static void main(String args[]){
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
                                    for(int k = 0; k < wL.getLength(); k++){
                                        Node w = wL.item(k);
                                        if(w.getNodeName().equals("WHYPO")){

                                            Element el = (Element)w;
                                            if(el.getAttribute("WORD").equals("。")) continue;
                                            if(el.getAttribute("WORD").equals("")) continue;
                                            System.out.println("WORD:" + el.getAttribute("WORD") +" CLASSID: " + el.getAttribute("CLASSID") + " CM:"+el.getAttribute("CM"));

                                            sbWord.append(el.getAttribute("WORD"));
                                            cm += Float.parseFloat(el.getAttribute("CM"));
                                            num++;
                                        }

                                    }
                                    System.out.println("WORDS:"+num);
                                    System.out.println(sbWord+":"+cm/num);

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

            output.print("DIE");
            client.close();
        }
        catch(Exception e){
            e.printStackTrace();
        }

    }
}
