package com.caktuspace.chip8droid;

import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;

import java.io.IOException;

public class MainActivity extends Activity {

    public static final int CODE_RETOUR = 0;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Resources res = getResources(); //if you are in an activity
        AssetManager am = res.getAssets();
        String fileList[] = new String[0];
        try {
            fileList = am.list("chip8file");
        } catch (IOException e) {
            e.printStackTrace();
        }

        for (String aFileList : fileList) {
            Log.d("", aFileList);
        }
        Intent intent;
        intent = new Intent(this, AndroidFileBrowser.class);
        startActivityForResult(intent, CODE_RETOUR);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == CODE_RETOUR) {
            if (resultCode == RESULT_OK) {
                String filename = data.getStringExtra("filename");
                Intent intent = new Intent(this, Chip8_emulatorActivity.class);
                intent.putExtra("filename", filename);
                startActivity(intent);
            } else if (resultCode == RESULT_CANCELED) {
                finish();
            }
        }
    }
}
