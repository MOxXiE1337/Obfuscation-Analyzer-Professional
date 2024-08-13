#include "UI.h"


namespace oaui
{
	void UI::LogWindow()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		if (!m_showLogWindow)
			return;

		ImGui::Begin(u8"\uE81E Output", &m_showLogWindow, ImGuiWindowFlags_NoCollapse);

		m_logMutex.lock();

		for (auto& i : m_logs)
		{
			ImGui::TextColored(i.first, i.second.c_str());
		}

		m_logMutex.unlock();

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Button("Clear logs"))
			{
				ClearLogs();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}