#include "UI.h"

#include "imgui.h"

namespace oaui
{
    void UI::SettingsWindow()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        if (!m_showSettingsWindow)
            return;

        ImGuiContext* context = ImGui::GetCurrentContext();

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize({ 800,550 });

        ImGui::Begin(u8"\uE818 Settings", &m_showSettingsWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);

        if (!ImGui::IsWindowFocused())
        {
            PlaySoundA("SystemAsterisk", NULL, SND_ASYNC);
            ImGui::SetWindowFocus();
        }

        ImGui::BeginTabBar("##UI.Settings.Tab");

        if (ImGui::BeginTabItem("UI"))
        {
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Misc"))
        {
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();

       
        ImGui::Separator();

        ImGui::SetCursorPosX(ImGui::GetWindowSize().x - style.ItemSpacing.x - style.WindowPadding.x - 160);

        if (ImGui::Button("OK", { 80, 0 }))
        {
            
        }
        
        ImGui::SameLine();

        if (ImGui::Button("Cancel", {80,0}))
            m_showSettingsWindow = false;
            
        ImGui::End();
    }
   
}