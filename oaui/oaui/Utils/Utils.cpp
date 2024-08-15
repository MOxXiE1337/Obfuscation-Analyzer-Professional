#include "Utils.h"

namespace Utils
{
    bool SelectFile(HWND hwnd, const char* filter, std::string& buf, DWORD flags)
    {
        CHAR buffer[MAX_PATH] = { 0 };
        OPENFILENAMEA ofn{ 0 };
        
        ofn.lStructSize = sizeof(OPENFILENAMEA);
        ofn.hInstance = GetModuleHandle(NULL);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFilter = filter;
        ofn.lpstrCustomFilter = NULL;
        ofn.nFilterIndex = 0;
        ofn.lpstrFile = buffer;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = flags;

        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            buf = buffer;
            return true;
        }
        return false;
    }

    bool CopyToClipBoard(const char* data, size_t size)
    {
        if (OpenClipboard(NULL) == FALSE)
            return false;

        EmptyClipboard();
        HGLOBAL clipBuffer = NULL;
        char* buffer = nullptr;
        clipBuffer = GlobalAlloc(GMEM_DDESHARE, size + 1);

        if (clipBuffer == NULL)
            return false;

        buffer = (char*)GlobalLock(clipBuffer);

        if (buffer == nullptr)
            return false;

        memcpy(buffer, data, size);

        GlobalUnlock(clipBuffer);
        SetClipboardData(CF_TEXT, clipBuffer);

        return true;
    }
}

