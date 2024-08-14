#include "CAnalyzer.h"

namespace oacore
{
	CAnalyzer::CAnalyzer()
	{
		m_loaded = false;
	}

	bool CAnalyzer::IsLoaded()
	{
		return m_loaded;
	}

	IDisassembler* CAnalyzer::GetDisassembler()
	{
		return &m_disassembler;
	}

	Database* CAnalyzer::GetDatabase()
	{
		return &m_database;
	}

	uintptr_t CAnalyzer::GetImagebase()
	{
		return m_rebasedImagebase;
	}

	void CAnalyzer::RebaseProgram(uintptr_t imagebase)
	{
		m_rebasedImagebase = imagebase;
	}

	ANALYZER_LOAD_STATUS CAnalyzer::LoadFile(const std::string& path)
	{
		ANALYZER_LOAD_STATUS status = ANALYZER_LOAD_SUCCESS;

		m_loaded = true;

		/*
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

		RebaseProgram(m_peLoader.GetOptionalHeader()->ImageBase); */

		return status;
	}

	OACORE_API IAnalyzer* oacore::CreateAnalyzer()
	{
		return new CAnalyzer{};
	}

	OACORE_API VOID CloseAnalyzer(IAnalyzer*& analyzer)
	{
		if (analyzer)
		{
			delete analyzer;
			analyzer = nullptr;
		}
	}
}

