#pragma once
#include "oacore.h"

#include "IPELoader.h"
#include "IDisassembler.h"

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
		virtual IPELoader* GetPELoader() = 0;
		virtual IDisassembler* GetDisassembler() = 0;

		virtual DWORD64 GetImagebase() = 0;
		virtual VOID    RebaseProgram(DWORD64 imagebase) = 0;

		virtual ANALYZER_LOAD_STATUS LoadFile(CONST _TCHAR* path) = 0;
	};

	OACORE_API IAnalyzer* CreateAnalyzer();
}
