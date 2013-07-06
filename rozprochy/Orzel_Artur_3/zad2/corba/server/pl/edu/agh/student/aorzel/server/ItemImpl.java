package pl.edu.agh.student.aorzel.server;

import java.util.Date;

import pl.edu.agh.student.aorzel.idl.ItemPOA;

public class ItemImpl extends ItemPOA {
	private static final long MILIS_IN_SEC = 1000;

	private String name;
	private Date creationDate;

	public ItemImpl(String name) {
		this.name = name;
		creationDate = new Date();
	}

	@Override
	public String name() {
		return name;
	}

	@Override
	public int get_item_age() {
		return (int) ((new Date().getTime() - creationDate.getTime()) / MILIS_IN_SEC);
	}
}
