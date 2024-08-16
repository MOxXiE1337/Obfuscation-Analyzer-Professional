#pragma once
#include <array>
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <regex>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <functional>

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

	void Record(int id, const char* text, ...);
	InfoRecordFn OACORE_API SetRecordHook(int id, InfoRecordFn hook);
}

