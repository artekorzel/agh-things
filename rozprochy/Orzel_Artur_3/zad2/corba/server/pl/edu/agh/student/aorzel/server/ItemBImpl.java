package pl.edu.agh.student.aorzel.server;

import pl.edu.agh.student.aorzel.idl.ItemBPOA;

public class ItemBImpl extends ItemBPOA {

	private ItemImpl item;

	public ItemBImpl(String name) {
		item = new ItemImpl(name);
	}

	@Override
	public float actionB(String a) {
		try {
			return Float.parseFloat(a);
		} catch (NumberFormatException e) {
			return Float.MIN_VALUE;
		}
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
