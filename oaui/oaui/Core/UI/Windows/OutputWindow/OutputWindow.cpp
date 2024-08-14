#include "OutputWindow.h"

namespace oaui
{
	OutputWindow::OutputWindow() : Window(true)
	{
	}
	void OutputWindow::OutputMessage(const ImColor& color, const char* text ...)
	{
		va_list ap;
		va_start(ap, text);
		OutputMessage(color, text, ap);
		va_end(ap);
	}
	void OutputWindow::OutputMessage(const ImColor& color, const char* text, va_list ap)
	{
		static char buffer[OAUI_OUTPUT_WINDOW_MAX_SINGLE_LOG_SIZE] = { 0 };
		std::lock_guard<std::mutex> guard{ m_lock };
		vsprintf_s(buffer, OAUI_OUTPUT_WINDOW_MAX_SINGLE_LOG_SIZE, text, ap);
		if (m_logs.size() >= OAUI_OUTPUT_WINDOW_MAX_LOGS)
			m_logs.pop_front();
		m_logs.push_back({ color,buffer });
	}
	void OutputWindow::ClearMessages()
	{
		std::lock_guard<std::mutex> guard{ m_lock };
		m_logs.clear();
	}
	void OutputWindow::Render(UI* ui)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		static ImGuiTextFilter filter;
		std::lock_guard<std::mutex> guard{ m_lock };

		ImGui::Begin(u8"\uE81E Output", &m_show, ImGuiWindowFlags_NoCollapse);

		if (ImGui::BeginPopupContextWindow())
		{
			ImGui::PushStyleColor(ImGuiCol_Border, { 0,0,0,0 });
			if (ImGui::Button("Close"))
			{
				Close();
				ImGui::CloseCurrentPopup();
			}
			ImGui::PopStyleColor();
			ImGui::EndPopup();
		}

		if (ImGui::Button("Clear"))
		{
			m_logs.clear(); 
		}
		
		ImGui::SameLine();
		filter.Draw("Filter", ImGui::GetWindowSize().x - style.WindowPadding.x - style.FramePadding.x - ImGui::GetCursorPosX() - ImGui::CalcTextSize("Filter").x);

		ImGui::BeginChild("##Messages", { 0,0 }, ImGuiChildFlags_Border);

		if (ImGui::BeginPopupContextWindow())
		{
			ImGui::PushStyleColor(ImGuiCol_Border, { 0,0,0,0 });
			if (ImGui::Button("Clear"))
			{
				m_logs.clear();
				ImGui::CloseCurrentPopup();
			}
			ImGui::PopStyleColor();
			ImGui::EndPopup();
		}

		for (auto& i : m_logs)
		{
			if (filter.PassFilter(i.second.c_str()))
				ImGui::TextColored(i.first, i.second.c_str());
		}
		ImGui::EndChild();


		ImGui::End();
	}
}

