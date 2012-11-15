#include "jsbindings.h"
#include <string>

#include <android/log.h>

#include <jsapi.h>

namespace jsbindings {

#define  LOG_TAG    "jsbindings.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

    static const std::string VERSION = "Unknown Version";

    const char* getBindingsVersion (void) {
        return VERSION.c_str();
    }

    void finalize(JSFreeOp *freeOp, JSObject *obj) {
        return;
    }

    // The class of the global object.
    static JSClass global_class =
        {"global",
         JSCLASS_GLOBAL_FLAGS,
         JS_PropertyStub,
         JS_PropertyStub,
         JS_PropertyStub,
         JS_StrictPropertyStub,
         JS_EnumerateStub,
         JS_ResolveStub,
         JS_ConvertStub,
         finalize,
         JSCLASS_NO_OPTIONAL_MEMBERS};

    // The error reporter callback.
    static void reportError(JSContext *cx,
                            const char *message,
                            JSErrorReport *report) {
        LOGD("%s:%u:%s\n",
             report->filename ? report->filename : "<no filename>",
             (unsigned int) report->lineno,
             message);
    }

    int runJS(char* script) {
        LOGD("runJS");
        // LOGD("script :\n%s", script);

        /* Create a JS runtime. */
        JSRuntime *rt = JS_NewRuntime(8L * 1024L * 1024L);
        if (rt == NULL) {
            LOGD("(rt == NULL)");
            return 1;
        }

        /* Create a context. */
        JSContext *cx = JS_NewContext(rt, 8192);
        if (cx == NULL) {
            LOGD("(cx == NULL)");
            return 1;
        }

        JS_SetOptions(cx, JSOPTION_TYPE_INFERENCE);
        JS_SetVersion(cx, JSVERSION_LATEST);
        JS_SetOptions(cx, JS_GetOptions(cx) & ~JSOPTION_METHODJIT);
        JS_SetOptions(cx, JS_GetOptions(cx) & ~JSOPTION_METHODJIT_ALWAYS);

        JS_SetErrorReporter(cx, jsbindings::reportError);

        /* Create the global object in a new compartment. */
        JSObject* global = JS_NewGlobalObject(cx, &global_class, NULL);
        if (!global) {
            LOGD("(global == NULL)");
            return 1;
        }

        {
            // Enter the compartment of global... not strictly necessary
            // ... but test it out anyway
            JSAutoCompartment ac(cx, global);

            // Populate the global object with the standard globals,
            // like Object and Array.
            if (!JS_InitStandardClasses(cx, global)) {
                LOGD("(!JS_InitStandardClasses(cx, global))");
                return 1;
            }

            const char *filename = NULL;
            int lineno = 0;  
  
            jsval rval;
            JSBool evaluatedOK = JS_EvaluateScript(cx, global,
                                                   script, strlen(script),  
                                                   filename, lineno, &rval);  

            if (JS_FALSE == evaluatedOK) {
                LOGD("evaluatedOK == JS_FALSE)");
                // return 1;
            } else {
                if (JSVAL_IS_NULL(rval)) {
                    LOGD("rval : (JSVAL_IS_NULL(rval)");
                    // return 1;
                } else if ((JSVAL_IS_BOOLEAN(rval)) &&
                           (JS_FALSE == (JSVAL_TO_BOOLEAN(rval)))) {
                    LOGD("rval : (return value is JS_FALSE");
                    // return 1;
                } else if (JSVAL_IS_STRING(rval)) {
                    JSString *str = JS_ValueToString(cx, rval);  
                    if (NULL == str) {
                        LOGD("rval : return string is NULL");
                    } else {
                        LOGD("rval : return string =\n%s\n", JS_EncodeString(cx, str));
                    }
                } else if (JSVAL_IS_NUMBER(rval)) {
                    double number;
                    if (JS_FALSE == JS_ValueToNumber(cx, rval, &number)) {
                        LOGD("rval : return number could not be converted");
                    } else {
                        LOGD("rval : return number =\n%f", number);
                    }
                }
            }

        } // Leave the auto compartment

        // Cleanup
        JS_DestroyContext(cx);
        JS_DestroyRuntime(rt);
        JS_ShutDown();

        LOGD("runJS done.");
        return 0;
    }

    void bindingsDiagnostics (void) {
    }
}
