//
// Created by letha on 9/4/2021.
//

#ifndef IMGUIANDROID_FUNCTIONPOINTERS_H
#define IMGUIANDROID_FUNCTIONPOINTERS_H
using namespace BNM::UNITY_STRUCTS;
namespace Pointers
{

    void * (*GameObject_get_transform)(void *instance);

    Vector3 (*Transform_get_position)(void *instance);

    Vector3 (*Camera_WorldToScreenPoint)(void *instance, Vector3 worldPosition);

    void *(*Camera_get_main)();

    //DWORD PlayerScript_correctPlayerPos;
    void LoadPointers()
    {
        GameObject_get_transform =
                *(void *(*)(void *)) OBFUSCATE_BYNAME_METHOD("UnityEngine", "GameObject",
                                                             "get_transform", 0);
        Transform_get_position =
                *(Vector3 (*)(void *)) OBFUSCATE_BYNAME_METHOD("UnityEngine", "Transform",
                                                               "get_position", 0);
        Camera_WorldToScreenPoint =
                *(Vector3 (*)(void *, Vector3)) OBFUSCATE_BYNAME_METHOD("UnityEngine", "Camera",
                                                                        "WorldToScreenPoint", 1);
        Camera_get_main =
                *(void *(*)()) OBFUSCATE_BYNAME_METHOD("UnityEngine", "Camera",
                                                                        "get_main", 0);

        //PlayerScript_correctPlayerPos = OBFUSCATE_BYNAME_FIELD("", "PlayerScript", "position");
    }
}
#endif IMGUIANDROID_FUNCTIONPOINTERS_H
