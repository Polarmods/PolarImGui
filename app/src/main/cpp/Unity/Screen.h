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
        static BNM::Property<int> Height;
        static BNM::Property<int> Width;
        static bool is_done = false;

        void Setup()
        {
            Screen = BNM::LoadClass("UnityEngine", "Screen");
            Height = Screen.GetPropertyByName("height");
            Width = Screen.GetPropertyByName("width");
            is_done = true;
        }
    }
}