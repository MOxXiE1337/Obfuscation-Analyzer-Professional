#include "SavingWindow.h"
#include "oaui/Core/State/State.h"
#include "oaui/Utils/Utils.h"


void ExitOnTimer(HWND hwnd, UINT arg1, UINT_PTR nIDEvent, DWORD arg3)
{
    DestroyWindow(hwnd);
}

namespace oaui
{
    SavingWindow::SavingWindow() : m_draggedFilePath{}
    {
        m_openOpenFileDialog = false;
        m_shouldExitProgram = false;
        m_isProgramExiting = false;
        m_loadDraggedFile = false;
    }

    void SavingWindow::OpenOpenFileDialog()
    {
        m_openOpenFileDialog = true;
    }

    void SavingWindow::CloseOpenFileDialog()
    {
        m_openOpenFileDialog = false;
    }

    void SavingWindow::ExitProgram()
    {
        m_shouldExitProgram = true;
    }

    bool SavingWindow::IsProgramExiting()
    {
        return m_isProgramExiting;
    }

    void SavingWindow::LoadDraggedFile(const std::string& path)
    {
        m_loadDraggedFile = true;
        m_draggedFilePath = path;
    }

    void SavingWindow::Render(UI* ui)
    {
        static bool save = true;

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        ImGui::Begin("Save to database", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove);

        if (!ImGui::IsWindowFocused())
        {
            PlaySoundA("SystemAsterisk", NULL, SND_ASYNC);
            ImGui::SetWindowFocus();
        }

        ImGui::Text("Obfuscation Analyzer Professional will\nsave the database into disk");

        ImGui::Separator();

        if (ImGui::RadioButton("Save the database", save))
            save = true;
        if (ImGui::RadioButton("Don't save the database", !save))
            save = false;

        ImGui::Separator();

        if (ImGui::Button("OK"))
        {
            if (save)
                ui->GetState()->Save("", true);
            else
                ui->GetState()->Reset();
            
            Close();

            
            if (m_openOpenFileDialog)
            {
                std::string path{};
                if (Utils::SelectFile(ui->GetHWND(), "Exe\0*.exe\0Dll\0*.dll\0Database File\0*.odb", path))
                {
                    ui->GetState()->LoadFile(path);
                }
                m_openOpenFileDialog = false;
            }

            
            if (m_loadDraggedFile)
            {
                ui->GetState()->LoadFile(m_draggedFilePath);
                // m_draggedFilePath.clear();
                m_loadDraggedFile = false;
            } 

            if (m_shouldExitProgram = true)
            {
                ui->Log("Exiting...");
                m_isProgramExiting = true;
                SetTimer(ui->GetHWND(), 1, 1000, ExitOnTimer);
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            Close();
            m_shouldExitProgram = false;
        }

        ImGui::End();
    }

}