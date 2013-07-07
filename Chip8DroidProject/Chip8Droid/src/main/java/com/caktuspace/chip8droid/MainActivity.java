package com.caktuspace.chip8droid;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;

public class MainActivity extends Activity {

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = new Intent(this, AndroidFileBrowser.class);
        startActivityForResult(intent, CODE_RETOUR);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == CODE_RETOUR) {
            if(resultCode == RESULT_OK) {
                filename = data.getStringExtra("filename");
                Intent intent = new Intent(this, Chip8_emulatorActivity.class);
                intent.putExtra("filename", filename);
                startActivity(intent);
            } else if (resultCode == RESULT_CANCELED) {
                finish();
            }
        }
    }

    public static final int CODE_RETOUR = 0;
    private String filename;
}
