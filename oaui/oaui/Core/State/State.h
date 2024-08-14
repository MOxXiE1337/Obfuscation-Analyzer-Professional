#pragma once

#include "oaui/oaui.h"
#include "oaui/Core/UI/UI.h"

#include "oacore/Interfaces/IAnalyzer.h"

namespace oaui
{
	class State
	{
	private:
		oacore::IAnalyzer* m_analyzer;
		UI m_ui;

	public:
		State();
		~State();

		oacore::IAnalyzer* GetAnalyzer();
		UI* GetUI();
		
		void LoadFile(const std::string& path);
		void Save(const std::string& path = "", bool reset = false);
		void Reset(); // Close analyzer and create a new one

		bool Initialize(HWND hwnd);
		void Shutdown();
	};
}



