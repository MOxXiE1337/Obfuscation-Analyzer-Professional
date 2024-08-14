#include "Utils.h"
#include "cpp-base64/cpp-base64.h"

namespace oacore
{
	namespace Utils
	{
		std::string Base64Encode(const std::string& str)
		{
			return base64_encode(str);
		}
		std::string Base64Encode(const unsigned char* src, size_t size)
		{
			return base64_encode(src, size);
		}
		std::string Base64Decode(const std::string& str)
		{
			return base64_decode(str);
		}
	}
}