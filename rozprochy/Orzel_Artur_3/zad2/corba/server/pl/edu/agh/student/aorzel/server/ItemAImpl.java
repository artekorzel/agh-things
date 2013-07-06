package pl.edu.agh.student.aorzel.server;

import org.omg.CORBA.IntHolder;

import pl.edu.agh.student.aorzel.idl.ItemAPOA;

public class ItemAImpl extends ItemAPOA {

	private ItemImpl item;

	public ItemAImpl(String name) {
		item = new ItemImpl(name);
	}

	@Override
	public void actionA(float a, IntHolder b) {
		b.value = Math.round(a);
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
