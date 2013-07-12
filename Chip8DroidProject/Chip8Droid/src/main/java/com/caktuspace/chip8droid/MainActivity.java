package com.caktuspace.chip8droid;

import android.app.ActionBar;
import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;

import java.io.IOException;

public class MainActivity extends Activity {

    public static final int CODE_RETOUR = 0;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Set up the action bar.
        final ActionBar actionBar = getActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_STANDARD);
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
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.game_list, menu);
        return true;
    }

    /** Called when the user clicks the Play button */
    public void browseGame(View view) {
        // Do something in response to button
        Intent intent;
        intent = new Intent(this, AndroidFileBrowser.class);
        startActivity(intent);
    }

    public void gameList(View view) {
        Intent intent;
        intent = new Intent(this, gameList.class);
        startActivity(intent);
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
