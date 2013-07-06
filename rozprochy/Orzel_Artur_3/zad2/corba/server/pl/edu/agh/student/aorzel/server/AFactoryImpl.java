package pl.edu.agh.student.aorzel.server;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.omg.PortableServer.POA;

import pl.edu.agh.student.aorzel.idl.AFactoryPOA;
import pl.edu.agh.student.aorzel.idl.Item;
import pl.edu.agh.student.aorzel.idl.ItemAHelper;
import pl.edu.agh.student.aorzel.idl.ItemAlreadyExists;
import pl.edu.agh.student.aorzel.idl.ItemBHelper;
import pl.edu.agh.student.aorzel.idl.ItemBusy;
import pl.edu.agh.student.aorzel.idl.ItemCHelper;
import pl.edu.agh.student.aorzel.idl.ItemNotExists;

public class AFactoryImpl extends AFactoryPOA {

	private Map<String, Item> items = new ConcurrentHashMap<String, Item>();
	private Map<String, Boolean> itemsReserved = new ConcurrentHashMap<String, Boolean>();

	@Override
	public Item create_item(String name, String type) throws ItemAlreadyExists {
		if (items.containsKey(name)) {
			throw new ItemAlreadyExists();
		}

		try {
			POA rootPOA = this._poa();
			Item item;
			org.omg.CORBA.Object servantReference;
			if (type.equals("A")) {
				ItemAImpl servant = new ItemAImpl(name);
				servantReference = rootPOA.servant_to_reference(servant);
				item = ItemAHelper.narrow(servantReference);
			} else if (type.equals("B")) {
				ItemBImpl servant = new ItemBImpl(name);
				servantReference = rootPOA.servant_to_reference(servant);
				item = ItemBHelper.narrow(servantReference);
			} else if (type.equals("C")) {
				ItemCImpl servant = new ItemCImpl(name);
				servantReference = rootPOA.servant_to_reference(servant);
				item = ItemCHelper.narrow(servantReference);
			} else {
				throw new ItemAlreadyExists("Type not found");
			}
			items.put(name, item);
			itemsReserved.put(name, true);
			return item;
		} catch (Exception e) {
			System.out.println("Problem with creating item: " + e.getMessage());
			throw new ItemAlreadyExists("Problem with creating item!");
		}
	}

	@Override
	public Item take_item(String name) throws ItemNotExists, ItemBusy {
		if (!items.containsKey(name)) {
			throw new ItemNotExists();
		}

		if (itemsReserved.get(name) == true) {
			throw new ItemBusy();
		}

		itemsReserved.put(name, true);
		return items.get(name);
	}

	@Override
	public void release_item(String name) throws ItemNotExists {
		if (!items.containsKey(name)) {
			throw new ItemNotExists();
		}

		itemsReserved.put(name, false);
	}

}
