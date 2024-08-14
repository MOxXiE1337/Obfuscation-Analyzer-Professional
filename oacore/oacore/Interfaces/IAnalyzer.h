#pragma once
#include "oacore/oacore.h"
#include "oacore/Interfaces/IDisassembler.h"
#include "oacore/Common/Database.h"

namespace oacore
{
	enum ANALYZER_LOAD_STATUS
	{
		ANALYZER_LOAD_SUCCESS,
		ANALYZER_FILE_DOESNT_EXIST,
		ANALYZER_NOT_A_PE_FILE,
		ANALYZER_PE_LOAD_FAIL,
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

		virtual ANALYZER_LOAD_STATUS LoadFile(const std::string& path) = 0;
	};

	OACORE_API IAnalyzer* CreateAnalyzer();
	OACORE_API void       CloseAnalyzer(IAnalyzer*& analyzer);
}
