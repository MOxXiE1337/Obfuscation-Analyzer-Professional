#pragma once
#include "oaui/Core/UI/MenuBar.h"
#include "oaui/Core/UI/UI.h"


namespace oaui
{
	class MainMenuBar : public MenuBar
	{
	public:
		void Render(UI* ui);
	};
}