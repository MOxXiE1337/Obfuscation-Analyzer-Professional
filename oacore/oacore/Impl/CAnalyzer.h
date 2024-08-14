#pragma once

#include "oacore/Interfaces/IAnalyzer.h"

#include "CDisassembler.h"

namespace oacore
{
	class CAnalyzer : public IAnalyzer
	{
	private:
		bool m_loaded;
		std::string m_filePath;

		Database m_database;

		CDisassembler m_disassembler;

		uintptr_t m_rebasedImagebase;
	public:
		CAnalyzer();

		bool           IsLoaded();

		IDisassembler* GetDisassembler();
	
		Database*      GetDatabase();

		uintptr_t      GetImagebase();
		void           RebaseProgram(uintptr_t imagebase);

		ANALYZER_LOAD_STATUS LoadFile(const std::string& path);
	};
}
