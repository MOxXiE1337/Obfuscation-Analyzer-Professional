#pragma once
#include "oaui/oaui.h"

namespace oaui
{
	namespace Utils
	{
		bool SelectFile(HWND hwnd, const char* filter, std::string& buf, DWORD flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER);

	}
}

