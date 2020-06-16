import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;


    class ClientServiceThread extends Thread {
        Socket myClientSocket;
        boolean m_bRunThread = true;
	boolean ServerOn = true;
	int numero_cliente = 0;
 
        public ClientServiceThread() {
            super();
        }
 
        ClientServiceThread(Socket s, int numero_cliente) {
            myClientSocket = s;
	    this.numero_cliente = numero_cliente;
 
        }
 
        public void run() {           
            BufferedReader in = null;
            PrintWriter out = null;
 
           System.out.println("Cliente "+ numero_cliente + " Aceptado Dirección - " + myClientSocket.getInetAddress().getHostName());
 
            try {                               
                in = new BufferedReader(new InputStreamReader(myClientSocket.getInputStream()));
                out = new PrintWriter(new OutputStreamWriter(myClientSocket.getOutputStream()));

                while(m_bRunThread) {                   
                    String clientCommand = in.readLine();
                    System.out.println("Client " + numero_cliente + " Dice :" + clientCommand);
 
                    if(!ServerOn) {
                        System.out.print("Server Detenido");
                        out.println("Server Detenido");
                        out.flush();
                        m_bRunThread = false;  
                    }
 
                    if(clientCommand.equalsIgnoreCase("quit")) {
                        m_bRunThread = false;  
                        System.out.print("Deteniendo Hilo cliente: " + numero_cliente);
                    } else if(clientCommand.equalsIgnoreCase("end")) {
                        m_bRunThread = false;  
                        System.out.print("Deteniendo Hilo cliente y Servidor: ");
                        ServerOn = false;
                    } else {
                            out.println("Server Dice al cliente " + numero_cliente +": " + clientCommand);
                            out.flush();
                    }
                }
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            finally {
                try {                   
                    in.close();
                    out.close();
                    myClientSocket.close();
                    System.out.println("...Detenido");
                }
                catch(IOException ioe) {
                    ioe.printStackTrace();
                }
            }
        }
  
    }
