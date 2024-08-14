#pragma once

#include "Interfaces/IAnalyzer.h"

#include "CPELoader.h"
#include "CDisassembler.h"

namespace oacore
{
	class CAnalyzer : public IAnalyzer
	{
	private:
		CPELoader m_peLoader;
		CDisassembler m_disassembler;

		DWORD64 m_rebasedImagebase;
	public:
		CAnalyzer();

		IPELoader* GetPELoader();
		IDisassembler* GetDisassembler();

		DWORD64 GetImagebase();
		VOID    RebaseProgram(DWORD64 imagebase);

		ANALYZER_LOAD_STATUS LoadFile(CONST _TCHAR* path);
	};
}
