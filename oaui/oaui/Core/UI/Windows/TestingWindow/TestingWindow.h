#ifndef NDEBUG

#pragma once
#include "oaui/Core/UI/Window.h"
#include "oaui/Core/UI/UI.h"

namespace oaui
{
	// This window is for debugging usage
	class TestingWindow : public Window
	{
	private:
	public:
		TestingWindow();


		void Render(UI* ui);
	};
}

#endif
