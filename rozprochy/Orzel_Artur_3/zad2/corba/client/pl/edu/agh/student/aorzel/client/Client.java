package pl.edu.agh.student.aorzel.client;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import org.omg.CORBA.ORB;
import org.omg.CosNaming.NamingContextExt;
import org.omg.CosNaming.NamingContextExtHelper;

import pl.edu.agh.student.aorzel.idl.AFactory;
import pl.edu.agh.student.aorzel.idl.AFactoryHelper;
import pl.edu.agh.student.aorzel.idl.Item;
import pl.edu.agh.student.aorzel.idl.ItemAlreadyExists;
import pl.edu.agh.student.aorzel.idl.ItemBusy;
import pl.edu.agh.student.aorzel.idl.ItemNotExists;

public class Client {
	private ORB orb = null;
	private AFactory factory = null;
	private Map<String, Item> acquiredItems = new HashMap<String, Item>();
	public static final BufferedReader READER = new BufferedReader(
			new InputStreamReader(System.in));

	public static void main(String[] args) {
		Client client = new Client();
		try {
			client.init(args);
		} catch(Exception e) {
			System.out.println("Cannot obtain factory reference!");
			return;
		}

		try {
			String operation;
			while (true) {
				System.out.println("Choose operation:\n"
						+ "1: create and get item\n2: get item\n3: operate on "
						+ "item\n4: release item\n[else] quit\n");
				operation = READER.readLine();
				
				if(operation.equals("1")) {
					client.createAndGetItem();
				} else if(operation.equals("2")) {
					client.getItem();
				} else if(operation.equals("3")) {
					client.operateOnItem();
				} else if(operation.equals("4")) {
					client.releaseItem();
				} else {
					break;
				}
			}
		} catch (IOException e) {
			System.out.println("Problem with stdin: " + e.getMessage());
		}
	}

	private void init(String[] args) throws Exception {
		Properties properties = System.getProperties();
		properties.load(new FileInputStream("./client.config"));
		
		orb = ORB.init(args, null);
		ItemOperator.setOrb(orb);

		org.omg.CORBA.Object nameServiceReference = orb
				.string_to_object(properties.getProperty("IOR.Address"));

		NamingContextExt namingContextReference = NamingContextExtHelper
				.narrow(nameServiceReference);

		org.omg.CORBA.Object factoryReference = namingContextReference
				.resolve_str(properties.getProperty("Factory.Name"));
		factory = AFactoryHelper.narrow(factoryReference);
	}
	
	private void createAndGetItem() throws IOException {
		System.out.println("Choose name: ");
		String name = READER.readLine();
		System.out.println("Choose type: ");
		String type = READER.readLine();
		
		try {
			Item item = factory.create_item(name, type);
			acquiredItems.put(name, item);
		} catch (ItemAlreadyExists e) {
			System.out.println("Item already exists!");
		}
	}
	
	private void getItem() throws IOException {
		System.out.println("Choose name: ");
		String name = READER.readLine();
		
		try {
			Item item = factory.take_item(name);
			acquiredItems.put(name, item);
		} catch (ItemNotExists e) {
			System.out.println("Item doesn't exist!");
		} catch (ItemBusy e) {
			System.out.println("Item is busy! Please wait");
		}
	}
	
	private void operateOnItem() throws IOException {
		System.out.println("Choose name: ");
		String name = READER.readLine();
		if(!acquiredItems.containsKey(name)) {
			System.out.println("You didn't acquire such item!");
			return;
		}
		
		Item item = acquiredItems.get(name);
		if(item._is_a("IDL:MiddlewareTestbed/ItemA:1.0")) {
			ItemOperator.operateOnItemA(item);
		} else if(item._is_a("IDL:MiddlewareTestbed/ItemB:1.0")) {
			ItemOperator.operateOnItemB(item);
		} else if(item._is_a("IDL:MiddlewareTestbed/ItemC:1.0")) {
			ItemOperator.operateOnItemC(item);
		} else {
			System.out.println("Unknown type of item!");
		}
	}
	
	private void releaseItem() throws IOException {
		System.out.println("Choose name: ");
		String name = READER.readLine();
		if(!acquiredItems.containsKey(name)) {
			System.out.println("You didn't acquire such item!");
			return;
		}
		
		try {
			acquiredItems.remove(name);
			factory.release_item(name);
		} catch (ItemNotExists e) {
			System.out.println("Item doesn't exist!");
		}
	}
}
