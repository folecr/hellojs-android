package spidermonkey;

import android.content.res.AssetManager;
import android.util.Log;

public class Bindings {
    static private final String LOGTAG = "org.spidermonkey.Bindings";

    public static StringBuilder getLibVersions() {
        StringBuilder content = new StringBuilder();
        content.append("Hello JavaSscript, SpiderMonkey, Android!\n\n");

        try {
            content.append("SpiderMonkey JavaScript VM Version = " + getJSVMVersion() + "\n");
        } catch (Throwable t) {
            Log.d(LOGTAG, "Exception : " + t);
            content.append("Error in SpiderMonkey JavaScript VM.\n");
        }

        try {
            content.append("Bindings Version = " + getBindingsVersion() + "\n");
        } catch (Throwable t) {
            Log.d(LOGTAG, "Exception : " + t);
            content.append("Error in SpiderMonkey JavaScript bindings.\n");
        }

        return content;
    }

    public static void executeJS(AssetManager assetmanager,
                                 String relativePath) {
        Log.d(LOGTAG, "executeJS assets/" + relativePath);

        runJSFromAssets(assetmanager, relativePath);
    }

    private static native String getJSVMVersion();
    private static native void   jsvmDiagnostics();
    private static native void   runJSFromAssets(AssetManager a,
                                                 String s);

    private static native String getBindingsVersion();
    private static native void   bindingsDiagnostics();
}
