#pragma once
#include "oaui.h"
#include "imgui.h"

#define OAUI_MAX_LOGS 4096

namespace oaui
{
	class UI
	{
	private:
		HWND m_hwnd;

		std::mutex m_logMutex;
		std::list<std::pair<ImColor, std::string>> m_logs;

		char* m_notepadBuffer = nullptr;

		bool m_showSectionsWindow;
		bool m_showLogWindow = true;
		bool m_showNotepadWindow = false;

		// For save window
		bool m_showSaveWindow = false;
		int  m_shouldSave = 0;
		bool m_shouldOpenNewFile = false;
		bool m_shouldExit = false;
		bool m_isExiting = false;
		bool m_delayLoad = false;
		std::string m_delayLoadPath;

		bool m_showSettingsWindow = false;
	private:
		bool InitFont();
		bool InitStyle();

	private:

		void OpenFile();

	private:

		void Dockspace();
		void MenuBar();
		void ToolBar();

	private:
		void SectionsWindow();

		void LogWindow();
		void NotepadWindow();

		void SaveWindow();
		void SettingsWindow();

		void AddLog(const ImColor& color, const char* text, va_list va);

	public:
		void ShowSaveWindow();
		void ShouldOpenNewFile(bool val = true);
		void ShouldExit(bool val = true);
		bool IsExiting();
		void DelayLoad(const std::string& path);

	public:
		bool Init(HWND hwnd); // styles, fonts, etc
		void Shutdown();
		void Render();

		void Log(const char* text, ...);
		void Warn(const char* text, ...);
		void Error(const char* text, ...);
		void ClearLogs();

		HWND Hwnd();

	public:
		const char* GetNotepadContent();

		static UI& GetInstance();
	};
}

bool SelectFile(const std::string& fileTypes, std::string& buf, DWORD flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER);
