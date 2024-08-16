#include <D3DX11tex.h>

#include "UI.h"

#include "oaui/Resources/Iconfont.h"

#include "MenuBar/MainMenuBar/MainMenuBar.h"
#include "Windows/DockspaceWindow/DockspaceWindow.h"

#include "Windows/DatabaseViewerWindow/DatabaseViewerWindow.h"
#include "Windows/NotepadWindow/NotepadWindow.h"
#include "Windows/OutputWindow/OutputWindow.h"

#include "Windows/SavingWindow/SavingWindow.h"

#include "Windows/TestingWindow/TestingWindow.h"

#include "imgui_freetype.h"

#define OAUI_RENDER_WINDOW(window) if(window->IsShowed()) { window->Render(this); }

namespace oaui
{
	
	ID3D11ShaderResourceView* _CreateTextureFromMemory(ID3D11Device* device, void* src, size_t size)
	{

		ID3D11Texture2D* texture2D = NULL;
		D3D11_TEXTURE2D_DESC desc;


		HRESULT result;
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
		loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		loadInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		loadInfo.MipLevels = D3DX11_DEFAULT;  
		loadInfo.MipFilter = D3DX11_FILTER_LINEAR;
		result = D3DX11CreateTextureFromMemory(device, src, size, &loadInfo, NULL, reinterpret_cast<ID3D11Resource**>(&texture2D), NULL);

		if (result != S_OK)
		{
			return NULL;
		}
		texture2D->GetDesc(&desc);

		ID3D11ShaderResourceView* textureView = NULL;

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		device->CreateShaderResourceView(texture2D, &srvDesc, &textureView);

		return textureView;
	} 

	UI::UI()
	{		
		m_hwnd = NULL;
		m_textures = {};

		m_mainMenuBar = std::make_unique<MainMenuBar>();
		m_dockspaceWindow = std::make_unique<DockspaceWindow>();
		m_databaseViewerWindow = std::make_unique<DatabaseViewerWindow>();
		m_notepadWindow = std::make_unique<NotepadWindow>();
		m_outputWindow = std::make_unique<OutputWindow>();

		m_savingWindow = std::make_unique<SavingWindow>();

#ifndef NDEBUG
			m_testingWindow = std::make_unique <TestingWindow>();
#endif
	}

	UI::~UI()
	{
	}

	bool UI::_InitializeStyle()
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

	bool UI::_InitializeFonts()
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


		ImFont* iconFont = io.Fonts->AddFontFromMemoryCompressedTTF(Resources::IconFontCompressedData, sizeof(Resources::IconFontCompressedDataSize), 18, &config1, ranges1);
		if (iconFont == nullptr)
		{
			MessageBoxA(m_hwnd, "Failed to load icon font!", "Error", MB_ICONERROR);
			return false;
		}

		io.Fonts->Build();
		return true;
	}

	bool UI::_InitializeTextures()
	{
	
		static auto createTexture = [&](const std::string& name, void* src, size_t size) -> bool
			{
				ID3D11ShaderResourceView* texture = _CreateTextureFromMemory(m_device, src, size);
				if (texture == nullptr)
				{
					std::string errorText = "Failed to create texture \"" + name + "\"!";
					MessageBoxA(m_hwnd, errorText.c_str(), "Error", MB_ICONERROR);
					return false;
				}
				m_textures[name] = texture;
				return true;
			};

		return true;
	}

	bool UI::Initialize(HWND hwnd, ID3D11Device* device)
	{
		m_hwnd = hwnd;
		m_device = device;

		if (!_InitializeFonts())
			return false;
		if (!_InitializeStyle())
			return false;
		if (!_InitializeTextures())
			return false;
		return true;
	}

	void UI::Shutdown()
	{
		return;
	}

	ImTextureID UI::GetTexture(const std::string& name)
	{
		if (m_textures.count(name) == 0)
			return ImTextureID{  };
		return m_textures[name];
	}

	Window* UI::GetWindow(_WindowId id)
	{
		switch (id)
		{
		case DOCKSPACE_WINDOW:
			return m_dockspaceWindow.get();
		case DATABASE_VIEWER_WINDOW:
			return m_databaseViewerWindow.get();
		case NOTEPAD_WINDOW:
			return m_notepadWindow.get();
		case OUTPUT_WINDOW:
			return m_outputWindow.get();
		case SAVING_WINDOW:
			return m_savingWindow.get();
		default:
			return nullptr;
		}
	}

	void UI::Log(const char* text, ...)
	{
		
		va_list ap;
		va_start(ap, text);
		reinterpret_cast<OutputWindow*>(m_outputWindow.get())->OutputMessage(ImGui::GetStyleColorVec4(ImGuiCol_Text), text, ap);
		va_end(ap);
	}

	void UI::Warn(const char* text, ...)
	{
		va_list ap;
		va_start(ap, text);
		reinterpret_cast<OutputWindow*>(m_outputWindow.get())->OutputMessage(IM_COL32(255, 138, 37, 255), text, ap);
		va_end(ap);
	}

	void UI::Error(const char* text, ...)
	{
		va_list ap;
		va_start(ap, text);
		reinterpret_cast<OutputWindow*>(m_outputWindow.get())->OutputMessage(IM_COL32(255, 0, 0, 255), text, ap);
		va_end(ap);
	}

	void UI::LogV(const char* text, va_list ap)
	{

		reinterpret_cast<OutputWindow*>(m_outputWindow.get())->OutputMessage(ImGui::GetStyleColorVec4(ImGuiCol_Text), text, ap);
	}

	void UI::WarnV(const char* text, va_list ap)
	{
		reinterpret_cast<OutputWindow*>(m_outputWindow.get())->OutputMessage(IM_COL32(255, 138, 37, 255), text, ap);
	}

	void UI::ErrorV(const char* text, va_list ap)
	{
		reinterpret_cast<OutputWindow*>(m_outputWindow.get())->OutputMessage(IM_COL32(255, 0, 0, 255), text, ap);
	}

	void UI::Render()
	{
		m_mainMenuBar->Render(this);
		
		OAUI_RENDER_WINDOW(m_dockspaceWindow);
		OAUI_RENDER_WINDOW(m_databaseViewerWindow);
		OAUI_RENDER_WINDOW(m_notepadWindow);
		OAUI_RENDER_WINDOW(m_outputWindow);

		OAUI_RENDER_WINDOW(m_savingWindow);

#ifndef NDEBUG
		OAUI_RENDER_WINDOW(m_testingWindow);
#endif
	}
}
