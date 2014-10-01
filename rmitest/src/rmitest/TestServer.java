package rmitest;

import java.rmi.*;

public interface TestServer extends Remote {
	public String getServerName() throws RemoteException;
	public void printNumbers() throws RemoteException;

}
