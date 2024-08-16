#pragma once
#include "oaui/oaui.h"

namespace oaui
{

	class Window
	{
	protected:
		bool        m_show;
	public:
		Window(bool show = false) : m_show(show) {}
		virtual ~Window() = default;

		void Show();
		void Close();
		bool IsShowed() const;
		virtual void Render(class UI* ui) = 0;
	};
}
