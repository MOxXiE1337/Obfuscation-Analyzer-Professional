#pragma once
#include "oaui/Core/UI/Window.h"
#include "oaui/Core/UI/UI.h"


namespace oaui
{
	// The saving window only appears when you are opening a file with file loaded, or exiting with file loaded
	class SavingWindow : public Window
	{
	private:
	public:
		SavingWindow();

		void Render(UI* ui);
	};
}
