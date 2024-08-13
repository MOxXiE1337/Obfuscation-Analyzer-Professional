#include "CAnalyzer.h"

namespace oacore
{
	CAnalyzer::CAnalyzer()
	{

	}

	IPELoader* CAnalyzer::GetPELoader()
	{
		return &m_peLoader;
	}

	IDisassembler* CAnalyzer::GetDisassembler()
	{
		return &m_disassembler;
	}

	DWORD64 CAnalyzer::GetImagebase()
	{
		return m_rebasedImagebase;
	}

	VOID CAnalyzer::RebaseProgram(DWORD64 imagebase)
	{
		m_rebasedImagebase = imagebase;
	}

	ANALYZER_LOAD_STATUS CAnalyzer::LoadFile(CONST _TCHAR* path)
	{
		ANALYZER_LOAD_STATUS status = ANALYZER_LOAD_SUCCESS;
		PE_LOAD_STATUS peLoadStatus = m_peLoader.LoadFile(path);

		if (peLoadStatus != PE_LOAD_SUCCESS)
		{
			switch (peLoadStatus)
			{
			case PE_FILE_DOESNT_EXIST:
				return ANALYZER_FILE_DOESNT_EXIST;
			case PE_NOT_A_PE_FILE:
				return ANALYZER_NOT_A_PE_FILE;
			case PE_NOT_X64:
				return ANALYZER_PE_NOT_X64;
			default:
				return ANALYZER_PE_LOAD_FAIL;
			}
		}

		RebaseProgram(m_peLoader.GetOptionalHeader()->ImageBase);

		return status;
	}

	OACORE_API IAnalyzer* oacore::CreateAnalyzer()
	{
		return new CAnalyzer{};
	}
}

