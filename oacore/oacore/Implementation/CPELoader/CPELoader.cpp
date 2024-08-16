#include "CPELoader.h"


namespace oacore
{
    CPELoader::CPELoader()
    {
    }
    CPELoader::~CPELoader()
    {
    }
    _PELoadStatus CPELoader::LoadFromDatabase(IAnalyzer* analyzer)
    {
        Database* database = analyzer->GetDatabase();
        _PELoadStatus status = PE_LOAD_SUCCESS;

        if (!database->GetValue("PELoader.BasicInformation.FullFilePath", m_fileFullPath))
        {
            Record(2, "[ CPELoader ] Failed to read \"PELoader.BasicInformation.FullFilePath\" from database");
            return PE_DATABASE_CORRUPTED;
        }
        
        return status;
    }
}
