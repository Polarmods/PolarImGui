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

            if (index == 0)
            {
                ImGuiIO &io = ImGui::GetIO();
                float x = _touch.m_Position.x;
                float y = static_cast<float>(std::round(Unity::Screen::Height())) - _touch.m_Position.y;

                if (_touch.m_Phase == TouchPhase::Began)
                {
                    io.AddMousePosEvent(x,y);
                    io.AddMouseButtonEvent(0, Unity::Input::GetMouseButtonDown(0));
                }
                if (_touch.m_Phase == TouchPhase::Moved)
                {
                    io.AddMousePosEvent(x,y);
                }
                if (_touch.m_Phase == TouchPhase::Ended)
                {
                    io.AddMouseButtonEvent(0, Unity::Input::GetMouseButtonDown(0));
                    io.AddMouseButtonEvent(1, Unity::Input::GetMouseButtonDown(1));
                    io.AddMouseButtonEvent(2, Unity::Input::GetMouseButtonDown(3));
                }

                if (io.WantCaptureMouse)
                    return old_FakeGetTouch(-1);
            }

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