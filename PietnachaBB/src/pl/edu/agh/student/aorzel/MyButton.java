package pl.edu.agh.student.aorzel;

import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import java.lang.Math;
import java.util.Random;

public class MyButton extends Button implements OnClickListener {
	private int myX;
	private int myY;
	private static MyNumbers myAdapter;
	private static Pietnacha myActivity;
	private final static int DIMENSION = 4;
	private static int freeX;
	private static int freeY;

	public MyButton(Context context) {
		super(context);
	}
	
	public static void setFreeXAndY() {
		freeX = freeY = DIMENSION-1;
	}
	
	public MyButton(Context context, int position, MyNumbers adapter, Pietnacha activity) {
		super(context);
		myAdapter = adapter;
		myActivity = activity;
		myX = position % DIMENSION;
		myY = position / DIMENSION;
		
		setHeight(115);
		setWidth(144);
		setOnClickListener(this);
	}

	public int getMyX() {
		return myX;
	}

	public int getMyY() {
		return myY;
	}
	
	public void setMyX(int x) {
		myX = x;
	}
	
	public void setMyY(int y) {
		myY = y;
	}

	@Override
	public void onClick(View v) {
		if((Math.abs(freeX - myX) == 1 && freeY == myY) || (Math.abs(freeY - myY)==1 && freeX == myX)) {
			exchange(myX, myY);

			myActivity.getResult().setText(String.valueOf(Integer.parseInt((String) myActivity.getResult().getText())+1));
			
			if(freeY == DIMENSION-1 && freeX == DIMENSION-1) {
				boolean isSorted = true;
				for(int i = 0; i < DIMENSION*DIMENSION-1; ++i) {
					if(!((Button)myAdapter.getItem(i)).getText().equals(String.valueOf(i+1))) {
						isSorted = false;
						break;
					}
					
				}
				if(isSorted) {
					Intent intent = new Intent(myActivity, GiveName.class);
					myActivity.startActivityForResult(intent, 1);
				}
			}
		}
	}
	
	private static void exchange(int x, int y) {
		int freePos = DIMENSION * freeY + freeX;
		int myPos = DIMENSION * y + x;
		
		CharSequence text = ((Button)myAdapter.getItem(freePos)).getText();			
		((Button)myAdapter.getItem(freePos)).setText(((Button)myAdapter.getItem(myPos)).getText());
		((Button)myAdapter.getItem(myPos)).setText(text);
		
		freeX = x;
		freeY = y;
	}
	
	public static void mix() {
		Random maszynka = new Random();
		//0-gora,1-prawo,2-dol,3-lewo
		int k = DIMENSION*DIMENSION*DIMENSION*DIMENSION;
		while(k > 0) {
			switch(maszynka.nextInt(4)) {
				case 0:
					if(freeY > 0) {
						exchange(freeX, freeY - 1);
						k--;
					}
					break;				
				case 1: 
					if(freeX < DIMENSION - 1) {
						exchange(freeX + 1, freeY);
						k--;
					}
					break;				
				case 2: 
					if(freeY < DIMENSION - 1) {
						exchange(freeX, freeY + 1);
						k--;
					}
					break;
				case 3: 
					if(freeX > 0) {
						exchange(freeX - 1, freeY);
						k--;
					}
					break;
			}
		}
	}

	public static int getFreeX() {
		return freeX;
	}

	public static int getFreeY() {
		return freeY;
	}
}
