package pl.edu.agh.student.aorzel.client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

import MiddlewareTestbed.AFactoryPrx;
import MiddlewareTestbed.AFactoryPrxHelper;
import MiddlewareTestbed.ItemAlreadyExists;
import MiddlewareTestbed.ItemBusy;
import MiddlewareTestbed.ItemNotExists;
import MiddlewareTestbed.ItemPrx;

public class Client {
	private Ice.Communicator ic;
	private AFactoryPrx factory;
	private Map<String, ItemPrx> acquiredItems = new HashMap<String, ItemPrx>();
	public static final BufferedReader READER = new BufferedReader(
			new InputStreamReader(System.in));

	public static void main(String[] args) {
		Client client = new Client();
		try {
			client.init(args);
		} catch (Exception e) {
			System.out.println("Cannot obtain factory reference: " + e.getMessage());
			return;
		}

		try {
			String operation;
			while (true) {
				System.out.println("Choose operation:\n"
						+ "1: create and get item\n2: get item\n3: operate on "
						+ "item\n4: release item\n[else] quit\n");
				operation = READER.readLine();

				if (operation.equals("1")) {
					client.createAndGetItem();
				} else if (operation.equals("2")) {
					client.getItem();
				} else if (operation.equals("3")) {
					client.operateOnItem();
				} else if (operation.equals("4")) {
					client.releaseItem();
				} else {
					break;
				}
			}
		} catch (IOException e) {
			System.out.println("Problem with stdin: " + e.getMessage());
		}

		client.finish();
	}

	public void init(String[] args) throws Exception {
		ic = Ice.Util.initialize(args);
		ItemOperator.setCommunicator(ic);

		Ice.ObjectPrx base = ic.propertyToProxy("Factory.Proxy");
		if (base == null) {
			throw new Exception("Cannot obtain factory proxy");
		}
		factory = AFactoryPrxHelper.checkedCast(base);
	}

	private void createAndGetItem() throws IOException {
		System.out.println("Choose name: ");
		String name = READER.readLine();
		System.out.println("Choose type: ");
		String type = READER.readLine();

		try {
			ItemPrx item = factory.create_item(name, type);
			acquiredItems.put(name, item);
		} catch (ItemAlreadyExists e) {
			System.out.println("Item already exists!");
		}
	}

	private void getItem() throws IOException {
		System.out.println("Choose name: ");
		String name = READER.readLine();

		try {
			ItemPrx item = factory.take_item(name);
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
		if (!acquiredItems.containsKey(name)) {
			System.out.println("You didn't acquire such item!");
			return;
		}

		ItemPrx item = acquiredItems.get(name);
		if (item.ice_isA("::MiddlewareTestbed::ItemA")) {
			ItemOperator.operateOnItemA(item);
		} else if (item.ice_isA("::MiddlewareTestbed::ItemB")) {
			ItemOperator.operateOnItemB(item);
		} else if (item.ice_isA("::MiddlewareTestbed::ItemC")) {
			ItemOperator.operateOnItemC(item);
		} else {
			System.out.println("Unknown type of item!");
		}
	}

	private void releaseItem() throws IOException {
		System.out.println("Choose name: ");
		String name = READER.readLine();
		if (!acquiredItems.containsKey(name)) {
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

	public void finish() {
		if (ic != null) {
			try {
				ic.destroy();
			} catch (Exception e) {
				// Nothing can be done
			}
		}
	}

}
