#pragma once

#include "Unity.h"
#include "../ByNameModding/BNM.hpp"

using namespace BNM::UNITY_STRUCTS;
using namespace BNM::MONO_STRUCTS;
using namespace BNM;

namespace Unity
{
    namespace Input
    {
        static BNM::LoadClass Input;
        static BNM::Method<Touch> GetTouch;
        static BNM::Method<bool> GetMouseButtonDown;
        static bool is_done = false;

        Touch (*old_FakeGetTouch)(int index);

        Touch FakeGetTouch(int index)
        {
            Touch _touch = old_FakeGetTouch(index);

            if (!init)
                return _touch;

            ImGuiIO &io = ImGui::GetIO();

            if (index == 0)
            {
                float x = _touch.m_Position.x;
                float y = static_cast<float>(std::round(Unity::Screen::Height())) - _touch.m_Position.y;
                ImGui_ImplAndroid_HandleInputEvent(x, y, Unity::Input::GetMouseButtonDown(0));

            }

            if (io.WantCaptureMouse)
                return old_FakeGetTouch(-1);

            return _touch;
        }

        void Setup()
        {
            Input = BNM::LoadClass("UnityEngine", "Input");
            GetTouch = Input.GetMethodByName("GetTouch", 1);
            GetMouseButtonDown = Input.GetMethodByName("GetMouseButtonDown", 1);
            HOOK(GetTouch.GetOffset(), FakeGetTouch, old_FakeGetTouch);
            is_done = true;
        }
    }
}