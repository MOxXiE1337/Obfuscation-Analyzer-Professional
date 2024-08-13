#include "Utils.h"

namespace oaui
{
	Utils& Utils::GetInstance()
	{
		static Utils instance{};
		return instance;
	}
}