package pl.edu.agh.student.aorzel;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;

public class MyAdapter extends BaseAdapter {
	private final static int NUMBER_OF_BUTTONS = 16;
	private MyButton [] myButtons = new MyButton [NUMBER_OF_BUTTONS];
	private Pietnacha myActivity;
	
	public MyAdapter(Context c, Pietnacha activity) {
		myActivity = activity;
		for(int i = 0; i < NUMBER_OF_BUTTONS-1; ++i) {
			myButtons[i] = new MyButton(c, i, this, myActivity);
			myButtons[i].setText(String.valueOf(i + 1));
			myButtons[i].setTextSize(30);
		}
		myButtons[NUMBER_OF_BUTTONS-1] = new MyButton(c, NUMBER_OF_BUTTONS - 1, this, myActivity);
		myButtons[NUMBER_OF_BUTTONS-1].setText("");
		myButtons[NUMBER_OF_BUTTONS-1].setTextSize(30);
		
		MyButton.mix();
	}

	@Override
	public int getCount() {
		return myButtons.length;
	}

	@Override
	public Object getItem(int position) {
		return myButtons[position];
	}

	@Override
	public long getItemId(int position) {
		return myButtons[position].getId();
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		return myButtons[position];
	}

}
