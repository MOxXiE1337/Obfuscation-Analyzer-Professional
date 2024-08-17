#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

#include "oaui/Core/State/State.h"
#include "oaui/Core/UI/Windows/SavingWindow/SavingWindow.h"

// Data
ID3D11Device* d3dDevice = nullptr;
ID3D11DeviceContext* d3dDeviceContext = nullptr;
IDXGISwapChain* swapChain = nullptr;
bool swapChainOccluded = false;
UINT resizeWidth = 0, resizeHeight = 0;
ID3D11RenderTargetView* mainRenderTargetView = nullptr;

bool createDeviceD3D(HWND hWnd);
void cleanupDeviceD3D();
void createRenderTarget();
void cleanupRenderTarget();
LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int, char**)
{
    // Create application window
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, wndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"oauiClass", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Obfuscation Analyzer Professional", WS_OVERLAPPEDWINDOW, 100, 100, 1600, 900, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!createDeviceD3D(hwnd))
    {
        cleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_MAXIMIZE);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    io.ConfigViewportsNoAutoMerge = true;
    io.ConfigDockingTransparentPayload = true;

    if (!oaui::State::GetInstance().Initialize(hwnd, d3dDevice))
        return -1;

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(d3dDevice, d3dDeviceContext);

    // Our state
    bool showDemoWindow = true;
    bool showAnotherWindow = false;
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        if (swapChainOccluded && swapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        swapChainOccluded = false;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (resizeWidth != 0 && resizeHeight != 0)
        {
            cleanupRenderTarget();
            swapChain->ResizeBuffers(0, resizeWidth, resizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            resizeWidth = resizeHeight = 0;
            createRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        oaui::State::GetInstance().GetUI()->Render();

        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();
        const float clearColorWithAlpha[4] = { clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w };
        d3dDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
        d3dDeviceContext->ClearRenderTargetView(mainRenderTargetView, clearColorWithAlpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        // Present
        HRESULT hr = swapChain->Present(1, 0);   // Present with vsync
        //HRESULT hr = swapChain->Present(0, 0); // Present without vsync
        swapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    oaui::State::GetInstance().Shutdown();

    cleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions
bool createDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 2;
    swapChainDesc.BufferDesc.Width = 0;
    swapChainDesc.BufferDesc.Height = 0;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevels[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, 2, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &d3dDevice, &featureLevel, &d3dDeviceContext);
    if (result == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevels, 2, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &d3dDevice, &featureLevel, &d3dDeviceContext);
    if (result != S_OK)
        return false;

    createRenderTarget();
    return true;
}

void cleanupDeviceD3D()
{
    cleanupRenderTarget();
    if (swapChain) { swapChain->Release(); swapChain = nullptr; }
    if (d3dDeviceContext) { d3dDeviceContext->Release(); d3dDeviceContext = nullptr; }
    if (d3dDevice) { d3dDevice->Release(); d3dDevice = nullptr; }
}

void createRenderTarget()
{
    ID3D11Texture2D* backBuffer;
    swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &mainRenderTargetView);
    backBuffer->Release();
}

void cleanupRenderTarget()
{
    if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = nullptr; }
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    oaui::UI* ui = oaui::State::GetInstance().GetUI();
    std::shared_ptr<oacore::IAnalyzer> analyzer = oaui::State::GetInstance().GetAnalyzer();

    oaui::SavingWindow* savingWindow = reinterpret_cast<oaui::SavingWindow*>(ui->GetWindow(oaui::SAVING_WINDOW));

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_CREATE:
        DragAcceptFiles(hWnd, TRUE);
        break;
    case WM_DROPFILES:
    {
        HDROP drop = reinterpret_cast<HDROP>(wParam);
        UINT fileCount = DragQueryFileA(drop, 0xFFFFFFFF, NULL, 0);

        if (fileCount != 1)
            return 0;

        CHAR filePath[MAX_PATH];

        DragQueryFileA(drop, 0, filePath, MAX_PATH);

        if (analyzer)
        {
            if (analyzer->IsLoaded())
            {
                savingWindow->Show();
                savingWindow->LoadDraggedFile(filePath);
            }
            else
            {
                oaui::Utils::ThreadExecutor([filePath]()
                    {
                        oaui::State::GetInstance().LoadFile(filePath);
                    },
                    oaui::State::GetInstance().IsLoadOrSaving());
            }
        }

        DragFinish(drop);

        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_CLOSE:
        if (analyzer->IsLoaded() && !savingWindow->IsProgramExiting())
        {
            savingWindow->CloseOpenFileDialog();
            savingWindow->ExitProgram();
            savingWindow->Show();
            return 0;
        }

        if (savingWindow->IsProgramExiting())
            return 0;

        return DefWindowProc(hWnd, msg, wParam, lParam);
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        resizeWidth = (UINT)LOWORD(lParam); // Queue resize
        resizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            const RECT* suggestedRect = (RECT*)lParam;
            ::SetWindowPos(hWnd, nullptr, suggestedRect->left, suggestedRect->top, suggestedRect->right - suggestedRect->left, suggestedRect->bottom - suggestedRect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
