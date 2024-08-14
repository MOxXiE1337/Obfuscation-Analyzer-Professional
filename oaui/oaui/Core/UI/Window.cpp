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
	bool Window::IsShowed()
	{
		return m_show;
	}
	bool* Window::GetShowPointer()
	{
		return &m_show;
	}
}

