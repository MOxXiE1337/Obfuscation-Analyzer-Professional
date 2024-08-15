#include "MainMenuBar.h"

#include "oaui/Core/State/State.h"
#include "oaui/Utils/Utils.h"

#include "oaui/Core/UI/Windows/SavingWindow/SavingWindow.h"

namespace oaui
{
    void MainMenuBar::Render(UI* ui)
    {
        State* state = ui->GetState();
        oacore::IAnalyzer* analyzer = state->GetAnalyzer();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem(u8"      New instace"))
                {
                    CHAR processName[MAX_PATH] = { 0 };
                    STARTUPINFOA startInfo = { 0 };
                    PROCESS_INFORMATION pinfo = { 0 };
                    startInfo.cb = sizeof(STARTUPINFO);

                    GetModuleFileNameA(NULL, processName, MAX_PATH);
                    CreateProcessA(processName, (LPSTR)"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startInfo, &pinfo);

                    CloseHandle(pinfo.hProcess);
                    CloseHandle(pinfo.hThread);
                }
                ImGui::Separator();

                if (ImGui::MenuItem(u8"\uE804 Open"))
                {

                    if (analyzer->IsLoaded())
                    {
                        SavingWindow* saveWindow = dynamic_cast<SavingWindow*>(ui->GetWindow(WINDOW_SAVING_WINDOW));
                        saveWindow->Show();
                        saveWindow->OpenOpenFileDialog();
                    }
                    else
                    {
                        std::string path{};
                        if (Utils::SelectFile(ui->GetHWND(), "Executable File (*.exe *.dll)\0*.exe;*.dll\0Database File (*.odb)\0*.odb\0\0", path))
                        {
                            ui->GetState()->LoadFile(path);
                        }
                    }
                }
                /*
                if (ImGui::MenuItem(u8"\uE856 Save", nullptr, nullptr, Loader::GetInstance().IsLoaded()))
                {
                    Loader::GetInstance().Save();
                }
                if (ImGui::MenuItem(u8"      Save as...", nullptr, nullptr, Loader::GetInstance().IsLoaded()))
                {
                    std::string path = "";

                    if (SelectFile("Database File(*.odb)\0*.odb\0", path, OFN_PATHMUSTEXIST | OFN_EXPLORER))
                    {
                        if (path.find(".odb") == std::string::npos)
                            path += ".odb";
                        Loader::GetInstance().Save(path);
                    }
                }
                */
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                
                if (ImGui::BeginMenu("Open subviews"))
                {
                    /*
                    if (ImGui::MenuItem(u8"\uE78C Sections", nullptr, m_showSectionsWindow, Loader::GetInstance().IsLoaded()))
                    {
                        m_showSectionsWindow = true;
                    }
                    ImGui::Separator(); */

                    if (ImGui::MenuItem(u8"\uE81E Output", nullptr, ui->GetWindow(WINDOW_OUTPUT_WINDOW)->IsShowed()))
                    {
                        ui->GetWindow(WINDOW_OUTPUT_WINDOW)->Show();
                    }

                    ImGui::Separator();

                    
                    if (ImGui::MenuItem(u8"\uE620 Database notepad", nullptr, ui->GetWindow(WINDOW_NOTEPAD_WINDOW)->IsShowed(), analyzer->IsLoaded()))
                    {
                        ui->GetWindow(WINDOW_NOTEPAD_WINDOW)->Show();
                    }
                    ImGui::EndMenu(); 
                }
                

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Options"))
            {
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }
}

