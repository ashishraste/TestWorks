package rmitest;

import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class TestClient {

	public TestClient() {
		System.out.println("TestClient invoked");
	}
	
	public static void main(String[] args) {
		 System.setSecurityManager(new RMISecurityManager());
		 String serverHostname = args[0];
		 try {			
			 String myurl = "//"+serverHostname+"/TestServer";
			 TestServer server = (TestServer)Naming.lookup(myurl);	
			 System.out.println("RMI server: " + server);
			 System.out.println("TestClient attached with server: "+server.getServerName());
			 System.out.println("Calling the server to print some numbers...");
			 server.printNumbers();
			 System.out.println("exiting now");
		 }
		 catch(Exception e) {
			 System.out.println("TestClient exception: " + e.getMessage());
			 e.printStackTrace();
		 }
	}
}
