import java.io.*; 
import java.net.*; 
class TCPClient { 

    public static void main(String argv[]) throws Exception 
    { 
        String sentence; 
        String modifiedSentence; 

        BufferedReader inFromUser = 
          new BufferedReader(new InputStreamReader(System.in)); 

        Socket clientSocket = new Socket("localhost", 6789); 

        DataOutputStream outToServer = 
          new DataOutputStream(clientSocket.getOutputStream()); 

        BufferedReader inFromServer = 
          new BufferedReader(new
          InputStreamReader(clientSocket.getInputStream())); 
	while(true) {
	  sentence = inFromUser.readLine(); 

	  outToServer.writeBytes(sentence + '\n'); 
	  if(sentence.equals("end")) {
		  clientSocket.close();
		  break;
	  }

	  modifiedSentence = inFromServer.readLine(); 

	  System.out.println("Desde SERVER: " + modifiedSentence); 
	}

                   
    } 
} 
