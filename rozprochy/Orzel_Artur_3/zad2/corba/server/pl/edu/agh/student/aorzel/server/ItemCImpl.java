package pl.edu.agh.student.aorzel.server;

import org.omg.CORBA.IntHolder;
import org.omg.CORBA.ShortHolder;

import pl.edu.agh.student.aorzel.idl.ItemCPOA;

public class ItemCImpl extends ItemCPOA {

	private ItemImpl item;

	public ItemCImpl(String name) {
		item = new ItemImpl(name);
	}

	@Override
	public void actionC(IntHolder a, ShortHolder b) {
		int oldAValue = a.value;
		b.value = (short) oldAValue;
		a.value = oldAValue + 1;
	}

	@Override
	public String name() {
		return item.name();
	}

	@Override
	public int get_item_age() {
		return item.get_item_age();
	}
}
