#include "Database.h"

#include "UI/UI.h"
#include "Core/Loader/Loader.h"

namespace oaui
{


	bool Database::SaveDisassemblerData()
	{
		return true;
	}

	bool Database::SvaePELoaderData()
	{
		oacore::IPELoader* peLoader = Loader::GetInstance().GetAnalyzer()->GetPELoader();

		CONST PIMAGE_SECTION_HEADER sectionHeaders = peLoader->GetSectionHeaders();
		SIZE_T numberOfSections = peLoader->GetNumberOfSections();

		for (SIZE_T u = 0; u < numberOfSections; u++)
		{
			std::string header0 = std::string("PELoader.Binary.Section[") + std::to_string(u) + "]";
			SetValue<std::string>(header0, Utils::GetInstance().EncodeBase64((unsigned char*)(peLoader->GetImagebase() + sectionHeaders[u].VirtualAddress), sectionHeaders[u].Misc.VirtualSize));

			std::string header1 = std::string("PELoader.Sections.Section[") + std::to_string(u) + "]";
			SetValue<std::string>(header1 + ".Name", std::string((const char*)sectionHeaders[u].Name));
			SetValue<unsigned int>(header1 + ".VirtualAddress", sectionHeaders[u].VirtualAddress);
			SetValue<unsigned int>(header1 + ".VirtualSize", sectionHeaders[u].Misc.VirtualSize);
			SetValue<unsigned int>(header1 + ".PointerToRawData", sectionHeaders[u].PointerToRawData);
			SetValue<unsigned int>(header1 + ".SizeOfRawData", sectionHeaders[u].SizeOfRawData);
			SetValue<unsigned int>(header1 + ".Characteristics", sectionHeaders[u].Characteristics);
		}
		return true;
	}

	bool Database::SaveNotepadData()
	{
		const char* notepadContent = UI::GetInstance().GetNotepadContent();
		if (notepadContent)
		{
			SetValue("DatabaseNotepad", Utils::GetInstance().EncodeBase64(notepadContent));
		}
		return true;
	}

	Database::Database() : Config("Database")
	{
	}

	_ConfigResolveStatus Database::LoadFile(const std::string& path)
	{
		return Config::LoadFile(path);
	}

	bool Database::Save(const std::string& path)
	{
		if (!Loader::GetInstance().IsLoaded())
			return false;

		Clear();
		

		if (!SaveDisassemblerData())
			return false;
		if (!SvaePELoaderData())
			return false;
		if (!SaveNotepadData())
			return false;

#ifdef _NDEBUG
		return Config::Save(path, true);
#else
		return Config::Save(path, false);
#endif
	}


}

