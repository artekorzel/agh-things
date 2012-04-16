package pl.edu.agh.student.aorzel;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.TextView;

public class Pietnacha extends Activity {
	private ResultsFile plikWynikowy;
	private TextView result;
	
	public ResultsFile getPlikWynikowy() {
		return plikWynikowy;
	}
	
	public TextView getResult() {
		return result;
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
		if(requestCode == 1) {	
			String name = intent.getExtras().getString("pl.edu.agh.student.aorzel.GiveName");
			
			plikWynikowy.checkAndAddResult(result, name);
			MyButton.mix();
			result.setText("0");
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.menu, menu);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
	    switch (item.getItemId()) {
	        case R.id.nowa:
	        	MyButton.mix();
				result.setText("0");
	            return true;
	        case R.id.najlepszeWyniki:
	        	startActivityForResult(new Intent(Pietnacha.this, BestResults.class), 0);
	            return true;
	        case R.id.wyjdzZGry:
	        	finish();
	            return true;
	        default:
	            return super.onOptionsItemSelected(item);
	    }
	}

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.numbers);
       
        plikWynikowy = new ResultsFile(this);
        BestResults.setPlikWynikowy(plikWynikowy);
        result = (TextView)findViewById(R.id.textRes);
        MyButton.setFreeXAndY();
        new MyNumbers(this, this); 
    }
}