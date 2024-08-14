#include "State.h"

namespace oaui
{
    State::State()
    {
        m_ui.m_state = this;
    }

    State::~State()
    {
        if (m_analyzer)
            oacore::CloseAnalyzer(m_analyzer);
    }

    oacore::IAnalyzer* State::GetAnalyzer()
    {
        return m_analyzer;
    }

    UI* State::GetUI()
    {
        return &m_ui;
    }

    void State::LoadFile(const std::string& path)
    {
        m_analyzer->LoadFile(path);

        SetWindowTextA(m_ui.GetHWND(), (std::string("Obfuscation Analyzer Professional - ") + path).c_str());
    }

    void State::Save(const std::string& path, bool reset)
    {

        if (reset)
            Reset();
    }

    void State::Reset()
    {
        oacore::CloseAnalyzer(m_analyzer);
        m_analyzer = oacore::CreateAnalyzer();

        SetWindowTextA(m_ui.GetHWND(), "Obfuscation Analyzer Professional");
    }

    bool State::Initialize(HWND hwnd)
    {
        m_analyzer = oacore::CreateAnalyzer();

        if (m_analyzer == nullptr)
            return false;

        if (!m_ui.Initialize(hwnd))
            return false;
        return true;
    }

    void State::Shutdown()
    {
        m_ui.Shutdown();
    }
}

