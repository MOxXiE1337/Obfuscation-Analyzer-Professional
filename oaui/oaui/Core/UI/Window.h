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

		void Show();
		void Close();
		bool IsShowed();
		bool* GetShowPointer();
		virtual void Render(class UI* ui) = 0;
	};
}
