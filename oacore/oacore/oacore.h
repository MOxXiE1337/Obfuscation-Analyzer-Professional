#pragma once

#include <cstdio>
#include <cassert>

#include <Windows.h>
#include <tchar.h>

#ifdef OACORE_EXPORTS
#define OACORE_API __declspec(dllexport)
#else
#define OACORE_API __declspec(dllimport)
#endif


