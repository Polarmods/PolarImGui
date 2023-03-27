#pragma once
#include "../ByNameModding/BNM.hpp"

using namespace BNM::UNITY_STRUCTS;
using namespace BNM::MONO_STRUCTS;
using namespace BNM;

namespace Unity
{
    namespace Screen
    {
        static BNM::LoadClass Screen;

        static BNM::Method<int> Height;

        static bool is_done = false;

        void Setup()
        {
            Screen = BNM::LoadClass("UnityEngine", "Screen");
            Height = Screen.GetMethodByName("get_height", 0);
            is_done = true;
        }
    }
}