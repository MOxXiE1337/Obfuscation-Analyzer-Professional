#include "Utils.h"

namespace oaui
{
	bool Utils::String2Int(const std::string& str, int& val)
	{
		static std::regex dec_reg{ "^[0-9]*$" };
		static std::regex hex_reg{ "0[xX][0-9a-fA-F]+" };
		static std::regex float_reg{ "-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))" };

		std::stringstream stream{};

		if (std::regex_match(str, dec_reg))
		{
			stream << std::dec << str;
			stream >> val;
		}
		else if (std::regex_match(str, hex_reg))
		{
			stream << std::hex << str;
			stream >> val;
		}
		else if (std::regex_match(str, float_reg))
		{
			double doubleval = -1;
			stream << str;
			stream >> doubleval;
			val = (int)std::round(doubleval);
		}
		else
		{
			return false;
		}
		return true;
	}

	bool Utils::String2Uint(const std::string& str, unsigned int& val)
	{
		static std::regex dec_reg{ "^[0-9]*$" };
		static std::regex hex_reg{ "0[xX][0-9a-fA-F]+" };
		static std::regex float_reg{ "-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))" };

		std::stringstream stream{};

		if (std::regex_match(str, dec_reg))
		{
			stream << std::dec << str;
			stream >> val;
		}
		else if (std::regex_match(str, hex_reg))
		{
			stream << std::hex << str;
			stream >> val;
		}
		else if (std::regex_match(str, float_reg))
		{
			double doubleval = -1;
			stream << str;
			stream >> doubleval;
			val = (unsigned int)std::round(doubleval);
		}
		else
		{
			return false;
		}
		return true;
	}

	bool Utils::String2Double(const std::string& str, double& val)
	{
		static std::regex int_reg{ "^[0-9]*$" };
		static std::regex double_reg{ "-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))" };
		std::stringstream stream{};

		if (!std::regex_match(str, double_reg) && !std::regex_match(str, int_reg))
			return false;

		stream << str;
		stream >> val;
		return true;
	}

	bool Utils::String2Bool(const std::string& str, bool& val)
	{
		static std::regex true_reg{ "[tT][rR][uU][eE]" };
		static std::regex false_reg{ "[fF][aA][lL][sS][eE]" };

		if (std::regex_match(str, true_reg))
		{
			val = true;
			return true;
		}
		else if (std::regex_match(str, false_reg))
		{
			val = false;
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string Utils::Bool2String(bool val)
	{
		if (val)
			return "true";
		return "false";
	}

	std::string Utils::GetShortPath(const std::string& path)
	{
		size_t position = path.find_last_of("/\\");

		return path.substr(position + 1, path.length() - position - 1);
	}

	std::string Utils::GetPathDirectory(const std::string& path)
	{
		size_t position = path.find_last_of("/\\");

		return path.substr(0, position + 1);
	}

}

