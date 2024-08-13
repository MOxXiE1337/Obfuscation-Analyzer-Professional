#include "UI.h"

#include "imgui.h"

#include "Core/Loader/Loader.h"

void ExitOnTimer(HWND hwnd, UINT arg1, UINT_PTR nIDEvent, DWORD arg3)
{
    DestroyWindow(hwnd);
}

namespace oaui
{
    void UI::SaveWindow()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        if (!m_showSaveWindow)
            return;

        ImGuiContext* context = ImGui::GetCurrentContext();

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        ImGui::Begin(u8"Save to database", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove);

        if (!ImGui::IsWindowFocused())
        {
            PlaySoundA("SystemAsterisk", NULL, SND_ASYNC);
            ImGui::SetWindowFocus();
        }

        ImGui::Text("Obfuscation Analyzer Professional will\nsave the data into database");

        ImGui::Separator();

        ImGui::RadioButton("Save the database", &m_shouldSave, 0);
        ImGui::RadioButton("Don't save the database", &m_shouldSave, 1);

        ImGui::Separator();

        if (ImGui::Button("OK"))
        {
            if (m_shouldSave == 0)
                Loader::GetInstance().Save("", true);
            else
                Loader::GetInstance().Unload();

            m_showSaveWindow = false;
            
            if (m_shouldOpenNewFile)
            {
                OpenFile();
                m_shouldOpenNewFile = false;
            }

            if (m_delayLoad)
            {
                Loader::GetInstance().LoadFile(m_delayLoadPath);
                m_delayLoadPath.clear();
                m_delayLoad = false;
            }

            if (m_shouldExit)
            {
                Log("Exiting...");
                m_isExiting = true;
                SetTimer(m_hwnd, 1, 1500, ExitOnTimer);
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            if(!m_shouldExit)
                Loader::GetInstance().Unload();

            m_showSaveWindow = false;
            m_shouldExit = false;
        }

        ImGui::End();
    }

}