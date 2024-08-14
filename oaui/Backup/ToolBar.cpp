#include "UI.h"

#include "imgui.h"

#include "Core/Loader/Loader.h"

namespace oaui
{
    void UI::ToolBar()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::MenuItem(u8"\uE804"))
            {
                if (Loader::GetInstance().IsLoaded())
                {
                    m_showSaveWindow = true;
                    m_shouldSave = 0;
                    m_shouldOpenNewFile = true;
                }
                else
                {
                    OpenFile();
                }
            }
            if (ImGui::BeginItemTooltip())
            {
                ImGui::Text(" Open ");
                ImGui::EndTooltip();
            }

            if (ImGui::MenuItem(u8"\uE856", nullptr, nullptr, Loader::GetInstance().IsLoaded()))
            {
                Loader::GetInstance().Save();
            }
            if (ImGui::BeginItemTooltip())
            {
                ImGui::Text(" Save ");
                ImGui::EndTooltip();
            }

            ImGui::EndMenuBar();
        }
    }
}