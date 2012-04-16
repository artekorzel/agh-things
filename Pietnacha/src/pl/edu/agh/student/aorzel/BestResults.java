package pl.edu.agh.student.aorzel;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class BestResults extends Activity {
	private TableLayout resultsTable;
	private static ResultsFile plikWynikowy;
	
	public static void setPlikWynikowy(ResultsFile rf) {
		plikWynikowy = rf;
	}
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);		
		setContentView(R.layout.results);
		
		resultsTable = (TableLayout)findViewById(R.id.relativeLayout1).findViewById(R.id.tableLayout1);
		
		TableRow tr = (TableRow)resultsTable.findViewById(R.id.tableRow2);
		TextView tv = (TextView)tr.findViewById(R.id.textView2_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa1"));
		tv = (TextView)tr.findViewById(R.id.textView2_3);
		tv.setText((String)plikWynikowy.getProperty("wynik1"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow3);
		tv = (TextView)tr.findViewById(R.id.textView3_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa2"));
		tv = (TextView)tr.findViewById(R.id.textView3_3);
		tv.setText((String)plikWynikowy.getProperty("wynik2"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow4);
		tv = (TextView)tr.findViewById(R.id.textView4_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa3"));
		tv = (TextView)tr.findViewById(R.id.textView4_3);
		tv.setText((String)plikWynikowy.getProperty("wynik3"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow5);
		tv = (TextView)tr.findViewById(R.id.textView5_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa4"));
		tv = (TextView)tr.findViewById(R.id.textView5_3);
		tv.setText((String)plikWynikowy.getProperty("wynik4"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow6);
		tv = (TextView)tr.findViewById(R.id.textView6_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa5"));
		tv = (TextView)tr.findViewById(R.id.textView6_3);
		tv.setText((String)plikWynikowy.getProperty("wynik5"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow7);
		tv = (TextView)tr.findViewById(R.id.textView7_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa6"));
		tv = (TextView)tr.findViewById(R.id.textView7_3);
		tv.setText((String)plikWynikowy.getProperty("wynik6"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow8);
		tv = (TextView)tr.findViewById(R.id.textView8_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa7"));
		tv = (TextView)tr.findViewById(R.id.textView8_3);
		tv.setText((String)plikWynikowy.getProperty("wynik7"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow9);
		tv = (TextView)tr.findViewById(R.id.textView9_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa8"));
		tv = (TextView)tr.findViewById(R.id.textView9_3);
		tv.setText((String)plikWynikowy.getProperty("wynik8"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow10);
		tv = (TextView)tr.findViewById(R.id.textView10_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa9"));
		tv = (TextView)tr.findViewById(R.id.textView10_3);
		tv.setText((String)plikWynikowy.getProperty("wynik9"));
		
		tr = (TableRow)resultsTable.findViewById(R.id.tableRow11);
		tv = (TextView)tr.findViewById(R.id.textView11_2);
		tv.setText((String)plikWynikowy.getProperty("wynikNazwa10"));
		tv = (TextView)tr.findViewById(R.id.textView11_3);
		tv.setText((String)plikWynikowy.getProperty("wynik10"));
		
		findViewById(R.id.relativeLayout1).findViewById(R.id.button1).setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				setResult(RESULT_OK);
				finish();
			}
			
		});
	}	
}
