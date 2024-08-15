#pragma once

#include <mutex>
#include <shared_mutex>
#include <regex>
#include <string>
#include <sstream>

#include <Windows.h>

#ifdef OACORE_EXPORTS
#define OACORE_API __declspec(dllexport)
#else
#define OACORE_API __declspec(dllimport)
#endif


