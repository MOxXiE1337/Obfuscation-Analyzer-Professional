#pragma once

#include "oacore/Interfaces/IAnalyzer.h"

#include "CPELoader.h"
#include "CDisassembler.h"

namespace oacore
{
	class CAnalyzer : public IAnalyzer
	{
	private:
		int m_componentError[COMPONENT_SIZE];
	private:
		bool m_loaded;
		std::string m_filePath;

		Database     m_database;
		CPELoader     m_peLoader;
		CDisassembler m_disassembler;


		uintptr_t m_rebasedImagebase;

	public:
		_AnalyzerLoadStatus _LoadPEFile(const std::string& path);
		_AnalyzerLoadStatus _LoadDatabaseFile(const std::string& path);

	public:
		CAnalyzer();

		bool           IsLoaded();

		IDisassembler* GetDisassembler();
	
		Database*      GetDatabase();

		uintptr_t      GetImagebase();
		void           RebaseProgram(uintptr_t imagebase);

		unsigned int   GetComponentLastError(_OacoreComponent component);
		void           SetComponentLastError(_OacoreComponent component, int error);


		_AnalyzerLoadStatus LoadFile(const std::string& path);
	};
}
