#include "Utils.h"

namespace oaui
{
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

        struct MessageBoxInfo
        {
            const char* text;
            const char* title;
            unsigned int type;
            void(*callback)(int);
        };

        int _MessageBoxThread(MessageBoxInfo* info)
        {
            int button = MessageBoxA(NULL, info->text, info->title, info->type);

            if (info->callback)
                info->callback(button);

            free((void*)info->title);
            free((void*)info->text);
            free(info);
            return 0;
        }

    }

}

