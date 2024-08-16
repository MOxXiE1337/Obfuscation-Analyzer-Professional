#include "CAnalyzer.h"

#include "oacore/Utils/Utils.h"


namespace oacore
{
	_AnalyzerLoadStatus CAnalyzer::_LoadPEFile(const std::string& path)
	{
		_AnalyzerLoadStatus status = ANALYZER_LOAD_SUCCESS;

		m_database.SetValue<std::string>("Analyzer.BasicInformation.DatabaseFilePath", Utils::GetPathWithoutExtension(path) + ".odb");

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
		m_callback = {nullptr};
		m_rebasedImagebase = 0x0;

		m_componentError[COMPONENT_DATABASE] = DATABASE_LOAD_SUCCESS;
		m_componentError[COMPONENT_PELOADER] = PE_LOAD_SUCCESS;
	}

	CAnalyzer::~CAnalyzer()
	{
		if (m_callback)
			m_callback(this);
	}

	bool CAnalyzer::IsLoaded() const
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

	uintptr_t CAnalyzer::GetImagebase() const
	{
		return m_rebasedImagebase;
	}

	void CAnalyzer::RebaseProgram(uintptr_t imagebase)
	{
		m_rebasedImagebase = imagebase;
	}

	unsigned int CAnalyzer::GetComponentLastError(_OacoreComponent component) const
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

		Record(0, "Loading %s...", path.c_str());

		if (extensionName == "exe" || extensionName == "dll")
			status = _LoadPEFile(path);
		else if (extensionName == "odb")
			status = _LoadDatabaseFile(path);
		else
			return ANALYZER_UNKNOWN_FILE_TYPE;


		if (status != ANALYZER_LOAD_SUCCESS)
		{
			return status;
		}

		m_loaded = true;
		return status;
	}

	_AnalyzerSaveStatus CAnalyzer::SaveFile(const std::string& path)
	{
		_AnalyzerSaveStatus status = ANALYZER_SAVE_SUCCESS;
		std::string realPath{ path };

		if (path.empty())
			m_database.GetValue("Analyzer.BasicInformation.DatabaseFilePath", realPath);

		if (realPath.empty())
		{
			Record(1, "The path is empty! Please rechoose a path to save the database\n", realPath.c_str());
			return ANALYZER_EMPTY_PATH;
		}

		Record(0, "Saving database to %s...", realPath.c_str());

		if (m_database.SaveFile(realPath) != DATABASE_SAVE_SUCCESS)
		{
			SetComponentLastError(COMPONENT_DATABASE, DATABASE_SAVE_TO_FILE_FAIL);
			return ANALYZER_SAVE_FAIL;
		}

		return status;
	}

	void CAnalyzer::_SetDestructCallback(const std::function<void(IAnalyzer*)>& callback)
	{
		m_callback = callback;
	}

	void OACORE_API CreateAnalyzer(std::shared_ptr<IAnalyzer>& ptr)
	{
		ptr = std::make_shared<CAnalyzer>();
	}
}

