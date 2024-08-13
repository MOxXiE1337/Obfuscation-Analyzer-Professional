#include "UI.h"

#include "imgui_freetype.h"

#include "Resources/iconfont.h"
#include "Core/Loader/Loader.h"


bool SelectFile(const std::string& fileTypes, std::string& buf, DWORD flags)
{
	CHAR curPath[MAX_PATH] = { 0 };

	// Make sure the work path wont change
	GetCurrentDirectoryA(MAX_PATH, curPath);

	CHAR szBuffer[MAX_PATH] = { 0 };
	OPENFILENAMEA ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = oaui::UI::GetInstance().Hwnd();
	ofn.lpstrFilter = fileTypes.c_str();  ;
	ofn.lpstrInitialDir = "C:\\Windows";
	ofn.lpstrFile = szBuffer;
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = flags;
	BOOL bSel = GetOpenFileNameA(&ofn);

	SetCurrentDirectoryA(curPath);

	if (bSel == TRUE)
		buf = szBuffer;

	return (bSel == TRUE);
}

namespace oaui
{
	bool UI::InitFont()
	{
		ImGuiIO& io = ImGui::GetIO();

		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 18, NULL, io.Fonts->GetGlyphRangesDefault());

		ImFontConfig config0{};
		const ImWchar ranges0[] =
		{
			0x2000, 0x206F, 			0x3000, 0x30FF, 			0x31F0, 0x31FF, 			0xFF00, 0xFFEF, 			0xFFFD, 0xFFFD, 			0x4e00, 0x9FAF, 			0,
		};

		config0.MergeMode = true;
		ImFont* msyh = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 18, &config0, ranges0);

		if (msyh == nullptr)
		{
			MessageBoxA(m_hwnd, "Failed to load msyc font!", "Error", MB_ICONERROR);
			return false;
		}

		ImFontConfig config1{};
		const ImWchar ranges1[] =
		{
			58896,59551,
			0
		};

		config1.OversampleH = config1.OversampleV = 1;
		config1.MergeMode = true;
		config1.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_LoadColor;


		ImFont* iconFont = io.Fonts->AddFontFromMemoryCompressedTTF(Resources::iconfont_compressed_data, sizeof(Resources::iconfont_compressed_size), 18, &config1, ranges1);
		if (iconFont == nullptr)
		{
			MessageBoxA(m_hwnd, "Failed to load icon font!", "Error", MB_ICONERROR);
			return false;
		}

		io.Fonts->Build();

		return true;
	}

	bool UI::InitStyle()
	{
        ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowRounding = 7;

        style->FrameBorderSize = 1;
        style->FrameRounding = 3;

		style->TabBorderSize = 1;
		style->TabBarBorderSize = 1;

        style->GrabRounding = 4.0f;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.78f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.81f, 0.81f, 0.81f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.62f, 0.62f, 0.63f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.91f, 0.91f, 0.91f, 0.86f);
		colors[ImGuiCol_TabSelected] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
		colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.51f, 0.51f, 0.51f, 0.00f);
		colors[ImGuiCol_TabDimmed] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
		colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.15f, 0.50f, 0.92f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.05f, 0.40f, 0.82f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.15f, 0.50f, 0.92f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.05f, 0.40f, 0.82f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.81f, 0.81f, 0.81f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextLink] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.15f, 0.50f, 0.92f, 0.20f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.17f, 0.17f, 0.17f, 0.04f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

		return true;
	}

	void UI::OpenFile()
	{
		Loader& loader = Loader::GetInstance();
		std::string path;

		// TODO if is loaded, save and open new file

		if (!SelectFile("Exe(*.exe)\0*.exe\0Dll(*.dll)\0*.dll\0All Files(*.*)\0*.*\0", path))
			return;

		loader.LoadFile(path);
	}

	bool UI::Init(HWND hwnd)
	{
		m_hwnd = hwnd;

		if (!InitFont())
			return false;

		if (!InitStyle())
			return false;

		return true;
	}

	void UI::Shutdown()
	{
		if (m_notepadBuffer)
		{
			free(m_notepadBuffer);
			m_notepadBuffer = nullptr;
		}

	}

	void UI::Render()
	{
		MenuBar();

		Dockspace();

		SectionsWindow();
		LogWindow();
		NotepadWindow();

		SaveWindow();
		SettingsWindow();

	}

	void UI::AddLog(const ImColor& color, const char* text, va_list va)
	{
		static char buffer[2048];

		m_logMutex.lock();

		if (m_logs.size() > OAUI_MAX_LOGS)
			m_logs.pop_front();
	
		memset(buffer, 0, 2048);
		vsprintf(buffer, text, va);

		m_logs.push_back({ color, std::string(buffer) });

		m_logMutex.unlock();
	}

	void UI::ShowSaveWindow()
	{
		m_shouldSave = 0;
		m_showSaveWindow = true;
	}

	void UI::ShouldOpenNewFile(bool val)
	{
		m_shouldOpenNewFile = val;
	}

	void UI::ShouldExit(bool val)
	{
		m_shouldExit = val;
	}

	bool UI::IsExiting()
	{
		return m_isExiting;
	}

	void UI::DelayLoad(const std::string& path)
	{
		m_delayLoad = true;
		m_delayLoadPath = path;
	}

	void UI::Log(const char* text, ...)
	{
		va_list va;
		va_start(va, text);
		AddLog(ImGui::GetStyle().Colors[ImGuiCol_Text], text, va);
		va_end(va);
	}

	void UI::Warn(const char* text, ...)
	{
		va_list va;
		va_start(va, text);
		AddLog(ImColor{ IM_COL32(238,154,0,255) }, text, va);
		va_end(va);
	}

	void UI::Error(const char* text, ...)
	{
		va_list va;
		va_start(va, text);
		AddLog(ImColor{ 0xFF0000FF }, text, va);
		va_end(va);
	}

	void UI::ClearLogs()
	{
		m_logs.clear();
	}

	HWND UI::Hwnd()
	{
		return m_hwnd;
	}

	const char* UI::GetNotepadContent()
	{
		return m_notepadBuffer;
	}

	UI& UI::GetInstance()
	{
		static UI instance{};
		return instance;
	}
	
}
