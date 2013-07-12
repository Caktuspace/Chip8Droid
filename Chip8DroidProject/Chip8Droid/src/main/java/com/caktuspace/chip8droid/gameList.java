package com.caktuspace.chip8droid;

import android.app.ActionBar;
import android.content.Intent;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Locale;

public class gameList extends FragmentActivity implements ActionBar.OnNavigationListener {

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link android.support.v4.app.FragmentPagerAdapter} derivative, which
     * will keep every loaded fragment in memory. If this becomes too memory
     * intensive, it may be best to switch to a
     * {@link android.support.v4.app.FragmentStatePagerAdapter}.
     */
    SectionsPagerAdapter mSectionsPagerAdapter;
    private String categGameList[];

    /**
     * The {@link ViewPager} that will host the section contents.
     */
    ViewPager mViewPager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.list_game);

        // Set up the action bar.
        final ActionBar actionBar = getActionBar();
        if (actionBar != null) {
            actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_LIST);
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        Resources res = getResources();
        AssetManager am = res.getAssets();
        String fileList[] = new String[0];
        try {
            fileList = am.list("chip8file");
        } catch (IOException e) {
            e.printStackTrace();
        }
        categGameList = new String[fileList.length + 1];
        categGameList[0] = "All";

        int j = 1;
        for (String aFileList : fileList) {
            categGameList[j] = aFileList;
            ++j;
        }
        // Create the adapter that will return a fragment for each of the three
        // primary sections of the app.
        mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());

        // Set up the ViewPager with the sections adapter.
        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mSectionsPagerAdapter);
        // When swiping between different sections, select the corresponding
        // tab. We can also use ActionBar.Tab#select() to do this if we have
        // a reference to the Tab.
        mViewPager.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
            @Override
            public void onPageSelected(int position) {
                if (actionBar != null) {
                    actionBar.setSelectedNavigationItem(position);
                }
            }
        });

        if (actionBar != null) {
            actionBar.setListNavigationCallbacks(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, categGameList), this);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.game_list, menu);
        return true;
    }

    @Override
    public boolean onNavigationItemSelected(int i, long l) {
        mViewPager.setCurrentItem(i);
        return true;
    }

    /**
     * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
     * one of the sections/tabs/pages.
     */
    public class SectionsPagerAdapter extends FragmentPagerAdapter {

        public SectionsPagerAdapter(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int position) {
            // getItem is called to instantiate the fragment for the given page.
            // Return a DummySectionFragment (defined as a static inner class
            // below) with the page number as its lone argument.
            Fragment fragment = new DummySectionFragment();
            Bundle args = new Bundle();
            args.putInt(DummySectionFragment.ARG_SECTION_NUMBER, position);
            fragment.setArguments(args);
            return fragment;
        }

        @Override
        public int getCount() {
            // Show 3 total pages.
            return categGameList.length;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            Locale l = Locale.getDefault();
            return categGameList[position].toUpperCase(l);
        }
    }

    /**
     * A dummy fragment representing a section of the app, but that simply
     * displays dummy text.
     */
    public static class DummySectionFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        public static final String ARG_SECTION_NUMBER = "section_number";
        private String categ;

        public DummySectionFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                 Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_game_list, container, false);
            ListView listView = (ListView) (rootView != null ? rootView.findViewById(R.id.listView) : null);
            Resources res = getResources();
            final AssetManager am = res.getAssets();
            int sectionNumber = getArguments().getInt(ARG_SECTION_NUMBER);
            if (sectionNumber == 0) {
//                try {
//                    for (String categName : am.list("chip8file")) {
//                        ArrayList list = new ArrayList();
//
//                        list.add()
//                    }
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
            }
            else {
                try {
                    categ = am.list("chip8file")[sectionNumber - 1];
                    ArrayAdapter<String> arrayAdapter =
                            new ArrayAdapter<String>(getActivity(),android.R.layout.simple_list_item_1,
                                    am.list("chip8file/" + categ));
                    if (listView != null) {
                        listView.setAdapter(arrayAdapter);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (listView != null) {
                listView.setOnItemClickListener(new ListView.OnItemClickListener() {
                    @Override
                    public void onItemClick(AdapterView<?> parent, View view, int position,
                                            long id) {

                        String item = ((TextView) view).getText().toString();
                        String filenameSrc = "chip8file/" + categ + "/" + item;
                        String filenameDst = Environment.getExternalStorageDirectory() + "/tmpGameSave.ch8";
                        try {
                            InputStream in = am.open(filenameSrc);
                            OutputStream out = new FileOutputStream(new File(filenameDst));

                            byte[] buf = new byte[1024];
                            int len;
                            while ((len = in.read(buf)) > 0) {
                                out.write(buf, 0, len);
                            }
                            in.close();
                            out.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        Intent intent = new Intent(getActivity(), Chip8_emulatorActivity.class);
                        intent.putExtra("filename", filenameDst);
                        startActivity(intent);
                    }
                });
            }
            // dummyTextView.setText(Integer.toString(getArguments().getInt(ARG_SECTION_NUMBER)));
            return rootView;
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                // app icon in action bar clicked; go home
                Intent intent = new Intent(this, MainActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                startActivity(intent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
