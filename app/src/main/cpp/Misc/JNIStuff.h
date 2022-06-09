#ifndef JNISTUFF
#define JNISTUFF
JavaVM *jvm;
jclass UnityPlayer_cls;
jfieldID UnityPlayer_CurrentActivity_fid;
JNIEnv* getEnv() {
    JNIEnv *env;
    int status = jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
    if(status < 0) {
        status = jvm->AttachCurrentThread(&env, NULL);
        if(status < 0) {
            LOGE(OBFUSCATE("Error Getting JNI"), 1);
            return nullptr;
        }
    }
    return env;
}
jobject getGlobalContext(JNIEnv *env)
{
    jclass activityThread = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, OBFUSCATE("currentActivityThread"), OBFUSCATE("()Landroid/app/ActivityThread;"));
    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
    jmethodID getApplication = env->GetMethodID(activityThread, OBFUSCATE("getApplication"), OBFUSCATE("()Landroid/app/Application;"));
    jobject context = env->CallObjectMethod(at, getApplication);
    return context;
}
void displayKeyboard(bool pShow) {
    JNIEnv *env = getEnv();
    jclass ctx = env->FindClass(OBFUSCATE("android/content/Context"));
    jfieldID fid = env->GetStaticFieldID(ctx, OBFUSCATE("INPUT_METHOD_SERVICE"), OBFUSCATE("Ljava/lang/String;"));
    jmethodID mid = env->GetMethodID(ctx, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
    jobject context = env->GetStaticObjectField(UnityPlayer_cls, UnityPlayer_CurrentActivity_fid);
    jobject InputManObj = env->CallObjectMethod(context, mid, (jstring) env->GetStaticObjectField(ctx, fid));
    jclass ClassInputMethodManager = env->FindClass(OBFUSCATE("android/view/inputmethod/InputMethodManager"));
    jmethodID toggleSoftInputId = env->GetMethodID(ClassInputMethodManager, OBFUSCATE("toggleSoftInput"), OBFUSCATE("(II)V"));
    if (pShow) {
        env->CallVoidMethod(InputManObj, toggleSoftInputId, 2, 0);
    } else {
        env->CallVoidMethod(InputManObj, toggleSoftInputId, 0, 0);
    }
}
#endif JNISTUFF