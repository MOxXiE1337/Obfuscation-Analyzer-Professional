#pragma once
#include "oaui/Core/UI/Window.h"
#include "oaui/Core/UI/UI.h"

namespace oaui
{
	class DatabaseViewerWindow : public Window
	{
	private:
	public:
		DatabaseViewerWindow();
		void Render(UI* ui);
	};
}
