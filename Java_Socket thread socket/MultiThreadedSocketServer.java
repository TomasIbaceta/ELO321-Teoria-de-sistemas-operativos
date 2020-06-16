import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Calendar;
 
 
public class MultiThreadedSocketServer {
 
    ServerSocket myServerSocket;
    boolean ServerOn = true;
    int numero_cliente = 0;
 
 
    public MultiThreadedSocketServer()
    {
        try {
            myServerSocket = new ServerSocket(6789);
        }
        catch(IOException ioe) {
            System.out.println("No se puede crear server socket en puerto 6789.");
            System.exit(-1);
        }
 
        Calendar now = Calendar.getInstance();
        SimpleDateFormat formatter = new SimpleDateFormat("E yyyy.MM.dd 'at' hh:mm:ss a zzz");
        System.out.println("Fecha/Hora : " + formatter.format(now.getTime()));
 
        while(ServerOn)
        {                       
            try {
                Socket clientSocket = myServerSocket.accept();
                ClientServiceThread cliThread = new ClientServiceThread(clientSocket, numero_cliente);
		numero_cliente++;
                cliThread.start();
            }
            catch(IOException ioe) {
                System.out.println("Exception al aceptar conexión. Stack Trace :");
                ioe.printStackTrace();
            }
 
        }
 
        try {
            myServerSocket.close();
            System.out.println("Server Detenido");
        }
        catch(Exception ioe) {
            System.out.println("Problema al detener server socket");
            System.exit(-1);
        }
    }
 
    public static void main (String[] args) {
        new MultiThreadedSocketServer();       
    }    
}
