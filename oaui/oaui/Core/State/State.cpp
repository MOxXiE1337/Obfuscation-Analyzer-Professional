#include "State.h"
#include "oaui/Utils/Utils.h"
#include <iostream>

namespace oaui
{
    void _RecordOacoreLog(const char* text)
    {
        State::GetInstance().GetUI()->Log(text);
    }

    void _RecordOacoreWarn(const char* text)
    {
        State::GetInstance().GetUI()->Warn(text);
    }

    void _RecordOacoreError(const char* text)
    {
        State::GetInstance().GetUI()->Error(text);
    }

    // for reset function
    void _AnalyzerDestructCallback(oacore::IAnalyzer* analyzer)
    {
        // Create a new analyzer
        oacore::CreateAnalyzer(State::GetInstance().m_analyzer);
        State::GetInstance().GetAnalyzer()->_SetDestructCallback(_AnalyzerDestructCallback);
    }

    // To prevent from choking GUI thread
    void _LoadFileRoutine(State* state, std::shared_ptr<oacore::IAnalyzer> analyzer, std::unique_ptr<std::string> path)
    {
        using namespace oacore;
        std::lock_guard<std::mutex> guard{ State::GetInstance().IsLoadOrSaving()};

        _AnalyzerLoadStatus status = analyzer->LoadFile(*path);

        switch (status)
        {
        case ANALYZER_DATABASE_LOAD_FAIL:
            if (analyzer->GetComponentLastError(COMPONENT_DATABASE) == DATABASE_XML_PARSE_FAIL)
                MessageBoxA(NULL, "Failed to parse database!", "Error", MB_ICONERROR);
            if (analyzer->GetComponentLastError(COMPONENT_DATABASE) == DATABASE_CORRUPTED)
                MessageBoxA(NULL, "Database is corrupted!", "Error", MB_ICONERROR);
            return;
        case ANALYZER_LOAD_SUCCESS:
            SetWindowTextA(State::GetInstance().GetUI()->GetHWND(), (std::string("Obfuscation Analyzer Professional - ") + *path).c_str());
            break;
        }
    }

    void _SaveFileRoutine(State* state, std::shared_ptr<oacore::IAnalyzer> analyzer, std::unique_ptr<std::string> path)
    {
        using namespace oacore;
        std::lock_guard<std::mutex> guard{ State::GetInstance().IsLoadOrSaving() };

        _AnalyzerSaveStatus status = analyzer->SaveFile(*path);

        std::string newPath{};
        switch (status)
        {
        // the path in database is empty (normally it shouldn't be empty)
        case ANALYZER_EMPTY_PATH:
             Utils::SelectFile(State::GetInstance().GetUI()->GetHWND(), "Database File (*.odb)\0*.odb\0\0", newPath, OFN_PATHMUSTEXIST | OFN_EXPLORER);
             _SaveFileRoutine(state, analyzer, std::make_unique<std::string>(newPath));
            break;
        case ANALYZER_SAVE_FAIL:
            MessageBoxA(NULL, "Failed to save file!", "Error", MB_ICONERROR);
            break;
        case ANALYZER_SAVE_SUCCESS:
            break;
        }

    }

    State::State() : m_analyzer(), m_isLoadingOrSaving()
    {
        
    }

    State::~State()
    {

        Shutdown();
    }


    UI* State::GetUI()
    {
        return &m_ui;
    }

    std::shared_ptr<oacore::IAnalyzer> State::GetAnalyzer()
    {
        return m_analyzer;
    }

    std::mutex& State::IsLoadOrSaving()
    {
        return m_isLoadingOrSaving;
    }

    void State::LoadFile(const std::string& path, bool createNewThread)
    {
        if (createNewThread)
        {
            std::thread{ _LoadFileRoutine , this,  m_analyzer, std::make_unique<std::string>(path) }.detach();
        }
        else
        {
            _LoadFileRoutine(this, m_analyzer, std::make_unique<std::string>(path));
        }
    }

    void State::Save(const std::string& path, bool createNewThread)
    {
        if (createNewThread)
        {
            std::thread { _SaveFileRoutine , this,  m_analyzer, std::make_unique<std::string>(path) }.detach();
        }
        else
        {
            _SaveFileRoutine(this, m_analyzer, std::make_unique<std::string>(path));
        }
    }

    void State::Reset()
    {
        std::shared_ptr<oacore::IAnalyzer> oldAnalyzer = m_analyzer;

        // Free old analyzer 
        oldAnalyzer.reset();

        SetWindowTextA(m_ui.GetHWND(), "Obfuscation Analyzer Professional");
    }


    bool State::Initialize(HWND hwnd, ID3D11Device* device)
    {
        oacore::CreateAnalyzer(m_analyzer);
        m_analyzer->_SetDestructCallback(_AnalyzerDestructCallback);

        oacore::SetRecordHook(0, _RecordOacoreLog);
        oacore::SetRecordHook(1, _RecordOacoreWarn);
        oacore::SetRecordHook(2, _RecordOacoreError);

        if (!m_ui.Initialize(hwnd, device))
            return false;

        
        return true;
    }


    void State::Shutdown()
    {
        m_ui.Shutdown();

    }

    State& State::GetInstance()
    {
        static State instance{};
        return instance;
    }
}

