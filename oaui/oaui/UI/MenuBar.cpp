#include "UI.h"

#include "imgui.h"

#include "Core/Loader/Loader.h"


namespace oaui
{

	void UI::MenuBar()
	{

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem(u8"      New instace"))
                {
                    CHAR processName[MAX_PATH] = { 0 };
                    STARTUPINFOA startInfo;
                    PROCESS_INFORMATION pinfo;
                    memset(&startInfo, 0, sizeof(STARTUPINFO));
                    startInfo.cb = sizeof(STARTUPINFO);

                    GetModuleFileNameA(NULL, processName, MAX_PATH);
                    CreateProcessA(processName, (LPSTR)"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startInfo, &pinfo);
                }
                ImGui::Separator();
                if (ImGui::MenuItem(u8"\uE804 Open"))
                {
                    if (Loader::GetInstance().IsLoaded())
                    {
                        m_showSaveWindow = true;
                        m_shouldOpenNewFile = true;
                    }
                    else
                    {
                        OpenFile();
                    }
                }
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
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::BeginMenu("Open subviews"))
                {
                    if (ImGui::MenuItem(u8"\uE78C Sections", nullptr, m_showSectionsWindow, Loader::GetInstance().IsLoaded()))
                    {
                        m_showSectionsWindow = true;
                    }
                    ImGui::Separator();

                    if (ImGui::MenuItem(u8"\uE81E Output", nullptr, m_showLogWindow))
                    {
                        m_showLogWindow = true;
                    }
                    ImGui::Separator();
                    if (ImGui::MenuItem(u8"\uE620 Notepad", nullptr, m_showNotepadWindow, Loader::GetInstance().IsLoaded()))
                    {
                        m_showNotepadWindow = true;
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem(u8"\uE818 Settings"))
                {
                    m_showSettingsWindow = true;
                }
                ImGui::EndMenu();
            }

         

            ImGui::EndMainMenuBar();
        }
	}
}