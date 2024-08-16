#pragma once

#include "oacore/Interface/IPELoader.h"
#include "oacore/Interface/IAnalyzer.h"

namespace oacore
{
	
	class CPELoader : public IPELoader
	{
	private:
		std::string m_fileFullPath; // Not used, just a record
	public:
		CPELoader();
		~CPELoader();

		_PELoadStatus LoadFromDatabase(IAnalyzer* analyzer);
		_PELoadStatus LoadFromPEFile(IAnalyzer* analyzer, const std::string& path);
	};
}
