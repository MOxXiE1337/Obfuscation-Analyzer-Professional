#include "Utils.h"

namespace Utils
{
    bool SelectFile(HWND hwnd, const std::string& filter, std::string& buf, DWORD flags)
    {
        CHAR buffer[MAX_PATH] = { 0 };
        OPENFILENAMEA ofn{ 0 };
        
        ofn.lStructSize = sizeof(OPENFILENAMEA);
        ofn.hInstance = GetModuleHandle(NULL);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFilter = filter.c_str();
        ofn.lpstrCustomFilter = NULL;
        ofn.nFilterIndex = 0;
        ofn.lpstrFile = buffer;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrInitialDir = "C:\\Windows";
        ofn.Flags = flags;

        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            buf = buffer;
            return true;
        }
        return false;
    }
}

