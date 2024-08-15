#pragma once
#include <d3d11.h>

#include "oaui/oaui.h"

#include "Window.h"
#include "MenuBar.h"

#include "imgui.h"

namespace oaui
{
	enum _WindowId
	{
		DOCKSPACE_WINDOW,
		DATABASE_VIEWER_WINDOW,
		NOTEPAD_WINDOW,
		OUTPUT_WINDOW,
		SAVING_WINDOW
	};


	class UI
	{
		friend class State;
	private:
		HWND m_hwnd;
		ID3D11Device* m_device;

		std::unordered_map<std::string, ImTextureID> m_textures;
	private:

		MenuBar* m_mainMenuBar;
		Window* m_dockspaceWindow;
		Window* m_databaseViewerWindow;
		Window* m_notepadWindow;
		Window* m_outputWindow;

		Window* m_savingWindow;

#ifndef NDEBUG
		Window* m_testingWindow;
#endif

	private:
		bool _InitializeStyle();
		bool _InitializeFonts();
		bool _InitializeTextures();

	private:
		// for State to call
		bool Initialize(HWND hwnd, ID3D11Device* device);
		void Shutdown();
	public:
		UI();
		~UI();

		HWND GetHWND() { return m_hwnd; }
		ImTextureID GetTexture(const std::string);
		Window* GetWindow(_WindowId id);

		void Log(const char* text, ...);
		void Warn(const char* text, ...);
		void Error(const char* text, ...);
		void LogV(const char* text, va_list ap);
		void WarnV(const char* text, va_list ap);
		void ErrorV(const char* text, va_list ap);

		void Render();
	};
}
