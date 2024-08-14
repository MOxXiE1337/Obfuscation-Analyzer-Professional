#pragma once
#include "oaui/Core/UI/Window.h"
#include "oaui/Core/UI/UI.h"

#define OAUI_OUTPUT_WINDOW_MAX_SINGLE_LOG_SIZE 512
#define OAUI_OUTPUT_WINDOW_MAX_LOGS 4096

namespace oaui
{
	class OutputWindow : public Window
	{
	private:
		std::mutex                                 m_lock;
		std::list<std::pair<ImColor, std::string>> m_logs;
	public:
		OutputWindow();
		
		void OutputMessage(const ImColor& color, const char* text ...);
		void OutputMessage(const ImColor& color, const char* text, va_list ap);
		void ClearMessages();

		void Render(UI* ui);
	};
}

