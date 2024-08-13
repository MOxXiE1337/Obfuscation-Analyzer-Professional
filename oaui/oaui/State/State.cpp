#include "State.h"

namespace oaui
{
	bool State::InitGlobalConfig()
	{
		_ConfigResolveStatus status = m_globalConfig.LoadFile("./cfg/oap.xml");

		if (status == CONFIG_FILE_DOESNT_EXIST)
		{
			if (!GenerateDefaultConfig())
			{
				MessageBoxA(m_hwnd, "Failed to generate default global config!", "Error", MB_ICONERROR);
				return false;
			}
		}

		status = m_globalConfig.LoadFile("./cfg/oap.xml");
		if (status != CONFIG_RESOLVE_SUCCESS)
		{
			MessageBoxA(m_hwnd, "Failed to parse global config!", "Error", MB_ICONERROR);
			return false;
		}

		return true;
	}


	bool State::Init(HWND hwnd)
	{
		m_hwnd = hwnd;

		if (_access("cfg", 0) == -1) 
			_mkdir("cfg");
		
		if (!InitGlobalConfig())
			return false;

	
		return true;
	}

	void State::Shutdown()
	{

	}

	State& State::GetInstance()
	{
		static State instance{};
		return instance;
	}
}

