#pragma once
#include "oaui/Core/UI/Window.h"
#include "oaui/Core/UI/UI.h"


namespace oaui
{
	class DockspaceWindow : public Window
	{
	public:
		DockspaceWindow();
		void Render(UI* ui);
	};
}
