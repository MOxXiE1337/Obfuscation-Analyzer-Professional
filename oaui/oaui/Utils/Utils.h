#pragma once
#include "oaui/oaui.h"

namespace oaui
{
	namespace Utils
	{
		bool SelectFile(HWND hwnd, const char* filter, std::string& buf, DWORD flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER);

        template <typename Func, typename... Args>
        class ThreadExecutor
        {
        public:
            ThreadExecutor(Func&& function, std::mutex* waitFor = nullptr, Args&&... args)
            {
                auto task = [func = std::forward<Func>(function), waitFor, argsTuple = std::make_tuple(std::forward<Args>(args)...)]() mutable {
                    std::apply([&](auto&&... unpackedArgs) {
                        ThreadExecutorFunction(std::move(func), waitFor, std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
                        }, argsTuple);
                    };
                std::thread t(task);
                t.detach();
            }

        private:
            template <typename Func, typename... Args>
            static void ThreadExecutorFunction(Func&& function, std::mutex* waitFor, Args&&... args)
            {
                if (waitFor)
                {
                    std::lock_guard<std::mutex> guard(*waitFor); 
                }
                std::invoke(function, std::forward<Args>(args)...);
            }
        };
	}
}

