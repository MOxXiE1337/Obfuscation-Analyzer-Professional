#pragma once
#include "oaui.h"

#include "Interfaces/IAnalyzer.h"

#include "Core/Database/Database.h"

namespace oaui
{
	
	class Loader
	{
	private:
		std::string m_fileName;
		std::string m_path;
		bool m_loaded;

		oacore::IAnalyzer* m_analyzer;

		Database m_database;

	public:
		
		bool IsLoaded();

		oacore::IAnalyzer* GetAnalyzer();

		bool LoadFile(const std::string& path);
		void Unload();
		void Save(const std::string& path = "", bool unload = false); // save to database

		static Loader& GetInstance();
	};
}
