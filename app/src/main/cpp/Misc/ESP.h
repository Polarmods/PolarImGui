#ifndef ImGuiAndroid_ESP
#define ImGuiAndroid_ESP

#include "../ImGui/imgui_internal.h"

namespace ESP {
    void DrawLine(ImVec2 start, ImVec2 end, ImVec4 color) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            background->AddLine(start, end, ImColor(color.x,color.y,color.z,color.w));
        }
    }
    void DrawBox(ImVec4 rect, ImVec4 color) {
        ImVec2 v1(rect.x, rect.y);
        ImVec2 v2(rect.x + rect.z, rect.y);
        ImVec2 v3(rect.x + rect.z, rect.y + rect.w);
        ImVec2 v4(rect.x, rect.y + rect.w);

        DrawLine(v1, v2, color);
        DrawLine(v2, v3, color);
        DrawLine(v3, v4, color);
        DrawLine(v4, v1, color);
    }
    void DrawCircle(float X, float Y, float radius, bool filled, ImVec4 color) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            if(filled) {
                background->AddCircleFilled(ImVec2(X, Y), radius, ImColor(color.x,color.y,color.z,color.w));
            } else {
                background->AddCircle(ImVec2(X, Y), radius, ImColor(color.x,color.y,color.z,color.w));
            }
        }
    }
    void DrawText(ImVec2 position, ImVec4 color, const char *text) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            background->AddText(NULL, 25.0f, position, ImColor(color.x,color.y,color.z,color.w), text);
        }
    }
}

#endif ImGuiAndroid_ESP