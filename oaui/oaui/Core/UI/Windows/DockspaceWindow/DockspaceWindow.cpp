#include "DockspaceWindow.h"

namespace oaui
{
    DockspaceWindow::DockspaceWindow()
    {
        m_show = true;
    }

    void DockspaceWindow::Render(UI* ui)
	{
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("UI.DockspaceWindow", nullptr, window_flags);



        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("UI.Dockspace");
        ImGui::DockSpace(dockspace_id);

        ImGui::End();

	}
}

