package pl.edu.agh.student.aorzel;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.EditText;

public class GiveName extends Activity {
	private String name;
	
	public String getName() {
		return name;
	}
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.givename);
        
        findViewById(R.id.buttongn).setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				name = ((EditText)findViewById(R.id.editgn)).getText().toString();
				if(!name.equals("")) {
					GiveName.this.getIntent().putExtra("pl.edu.agh.student.aorzel.GiveName", name);
					setResult(RESULT_OK, GiveName.this.getIntent());
					finish();
				}
			}        	
        });
    }
}
