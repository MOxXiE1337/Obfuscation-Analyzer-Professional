#include "Loader.h"
#include "UI/UI.h"
#include "Utils/Utils.h"

//#include "Core/Database/Database.h"

namespace oaui
{
	bool Loader::IsLoaded()
	{
		return m_loaded;
	}

	oacore::IAnalyzer* Loader::GetAnalyzer()
	{
		return m_analyzer;
	}

	bool Loader::LoadDatabase(const std::string& path)
	{
		using namespace oacore;
		UI& ui = UI::GetInstance();

		return true;
	}

	bool Loader::LoadFile(const std::string& path)
	{
		using namespace oacore;
		UI& ui = UI::GetInstance();

		m_analyzer = CreateAnalyzer();

		if (path.find(".odb") != std::string::npos)
			return LoadDatabase(path);

		ANALYZER_LOAD_STATUS status = m_analyzer->LoadFile(std::wstring(path.begin(), path.end()).c_str());
		
		switch (status)
		{
		case ANALYZER_FILE_DOESNT_EXIST:
			ui.Error("Failed to load \"%s\" , file doesn't exist!", path.c_str());
			break;
		case ANALYZER_NOT_A_PE_FILE:
			ui.Error("Failed to load \"%s\" , target file is not a PE file!", path.c_str());
			break;
		case ANALYZER_PE_LOAD_FAIL:
			ui.Error("Failed to load \"%s\" , an error occured while parsing PE file!", path.c_str());
			break;
		case ANALYZER_PE_NOT_X64:
			ui.Error("Failed to load \"%s\" , only x64 PE file is supported!", path.c_str());
			break;
		case ANALYZER_LOAD_SUCCESS:
			ui.Log("PE file \"%s\", has been loaded ( %d sections )", path.c_str(), m_analyzer->GetPELoader()->GetNumberOfSections());
			ui.Log("        \tImagebase:  %p", m_analyzer->GetPELoader()->GetImagebase());
			ui.Log("        \tImagesize:   %p", m_analyzer->GetPELoader()->GetImagesize());
			ui.Log("        \tEntrypoint:  %p", m_analyzer->GetPELoader()->GetEntrypoint());
		
			break;
		}

		if (status != ANALYZER_LOAD_SUCCESS)
		{
			MessageBoxA(ui.Hwnd(), "Failed to initialize analyzer!", "Error", MB_ICONERROR);
			delete m_analyzer;
			m_analyzer = nullptr;
			return false;
		}

		m_loaded = true;

		m_fileName = Utils::GetInstance().GetShortPath(path);
		m_path = path;
		SetWindowTextA(ui.Hwnd(), (std::string("Obfuscation Analyzer Professional - ") + m_fileName + path).c_str());

		return true;
	}

	void Loader::Unload()
	{
		if (!m_loaded)
			return;

		delete m_analyzer;
		m_analyzer = nullptr;

		m_fileName.clear();
		m_path.clear();
		m_loaded = false;

		SetWindowTextA(UI::GetInstance().Hwnd(), "Obfuscation Analyzer Professional");

		
	}

	void Loader::Save(const std::string& path, bool unload)
	{
		UI& ui = UI::GetInstance();
		oacore::IPELoader* peLoader = nullptr;

		std::string realPath = path;

		if (!m_loaded)
			return;

		peLoader = m_analyzer->GetPELoader();

		if (path.empty())
			realPath = Utils::GetInstance().GetPathDirectory(m_path) + m_fileName + ".odb";

		ui.Log("Saving database to %s...", realPath.c_str());
		
		// if database existed, remove
		if (_access(path.c_str(), 0) != -1)
			remove(path.c_str());

		if (true)
			ui.Log("Database has been saved\n\n");
		else
			ui.Error("Failed to save database!\n\n");

		

		// Unload
		if (unload)
			Unload();
	}

	Loader& Loader::GetInstance()
	{
		static Loader instance{};
		return instance;
	}
}

