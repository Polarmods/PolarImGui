#pragma once

#include "../ByNameModding/BNM.hpp"

using namespace BNM::UNITY_STRUCTS;
using namespace BNM::MONO_STRUCTS;
using namespace BNM;

namespace Unity
{
    namespace Input
    {
        static enum TouchPhase{
            Began,
            Moved,
            Stationary,
            Ended,
            Canceled
        };

        static enum TouchType
        {
            Direct,
            Indirect,
            Stylus
        };

        using namespace BNM::UNITY_STRUCTS;

        struct Touch{
            int m_FingerId{};
            Vector2 m_Position;
            Vector2 m_RawPosition;
            Vector2 m_PositionDelta;
            float m_TimeDelta{};
            int m_TapCount{};
            TouchPhase m_Phase{};
            TouchType m_Type{};
            float m_Pressure{};
            float m_maximumPossiblePressure{};
            float m_Radius{};
            float m_RadiusVariance{};
            float m_AltitudeAngle{};
            float m_AzimuthAngle{};
        };


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

            // _touch.m_TapCount > 1 u can remove this if u just want single click;
            if (index == 0 && _touch.m_TapCount > 1)
            {
                int x = static_cast<float>(_touch.m_Position.x);
                float y = static_cast<float>(std::round(Unity::Screen::Height.get())) - _touch.m_Position.y;
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