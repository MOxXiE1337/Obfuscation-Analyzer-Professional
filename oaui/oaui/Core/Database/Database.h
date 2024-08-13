#pragma once
#include "Config/Config.h"

namespace oaui
{
	class Database : public Config
	{
	private:
		bool SaveDisassemblerData();
		bool SvaePELoaderData();
		bool SaveNotepadData();
	public:
		Database();

		_ConfigResolveStatus LoadFile(const std::string& path);

		bool Save(const std::string& path = "");

	};

}
