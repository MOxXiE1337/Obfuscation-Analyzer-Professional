#include "SavingWindow.h"
#include "oaui/Core/State/State.h"
#include "oaui/Utils/Utils.h"


void ExitOnTimer(HWND hwnd, UINT arg1, UINT_PTR nIDEvent, DWORD arg3)
{
    DestroyWindow(hwnd);
}

namespace oaui
{
    SavingWindow::SavingWindow()
    {
        // Intiialize options
        SetOptionValue(Constants::SAVINGWINDOW_OPEN_NEW_FILE, false);
        SetOptionValue(Constants::SAVINGWINDOW_SHOULD_EXIT, false);
        SetOptionValue(Constants::SAVINGWINDOW_EXITING, false);
        SetOptionValue(Constants::SAVINGWINDOW_LOAD_DRAGGED_FILE, true);
        SetOptionValue(Constants::SAVINGWINDOW_DRAGGED_FILE_PATH, std::string(""));
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

            
            if (GetOptionValue<bool>(Constants::SAVINGWINDOW_OPEN_NEW_FILE))
            {
                std::string path{};
                if (Utils::SelectFile(ui->GetHWND(), "Exe\0*.exe\0Dll\0*.dll\0Database File\0*.odb", path))
                {
                    ui->GetState()->LoadFile(path);
                }
                SetOptionValue(Constants::SAVINGWINDOW_OPEN_NEW_FILE, false);
            }

            
            if (GetOptionValue<bool>(Constants::SAVINGWINDOW_LOAD_DRAGGED_FILE))
            {
                ui->GetState()->LoadFile(GetOptionValue<std::string>(Constants::SAVINGWINDOW_DRAGGED_FILE_PATH));
                // SetOptionValue(Constants::SAVINGWINDOW_DRAGGED_FILE_PATH, std::string(""));
                SetOptionValue<bool>(Constants::SAVINGWINDOW_LOAD_DRAGGED_FILE, false);
            } 

            if (GetOptionValue<bool>(Constants::SAVINGWINDOW_SHOULD_EXIT))
            {
                //Log("Exiting...");
                SetOptionValue(Constants::SAVINGWINDOW_EXITING, true);
                SetTimer(ui->GetHWND(), 1, 1500, ExitOnTimer);
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            Close();
            SetOptionValue<bool>(Constants::SAVINGWINDOW_SHOULD_EXIT, false);
        }

        ImGui::End();
    }

}