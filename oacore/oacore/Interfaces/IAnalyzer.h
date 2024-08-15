#pragma once
#include "oacore/oacore.h"
#include "oacore/Interfaces/IDisassembler.h"
#include "oacore/Common/Database.h"

namespace oacore
{
	enum _AnalyzerLoadStatus
	{
		ANALYZER_LOAD_SUCCESS,
		ANALYZER_FILE_DOESNT_EXIST,
		ANALYZER_NOT_A_PE_FILE,
		ANALYZER_UNKNOWN_FILE_TYPE, // Not PE file or Database file, (shouldn't appear, cuz file selecting dialog filters the file type)
		ANALYZER_PE_LOAD_FAIL,
		ANALYZER_DATABASE_LOAD_FAIL,
		ANALYZER_PE_NOT_X64
	};


	class IAnalyzer
	{
	public:
		virtual bool           IsLoaded() = 0;

		virtual IDisassembler* GetDisassembler() = 0;
		virtual Database*      GetDatabase() = 0;

		virtual uintptr_t      GetImagebase() = 0;
		virtual void           RebaseProgram(uintptr_t imagebase) = 0;

		virtual unsigned int   GetComponentLastError(_OacoreComponent component) = 0;
		virtual void           SetComponentLastError(_OacoreComponent component, int error) = 0;

		virtual _AnalyzerLoadStatus LoadFile(const std::string& path) = 0;
	};

	OACORE_API IAnalyzer* CreateAnalyzer();
	OACORE_API void       CloseAnalyzer(IAnalyzer*& analyzer);
}
