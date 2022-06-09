#ifndef JNIHOOKS
#define JNIHOOKS

jmethodID MotionEvent_getX;
jmethodID MotionEvent_getY;
jmethodID MotionEvent_getAction;
jmethodID KeyEvent_getUnicodeChar;
jmethodID KeyEvent_getMetaState;
jmethodID KeyEvent_getAction;
jmethodID KeyEvent_getKeyCode;
jboolean (*old_nativeInjectEvent)(JNIEnv *, jobject, jobject);
jboolean nativeInjectEvent(JNIEnv *env, jobject thiz, jobject inputEvent)
{
    if (init)
    {
        jclass MotionEventCls = env->FindClass(OBFUSCATE("android/view/MotionEvent"));
        jclass KeyEventCls = env->FindClass(OBFUSCATE("android/view/KeyEvent"));
        if (env->IsInstanceOf(inputEvent, MotionEventCls))
        {
            if (!MotionEvent_getX)
                MotionEvent_getX = env->GetMethodID(MotionEventCls, OBFUSCATE("getX"),
                                                    OBFUSCATE("()F"));
            if (!MotionEvent_getY)
                MotionEvent_getY = env->GetMethodID(MotionEventCls, OBFUSCATE("getY"),
                                                    OBFUSCATE("()F"));
            if (!MotionEvent_getAction)
                MotionEvent_getAction = env->GetMethodID(MotionEventCls, OBFUSCATE("getAction"),
                                                         OBFUSCATE("()I"));
            ImGuiIO &io = ImGui::GetIO();
            auto x = env->CallFloatMethod(inputEvent, MotionEvent_getX);
            auto y = env->CallFloatMethod(inputEvent, MotionEvent_getY);
            auto action = env->CallIntMethod(inputEvent,
                                            MotionEvent_getAction);
            LOGD("X:%f\nY:%f\nAction:%i", x, y, action);
            ImGui_ImplAndroid_HandleInputEvent(x,
                                               y,
                                               action);
            if (io.WantCaptureMouse)
                return true;
        } else if (env->IsInstanceOf(inputEvent, KeyEventCls))
        {
            if (!KeyEvent_getAction)
                KeyEvent_getAction = env->GetMethodID(KeyEventCls, OBFUSCATE("getAction"),
                                                      OBFUSCATE("()I"));
            if (env->CallIntMethod(inputEvent, KeyEvent_getAction) == 0)
            {
                if (!KeyEvent_getKeyCode)
                    KeyEvent_getKeyCode = env->GetMethodID(KeyEventCls, OBFUSCATE("getKeyCode"),
                                                           OBFUSCATE("()I"));
                if (!KeyEvent_getUnicodeChar)
                    KeyEvent_getUnicodeChar = env->GetMethodID(KeyEventCls,
                                                               OBFUSCATE("getUnicodeChar"),
                                                               OBFUSCATE("(I)I"));
                if (!KeyEvent_getMetaState)
                    KeyEvent_getMetaState = env->GetMethodID(KeyEventCls, OBFUSCATE("getMetaState"),
                                                             OBFUSCATE("()I"));
                ImGuiIO &io = ImGui::GetIO();
                int KeyCode = env->CallIntMethod(inputEvent, KeyEvent_getKeyCode);
                switch (KeyCode)
                {
                    case 19:
                        io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = true;
                        break;
                    case 20:
                        io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = true;
                        break;
                    case 21:
                        io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = true;
                        break;
                    case 22:
                        io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = true;
                        break;
                    case 61:
                        io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = true;
                        break;
                    case 66:
                        io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = true;
                        break;
                    case 67:
                        io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = true;;
                        break;
                    case 92:
                        io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = true;
                        break;
                    case 93:
                        io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = true;
                        break;
                    case 111:
                        io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = true;
                        break;
                    case 112:
                        io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = true;
                        break;
                    case 122:
                        io.KeysDown[io.KeyMap[ImGuiKey_Home]] = true;
                        break;
                    case 123:
                        io.KeysDown[io.KeyMap[ImGuiKey_End]] = true;
                        break;
                    case 124:
                        io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = true;
                        break;
                    default:
                        io.AddInputCharacter(env->CallIntMethod(inputEvent, KeyEvent_getUnicodeChar,
                                                                env->CallIntMethod(inputEvent,
                                                                                   KeyEvent_getMetaState)));
                        break;
                }
            }
        }
    }
    return old_nativeInjectEvent(env, thiz, inputEvent);
}
jint (*old_RegisterNatives)(JNIEnv*, jclass, const JNINativeMethod*, jint);
jint hook_RegisterNatives(JNIEnv* env, jclass klazz, const JNINativeMethod* methods, jint methodcount)
{
    for (int i = 0; i < methodcount; ++i)
    {
        auto method = methods[i];
        if (strcmp(method.name, OBFUSCATE("nativeInjectEvent")) == 0)
        {
            hook((void *) method.fnPtr, (void *) nativeInjectEvent,
                 (void **) &old_nativeInjectEvent);
        }
    }
    return old_RegisterNatives(env, klazz, methods, methodcount);
}

#endif JNIHOOKS