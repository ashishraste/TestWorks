package rmitest;

import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.ExportException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Properties;
import java.io.FileInputStream;

public class TestServerImpl extends UnicastRemoteObject implements TestServer {
	private static final long serialVersionUID = 1L;
	private int port=1099;
	
	public TestServerImpl() throws RemoteException {
		super();
	}
	
	public TestServerImpl(int port) throws RemoteException {
		super(port);
	}
	
	@Override
	public String getServerName() throws RemoteException {
		return "RemoteBot";
	}
	
	@Override
	public void printNumbers() throws RemoteException {
		System.out.println("printNumbers called");
		for (int i=0; i<10; ++i) {
			System.out.println(i+"\n");
			try {
				Thread.sleep(1000);
			} 
			catch(InterruptedException ex) {
			    Thread.currentThread().interrupt();
			}
		}
	}
	
	public static void main(String[] args) {    		
		FileInputStream propsFile;
    String hostname = argv[0];
		try {
      //  write the JVM properties in a file (system.properties) and set it here
			//  propsFile = new FileInputStream("system.properties"); 
			//  Properties props = new Properties(System.getProperties());
			//  props.load(propsFile);
			//	setting java system properties 
			//  System.setProperties(props);
			//	display new properties set on the command line
			//  System.getProperties().list(System.out);
			
			TestServerImpl obj = new TestServerImpl();			
			System.out.println("RMI server: " + obj);
			// creating a registry on the local host, binding the stub to it       	
      LocateRegistry.createRegistry(1099);
      Naming.rebind("//"+hostname+"/TestServer", obj);
	  }
		catch (Exception e) {
			System.out.println("TestServer exception: " + e.getMessage());
	        e.printStackTrace();
		}
	}

}
