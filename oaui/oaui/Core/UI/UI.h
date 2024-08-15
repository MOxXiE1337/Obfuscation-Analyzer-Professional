#pragma once
#include "oaui/oaui.h"
#include "oaui/Core/UI/UI.h"

#include "Window.h"
#include "MenuBar.h"

#include "imgui.h"

namespace oaui
{
	enum _WindowId
	{
		DOCKSPACE_WINDOW,
		DATATBASE_VIWER_WINDOW,
		NOTEPAD_WINDOW,
		OUTPUT_WINDOW,
		SAVING_WINDOW
	};

	class UI
	{
		friend class State;
	private:
		State* m_state;
		HWND m_hwnd;

		MenuBar* m_mainMenuBar;
		Window* m_dockspaceWindow;
		Window* m_databaseViewerWindow;
		Window* m_notepadWindow;
		Window* m_outputWindow;
		Window* m_savingWindow;

	private:
		bool _InitializeStyle();
		bool _InitializeFonts();

	private:
		// for State to call
		bool Initialize(HWND hwnd);
		void Shutdown();
	public:
		UI();
		~UI();

		State* GetState() { return m_state; }
		HWND GetHWND() { return m_hwnd; }
		Window* GetWindow(_WindowId id);

		void Log(const char* text, ...);
		void Warn(const char* text, ...);
		void Error(const char* text, ...);

		void Render();
	};
	/*
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
	}; */
}

bool SelectFile(const std::string& fileTypes, std::string& buf, DWORD flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER);
