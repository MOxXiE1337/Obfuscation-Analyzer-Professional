#pragma once

#include "oaui.h"
#include "Utils/Utils.h"
#include "tinyxml2.h"

namespace oaui
{

	typedef std::unordered_map<std::string, std::string> ConfigFlatDatabase;

	enum _ConfigResolveStatus
	{
		CONFIG_RESOLVE_SUCCESS,
		CONFIG_FILE_DOESNT_EXIST,
		CONFIG_RESOLVE_FAIL
	};

	class Config
	{
	protected:
		std::string m_root;
		std::string m_path;
		ConfigFlatDatabase m_db;

	public:
		Config(const std::string& rootName = "Configuration");

		_ConfigResolveStatus LoadFile(const std::string& path);
		bool Save(const std::string& path = "", bool compact = false);

		ConfigFlatDatabase& GetFlatDatabase();
		void Clear();

		template<typename T>
		bool GetValue(const std::string& key, T& val)
		{
			Utils& utils = Utils::GetInstance();

			if (m_db.count(key) == 0)
				return false;

			std::string text = m_db[key];

			if constexpr (std::is_same<T, int>::value)
				return utils.String2Int(text, val);
			if constexpr (std::is_same<T, unsigned int>::value)
				return utils.String2Uint(text, val);
			if constexpr (std::is_same<T, float>::value)
			{
				double tmp;
				bool success = utils.String2Double(text, tmp);
				if (success)
					val = (float)tmp;
				return success;
			}
			if constexpr (std::is_same<T, double>::value)
				return utils.String2Double(text, val);
			if constexpr (std::is_same<T, bool>::value)
				return utils.String2Bool(text, val);
			if constexpr (std::is_same<T, const char*>::value)
			{
				val = text.c_str();
				return true;
			}
			if constexpr (std::is_same<T, std::string>::value)
			{
				val = text;
				return true;
			}

		}

		template<typename T>
		bool SetValue(const std::string& key, T value) 
		{
			std::stringstream stream{};
			std::string       strValue{};
		
			if constexpr (std::is_same<T, bool>::value)
			{
				m_db[key] = Utils::GetInstance().Bool2String(value);
				return true;
			}

			stream << value;
			stream >> strValue;
			m_db[key] = strValue;

			return true;
		}
	};


}
