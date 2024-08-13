#pragma once
#include "oaui.h"
#include "Config/Config.h"

namespace oaui
{
	class State
	{
	private:
		HWND m_hwnd;
		Config m_globalConfig;
	private:
		bool GenerateDefaultConfig();

		bool InitGlobalConfig();
	public:
		
		bool Init(HWND hwnd);
		void Shutdown();

	public:
		static State& GetInstance();
	};
}
