package com.example.spidermonkey.hellojs;

import android.app.Activity;
import android.content.res.AssetManager;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import spidermonkey.Bindings;

public class HelloJS extends Activity {
    static private final String LOGTAG = "HelloJS";

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(LOGTAG, "onCreate");

        setContentView(spidermonkey.hellojs.R.layout.mainmenu);

        LinearLayout linearlayout =
            (LinearLayout) findViewById(spidermonkey.hellojs.R.id.text_content);

        addVersionStringsToLinearLayout(linearlayout);
    }

    private void addVersionStringsToLinearLayout(LinearLayout linearlayout) {
        TextView tv = new TextView(this);
        tv.setText(Bindings.getLibVersions());
        linearlayout.addView(tv);
    }

    public void launchScriptsActivity(View v) {
        Log.d(LOGTAG, "launching AssetsScripts...");
        Intent intent = new Intent(this, AssetsScripts.class);
        startActivity(intent);
    }

    static {
        System.loadLibrary("game");
    }
}
