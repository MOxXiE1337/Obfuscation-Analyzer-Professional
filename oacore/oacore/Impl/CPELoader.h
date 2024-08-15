#pragma once

#include "oacore/Interfaces/IPELoader.h"
#include "oacore/Interfaces/IAnalyzer.h"

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
	};
}
