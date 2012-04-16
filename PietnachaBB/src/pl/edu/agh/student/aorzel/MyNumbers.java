package pl.edu.agh.student.aorzel;

import android.content.Context;
import android.widget.TableLayout;
import android.widget.TableRow;

public class MyNumbers {
	private final static int DIMENSION = 4;
	private MyButton [] myButtons = new MyButton [DIMENSION*DIMENSION];
	private Pietnacha myActivity;
	private TableLayout myLayout;

	public MyNumbers(Context context, Pietnacha activity) {
		myActivity = activity;
		myLayout = ((TableLayout)myActivity.findViewById(R.id.relativeLayout).findViewById(R.id.myNumbers));
		
		for(int i = 0; i < DIMENSION*DIMENSION; ++i) {
			myButtons[i] = new MyButton(context, i, this, myActivity);
			myButtons[i].setText(String.valueOf(i + 1));
			myButtons[i].setTextSize(30);
		}
		myButtons[DIMENSION*DIMENSION-1] = new MyButton(context, DIMENSION*DIMENSION - 1, this, myActivity);
		myButtons[DIMENSION*DIMENSION-1].setText("");
		myButtons[DIMENSION*DIMENSION-1].setTextSize(30);
		
		TableRow tmp;
		tmp = (TableRow)myLayout.findViewById(R.id.num1);
		for(int j = 0 ; j < DIMENSION; j++) {
			tmp.addView(myButtons[j], j);
		}
		
		tmp = (TableRow)myLayout.findViewById(R.id.num2);
		for(int j = 0 ; j < DIMENSION; j++) {
			tmp.addView(myButtons[DIMENSION+j], j);
		}
		
		tmp = (TableRow)myLayout.findViewById(R.id.num3);
		for(int j = 0 ; j < DIMENSION; j++) {
			tmp.addView(myButtons[DIMENSION*2+j], j);
		}
		
		tmp = (TableRow)myLayout.findViewById(R.id.num4);
		for(int j = 0 ; j < DIMENSION; j++) {
			tmp.addView(myButtons[DIMENSION*3+j], j);
		}
		
		MyButton.mix();
	}
	
	public MyButton getItem(int position) {
		return myButtons[position];
	}
}
