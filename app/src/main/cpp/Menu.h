#ifndef MENU
#define MENU

#include "Misc/ESP.h"
#include "Unity/Screen.h"

namespace Menu
{

    ImVec4 color = ImVec4(1, 1, 1, 1);

    void DrawMenu()
    {
        static bool show_demo_window = true;
        static bool show_another_window = false;
        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }
    void DrawImGui()
    {
        if (init && Unity::Screen::Height.get())
        {
            ImGuiIO &io = ImGui::GetIO();
            static bool WantTextInputLast = false;
//            if (io.WantTextInput && !WantTextInputLast)
//                displayKeyboard(true);
//            WantTextInputLast = io.WantTextInput;
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplAndroid_NewFrame(Unity::Screen::Width.get(), Unity::Screen::Height.get());;
            ImGui::NewFrame();
            DrawMenu();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            io.KeysDown[io.KeyMap[ImGuiKey_UpArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_DownArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_LeftArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_RightArrow]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Tab]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Enter]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_PageUp]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_PageDown]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Escape]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Delete]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Home]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_End]] = false;
            io.KeysDown[io.KeyMap[ImGuiKey_Insert]] = false;
            ImGui::EndFrame();
        }
    }
}
#endif MENU