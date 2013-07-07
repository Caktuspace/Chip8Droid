package com.caktuspace.chip8droid;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
 
public class AndroidFileBrowser extends ListActivity {
       
        private enum DISPLAYMODE{ ABSOLUTE, RELATIVE}
 
        private final DISPLAYMODE displayMode = DISPLAYMODE.ABSOLUTE;
        private List<String> directoryEntries = new ArrayList<String>();
        private File currentDirectory = new File("/");
 
        /** Called when the activity is first created. */
        @Override
        public void onCreate(Bundle icicle) {
                super.onCreate(icicle);
                // setContentView() gets called within the next line,
                // so we do not need it here.
                browseToRoot();
        }
       
        /**
         * This function browses to the
         * root-directory of the file-system.
         */
        private void browseToRoot() {
                browseTo(Environment.getRootDirectory());
    }
       
        /**
         * This function browses up one level
         * according to the field: currentDirectory
         */
        private void upOneLevel(){
                if(this.currentDirectory.getParent() != null)
                        this.browseTo(this.currentDirectory.getParentFile());
        }
       
        private void browseTo(final File aDirectory){
                if (aDirectory.isDirectory()){
                        this.currentDirectory = aDirectory;
                        fill(aDirectory.listFiles());
                }else{
                        OnClickListener okButtonListener = new OnClickListener(){
                                // @Override
                                public void onClick(DialogInterface arg0, int arg1) {
                                        Intent intent = new Intent();
                                        intent.putExtra("filename", aDirectory.getAbsolutePath());
                                        setResult(RESULT_OK, intent);
                                        finish();
                                }
                        };
                        OnClickListener cancelButtonListener = new OnClickListener(){
                                // @Override
                                public void onClick(DialogInterface arg0, int arg1) {
                                        // Do nothing
                                }
                        };
                        new AlertDialog.Builder(this)
                        .setTitle("Question")
                        .setMessage("Do you want to open that file?\n"+ aDirectory.getName())
                        .setPositiveButton("OK", okButtonListener)
                        .setNegativeButton("Cancel", cancelButtonListener)
                        .show();
                }
        }
 
        private void fill(File[] files) {
                this.directoryEntries.clear();
               
                // Add the "." and the ".." == 'Up one level'
                try {
                        Thread.sleep(10);
                } catch (InterruptedException e1) {
                        // TODO Auto-generated catch block
                        e1.printStackTrace();
                }
                this.directoryEntries.add(".");
               
                if(this.currentDirectory.getParent() != null)
                        this.directoryEntries.add("..");
               
                switch(this.displayMode){
                        case ABSOLUTE:
                                for (File file : files){
                                        this.directoryEntries.add(file.getPath());
                                }
                                break;
                        case RELATIVE: // On relative Mode, we have to add the current-path to the beginning
                                int currentPathStringLenght = this.currentDirectory.getAbsolutePath().length();
                                for (File file : files){
                                        this.directoryEntries.add(file.getAbsolutePath().substring(currentPathStringLenght));
                                }
                                break;
                }
               
                ArrayAdapter<String> directoryList = new ArrayAdapter<String>(this,
                                R.layout.file_row, this.directoryEntries);
               
                this.setListAdapter(directoryList);
        }
 
        @Override
        protected void onListItemClick(ListView l, View v, int position, long id) {
                String selectedFileString = this.directoryEntries.get(position);
                if (selectedFileString.equals(".")) {

                        // Refresh
                        this.browseTo(this.currentDirectory);
                } else if(selectedFileString.equals("..")){

                        this.upOneLevel();
                } else {
                        File clickedFile = null;
                        switch(this.displayMode){
                                case RELATIVE:
                                        clickedFile = new File(this.currentDirectory.getAbsolutePath()
                                                                                                + this.directoryEntries.get(position));
                                        break;
                                case ABSOLUTE:
                                        clickedFile = new File(this.directoryEntries.get(position));
                                        break;
                        }
                        if(clickedFile != null) {
                            this.browseTo(clickedFile);
                        }
                }
        }
}