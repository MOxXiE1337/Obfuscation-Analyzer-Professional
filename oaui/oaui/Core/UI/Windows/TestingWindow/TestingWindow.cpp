#ifndef NDEBUG

#include "TestingWindow.h"

namespace oaui
{

	TestingWindow::TestingWindow() : Window(true)
	{
	}

	void TestingWindow::Render(UI* ui)
	{
		ImGui::Begin("Testing");



		ImGui::End();
	}
}

#endif
