#include "Window.h"

namespace oaui
{
	void Window::Show()
	{
		m_show = true;
	}
	void Window::Close()
	{
		m_show = false;
	}
	bool Window::IsShowed() const
	{
		return m_show;
	}
}

