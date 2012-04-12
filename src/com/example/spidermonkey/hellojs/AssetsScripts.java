package com.example.spidermonkey.hellojs;

import android.app.ListActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;

import spidermonkey.Bindings;

/**
 * A list where the data for the list
 * comes from an array of strings.
 * The array of strings are the files in the
 * "assets/js" folder
 */
public class AssetsScripts extends ListActivity {
    static private final String LOGTAG = "AssetsScripts";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(LOGTAG, "onCreate");

        // map an array of strings to TextViews
        setListAdapter(new ArrayAdapter<String>(this,
                                                android.R.layout.simple_list_item_1,
                                                scriptList()));

        ListView lv = getListView();
        lv.setTextFilterEnabled(true);

        lv.setOnItemClickListener(new OnItemClickListener() {
                public void onItemClick(AdapterView<?> parent, View view,
                                        int position, long id) {
                    CharSequence path = ((TextView) view).getText();

                    // When clicked, show a toast with the path
                    Toast.makeText(getApplicationContext(), path,
                                   Toast.LENGTH_SHORT).show();

                    // ... and run the script
                    Bindings.executeJS(getAssets(), "js/" + path.toString());
                }
            });
    }

    private String[] scriptList() {
        try {
            String[] scripts = getJSAssets();

            Log.d(LOGTAG, "Scripts :\n --- js/\n      |");
            for (String s: scripts) {
                Log.d(LOGTAG, "      +-- " + s);
            }

            return scripts;
        } catch (java.io.IOException ioe) {
            Log.d(LOGTAG, "Exception reading scripts from assets/js.\n" + ioe);
            return(new String[] {});
        }
    }

    private String[] getJSAssets() throws java.io.IOException {
        String[] assetList = getAssets().list("js");
        return assetList;
    }
}
