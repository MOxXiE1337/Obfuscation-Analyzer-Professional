#pragma once

#include "oaui/oaui.h"
#include "oaui/Core/UI/UI.h"

#include "oacore/Interface/IAnalyzer.h"

#include "oaui/Utils/Utils.h"

namespace oaui
{
	class State
	{
	private:
		friend void _AnalyzerDestructCallback(oacore::IAnalyzer* analyzer);

		std::shared_ptr<oacore::IAnalyzer> m_analyzer;
		std::mutex                         m_isLoadingOrSaving;

		UI m_ui;

	public:
		State();
		~State();

		UI* GetUI();
		
		std::shared_ptr<oacore::IAnalyzer> GetAnalyzer();
		std::mutex& IsLoadOrSaving(); // For GUI sync

		void LoadFile(const std::string& path, bool createNewThread = true);
		void Save(const std::string& path = "", bool createNewThread = true);
		void Reset(); // Close analyzer and create a new one

		bool Initialize(HWND hwnd, struct ID3D11Device* device);
		void Shutdown();

		static State& GetInstance();
	};
}



