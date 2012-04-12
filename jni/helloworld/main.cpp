#include <jni.h>
#include <android/log.h>
#include <JNI_spidermonkey_bindings.h>

#define  LOG_TAG    "hellojs-main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C"
{
    
jint JNI_OnLoad (JavaVM *vm, void *reserved) {
    LOGD("JNI_OnLoad vm : 0x%X, reserved : 0x%X", vm, reserved);

    JNIEnv* env;
    vm->GetEnv((void**)&env, JNI_VERSION_1_4);

    JNI_spidermonkey_bindings::registernatives(env);

    LOGD("return JNI_VERSION_1_4");
	return JNI_VERSION_1_4;
}

}
