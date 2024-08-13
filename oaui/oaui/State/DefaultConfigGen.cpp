#include "State.h"

namespace oaui
{
	bool State::GenerateDefaultConfig()
	{
		return(m_globalConfig.Save("./cfg/oap.xml"));
	}

}