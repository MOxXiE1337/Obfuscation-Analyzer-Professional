#pragma once

#include <mutex>
#include <shared_mutex>
#include <regex>
#include <string>
#include <sstream>
#include <algorithm>

#include <Windows.h>


#ifdef OACORE_EXPORTS
#define OACORE_API __declspec(dllexport)
#else
#define OACORE_API __declspec(dllimport)
#endif


namespace oacore
{
	enum _OacoreComponent
	{
		/* ANALYZER, */ // You can't get analyzer error code by GetComponentLastError, just use the return value
		COMPONENT_DATABASE,
		COMPONENT_PELOADER,
		COMPONENT_SIZE
	};

	typedef void(*InfoRecordFn)(const char*);

	extern InfoRecordFn Log;
	extern InfoRecordFn Warn;
	extern InfoRecordFn Error;
	InfoRecordFn OACORE_API SetRecordHook(int id, InfoRecordFn hook);
}

