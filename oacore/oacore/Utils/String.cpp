#include "Utils.h"

namespace oacore
{
	namespace Utils
	{
		bool String2Int(const std::string& str, int& val)
		{
			static std::regex decRegex{ "^[0-9]*$" };
			static std::regex hexRegex{ "0[xX][0-9a-fA-F]+" };
			static std::regex floatRegex{ "-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))" };

			std::stringstream stream{};

			if (std::regex_match(str, decRegex))
			{
				stream << std::dec << str;
				stream >> val;
			}
			else if (std::regex_match(str, hexRegex))
			{
				stream << std::hex << str;
				stream >> val;
			}
			else if (std::regex_match(str, floatRegex))
			{
				double doubleValue = -1;
				stream << str;
				stream >> doubleValue;
				val = static_cast<int>(std::round(doubleValue));
			}
			else
			{
				return false;
			}
			return true;
		}

		bool String2UInt(const std::string& str, unsigned int& val)
		{
			static std::regex decRegex{ "^[0-9]*$" };
			static std::regex hexRegex{ "0[xX][0-9a-fA-F]+" };
			static std::regex floatRegex{ "-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))" };

			std::stringstream stream{};

			if (std::regex_match(str, decRegex))
			{
				stream << std::dec << str;
				stream >> val;
			}
			else if (std::regex_match(str, hexRegex))
			{
				stream << std::hex << str;
				stream >> val;
			}
			else if (std::regex_match(str, floatRegex))
			{
				double doubleValue = -1;
				stream << str;
				stream >> doubleValue;
				val = static_cast<unsigned int>(std::round(doubleValue));
			}
			else
			{
				return false;
			}
			return true;
		}

		bool String2Float(const std::string& str, float& val)
		{
			double tmp = 0;
			bool result = String2Double(str, tmp);
			if (result)
				val = static_cast<float>(tmp);
			return result;
		}

		bool String2Double(const std::string& str, double& val)
		{
			static std::regex intRegex{ "^[0-9]*$" };
			static std::regex doubleRegex{ "-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))" };
			std::stringstream stream{};

			if (!std::regex_match(str, doubleRegex) && !std::regex_match(str, intRegex))
				return false;

			stream << str;
			stream >> val;
			return true;
		}

		bool String2Bool(const std::string& str, bool& val)
		{
			static std::regex trueRegex{ "[tT][rR][uU][eE]" };
			static std::regex falseRegex{ "[fF][aA][lL][sS][eE]" };

			if (std::regex_match(str, trueRegex))
			{
				val = true;
				return true;
			}
			else if (std::regex_match(str, falseRegex))
			{
				val = false;
				return true;
			}
			else
			{
				return false;
			}
		}

		std::string Bool2String(bool val)
		{
			if (val)
				return "true";
			return "false";
		}

		std::string GetShortPath(const std::string& path)
		{
			size_t position = path.find_last_of("/\\");

			return path.substr(position + 1, path.length() - position - 1);
		}

		std::string GetPathDirectory(const std::string& path)
		{
			size_t position = path.find_last_of("/\\");

			return path.substr(0, position + 1);
		}

	}
}