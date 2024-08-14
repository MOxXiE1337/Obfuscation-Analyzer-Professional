#include "Utils/Utils.h"

#include "cpp-base64.h"

namespace oaui
{
	std::string Utils::EncodeBase64(const std::string& str)
	{
		return base64_encode(str);
	}
	std::string Utils::EncodeBase64(const unsigned char* src, size_t size)
	{
        return base64_encode(src, size);
    }

	std::string Utils::DecodeBase64(const std::string& str)
	{
		return base64_decode(str);
	}
}