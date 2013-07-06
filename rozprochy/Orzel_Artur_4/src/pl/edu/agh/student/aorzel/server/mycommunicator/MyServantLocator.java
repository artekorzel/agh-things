package pl.edu.agh.student.aorzel.server.mycommunicator;

import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MyServantLocator implements Ice.ServantLocator {
	
	private final Map<String, RoomI> rooms = new ConcurrentHashMap<String, RoomI>();

	@Override
	public Ice.Object locate(Ice.Current c,	Ice.LocalObjectHolder cookie) {
	    if(rooms.containsKey(c.id.name)) {
	    	System.out.println("Returning existing room");
	    	return rooms.get(c.id.name);
	    }
	    System.out.println("Creating room");
	    RoomI newRoomI = new RoomI(c.id.name);
	    rooms.put(c.id.name, newRoomI);
	    try {
			File file = new File(RoomI.ROOMS_FILE_PREFIX + c.id.name);
			if(!file.exists()) {
				file.createNewFile();
			}
		} catch (IOException e) {
			System.err.println("Cannot create file!");
			return null;
		}
	    return newRoomI;
	}

	@Override
	public void finished(Ice.Current c, Ice.Object o,
			java.lang.Object cookie) {
		System.out.println("Got room: " + c.id.name);
	}

	@Override
	public void deactivate(String category) {
		System.out.println("Shutting down...");
	}
}
