#pragma once

#include "oacore/Interface/IAnalyzer.h"

#include "oacore/Implementation/CPELoader/CPELoader.h"
#include "oacore/Implementation/CDisassembler/CDisassembler.h"

namespace oacore
{
	class CAnalyzer : public IAnalyzer
	{
	private:
		int m_componentError[COMPONENT_SIZE];
	private:
		bool m_loaded;
		std::function<void(IAnalyzer*)> m_callback;
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
		~CAnalyzer();

		bool           IsLoaded() const;

		IDisassembler* GetDisassembler();
	
		Database*      GetDatabase();

		uintptr_t      GetImagebase() const;
		void           RebaseProgram(uintptr_t imagebase);

		unsigned int   GetComponentLastError(_OacoreComponent component) const;
		void           SetComponentLastError(_OacoreComponent component, int error);


		_AnalyzerLoadStatus LoadFile(const std::string& path);
		_AnalyzerSaveStatus SaveFile(const std::string& path);

		void _SetDestructCallback(const std::function<void(IAnalyzer*)>& callback);
	};
}
