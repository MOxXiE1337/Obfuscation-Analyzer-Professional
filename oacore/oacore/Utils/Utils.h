#pragma once
#include "oacore/oacore.h"

namespace oacore
{
	namespace Utils
	{
		bool OACORE_API        String2Int(const std::string& str, int& val);
		bool OACORE_API        String2UInt(const std::string& str, unsigned int& val);
		bool OACORE_API        String2Float(const std::string& str, float& val);
		bool OACORE_API        String2Double(const std::string& str, double& val);
		bool OACORE_API        String2Bool(const std::string& str, bool& val);

		std::string OACORE_API Bool2String(bool val);

		std::string OACORE_API GetShortName(const std::string& path);
		std::string OACORE_API GetPathWithoutExtension(const std::string& path);
		std::string OACORE_API GetPathDirectory(const std::string& path);
		std::string OACORE_API GetExtensionName(const std::string& path);

		std::string OACORE_API Base64Encode(const std::string& str);
		std::string OACORE_API Base64Encode(const unsigned char* src, size_t size);
		std::string OACORE_API Base64Decode(const std::string& str);
	}
}
