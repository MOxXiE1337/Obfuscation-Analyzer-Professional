#include "State.h"
#include "oaui/Utils/Utils.h"

namespace oaui
{
    void RecordOacoreError(const char* text)
    {
        State::GetInstance().GetUI()->Error(text);
    }

    // To prevent from choking GUI thread
    void _LoadFileRoutine(State* state, std::string* path)
    {
        std::unique_ptr<std::string> ptr{ path };

        using namespace oacore;
        IAnalyzer* analyzer = state->GetAnalyzer();

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
            SetWindowTextA(state->GetUI()->GetHWND(), (std::string("Obfuscation Analyzer Professional - ") + *path).c_str());
            break;
        }
    }

    // To prevent from choking GUI thread
    void _SaveFileRoutine(State* state, std::string* path)
    {
        std::unique_ptr<std::string> ptr{ path };

        using namespace oacore;



    }


    State::State() 
    {
        m_analyzer = nullptr;
        m_database = nullptr;
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

    oacore::Database* State::GetDatabase()
    {
        return m_database;
    }

    UI* State::GetUI()
    {
        return &m_ui;
    }

    void State::LoadFile(const std::string& path)
    {
        m_ui.Log("Loading %s...", path.c_str());

        std::thread t{ _LoadFileRoutine , this, new std::string(path)};
        t.detach();
    }

    void State::Save(const std::string& path, bool reset)
    {
        if (!m_analyzer->IsLoaded())
            return;

        

        if (reset)
            Reset();
    }

    void State::Reset()
    {
        oacore::CloseAnalyzer(m_analyzer);
        m_analyzer = oacore::CreateAnalyzer();

        m_database = m_analyzer->GetDatabase();

        SetWindowTextA(m_ui.GetHWND(), "Obfuscation Analyzer Professional");
    }


    bool State::Initialize(HWND hwnd, ID3D11Device* device)
    {
        m_analyzer = oacore::CreateAnalyzer();
        m_database = m_analyzer->GetDatabase();;

        if (m_analyzer == nullptr)
            return false;

        oacore::SetRecordHook(2, RecordOacoreError);

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

