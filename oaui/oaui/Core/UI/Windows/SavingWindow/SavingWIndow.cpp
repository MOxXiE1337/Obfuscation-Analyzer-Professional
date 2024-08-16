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
        m_shouldExitProgram = false;
    }

    void SavingWindow::Render(UI* ui)
    {
        static bool save = true;

        HWND hwnd = FindWindowA("ImGui Platform", "Save to disk");
        if (hwnd)
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);


        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        ImGui::Begin("Save to disk", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove);

        if (!ImGui::IsWindowFocused())
        {
            PlaySoundA("C:\\Windows\\Media\\Windows background.wav", NULL, SND_ASYNC);
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
                State::GetInstance().Save(""); 
            
            State::GetInstance().Reset();
            
            
            if (m_openOpenFileDialog)
            {
                // prevent from choking GUI... (select file)                  
                Utils::ThreadExecutor([ui]()
                    {
                        std::string path{};
                        if (Utils::SelectFile(ui->GetHWND(), "Executable File (*.exe *.dll)\0*.exe;*.dll\0Database File (*.odb)\0*.odb\0\0", path))
                        {
                            State::GetInstance().LoadFile(path);
                        }
                    }, &State::GetInstance().IsLoadOrSaving());
                
                m_openOpenFileDialog = false;
            }

            
            if (m_loadDraggedFile)
            {
                State::GetInstance().LoadFile(m_draggedFilePath);
                // m_draggedFilePath.clear();
                m_loadDraggedFile = false;
            } 

            if (m_shouldExitProgram == true)
            {
                // To fix GUI log logical error                 
                Utils::ThreadExecutor executor(
                    [ui]() {
                    ui->Log("Exiting...");
                    SetTimer(ui->GetHWND(), 1, 800, ExitOnTimer);
                    },
                    &State::GetInstance().IsLoadOrSaving());

                m_isProgramExiting = true;
            }

            Close();
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