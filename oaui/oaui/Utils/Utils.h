#pragma once

#include "oaui.h"

namespace oaui
{
	class Utils
	{
	public:
		bool String2Int(const std::string& str, int& val);
		bool String2Uint(const std::string& str, unsigned int& val);
		bool String2Double(const std::string& str, double& val);
		bool String2Bool(const std::string& str, bool& val);

		std::string Bool2String(bool val);

		std::string GetShortPath(const std::string& path);
		std::string GetPathDirectory(const std::string& path);

		std::string EncodeBase64(const std::string& str);
		std::string EncodeBase64(const unsigned char* src, size_t size);
		std::string DecodeBase64(const std::string& str);
	
	public:
		static Utils& GetInstance();
	};
}
