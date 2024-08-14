#pragma once
#include "oaui/oaui.h"

namespace Utils
{
	bool SelectFile(HWND hwnd, const std::string& filter, std::string& buf, DWORD flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER);
}
