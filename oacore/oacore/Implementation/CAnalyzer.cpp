#include "CAnalyzer.h"

#include "oacore/Utils/Utils.h"


namespace oacore
{
	_AnalyzerLoadStatus CAnalyzer::_LoadPEFile(const std::string& path)
	{
		_AnalyzerLoadStatus status = ANALYZER_LOAD_SUCCESS;

		return status;
	}

	_AnalyzerLoadStatus CAnalyzer::_LoadDatabaseFile(const std::string& path)
	{
		_AnalyzerLoadStatus status = ANALYZER_LOAD_SUCCESS;

		_DatabaseLoadStatus databaseStatus = m_database.LoadFile(path);
		SetComponentLastError(COMPONENT_DATABASE, databaseStatus);

		if (databaseStatus == DATABASE_XML_PARSE_FAIL)
			return ANALYZER_DATABASE_LOAD_FAIL;

		_PELoadStatus peStatus = m_peLoader.LoadFromDatabase(this); // only return PE_LOAD_SUCCESS or PE_DATABASE_CORRUPTED
		SetComponentLastError(COMPONENT_PELOADER, peStatus);
		
		if (peStatus == PE_DATABASE_CORRUPTED)
		{
			SetComponentLastError(COMPONENT_DATABASE, DATABASE_CORRUPTED);
			m_database.Clear();
			return ANALYZER_DATABASE_LOAD_FAIL;
		}

		return status;
	}

	CAnalyzer::CAnalyzer() : m_peLoader()
	{
		m_loaded = false;
		m_rebasedImagebase = 0x0;

		m_componentError[COMPONENT_DATABASE] = DATABASE_LOAD_SUCCESS;
		m_componentError[COMPONENT_PELOADER] = PE_LOAD_SUCCESS;
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

	unsigned int CAnalyzer::GetComponentLastError(_OacoreComponent component)
	{
		if (component >= COMPONENT_SIZE)
			return -1;
		return m_componentError[component];
	}

	void CAnalyzer::SetComponentLastError(_OacoreComponent component, int error)
	{
		if (component >= COMPONENT_SIZE)
			return;
		m_componentError[component] = error;
	}

	_AnalyzerLoadStatus CAnalyzer::LoadFile(const std::string& path)
	{
		_AnalyzerLoadStatus status = ANALYZER_LOAD_SUCCESS;
		std::string extensionName = Utils::GetExtensionName(path);

		if (extensionName == "exe" || extensionName == "dll")
			status = _LoadPEFile(path);
		else if (extensionName == "odb")
			status = _LoadDatabaseFile(path);
		else
			return ANALYZER_UNKNOWN_FILE_TYPE;

		m_database.SetValue<std::string>("Analyzer.BasicInformation.DatabaseFilePath", Utils::GetPathWithoutExtension(path) + ".odb");

		if (status != ANALYZER_LOAD_SUCCESS)
		{
			return status;
		}

		m_loaded = true;
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

