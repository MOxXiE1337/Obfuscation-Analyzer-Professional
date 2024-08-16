#pragma once
#include "oacore/oacore.h"
#include "oacore/Interface/IDisassembler.h"
#include "oacore/Common/Database.h"

namespace oacore
{
	enum _AnalyzerLoadStatus
	{
		ANALYZER_LOAD_SUCCESS,
		ANALYZER_FILE_DOESNT_EXIST,
		ANALYZER_NOT_A_PE_FILE,
		ANALYZER_UNKNOWN_FILE_TYPE, // Not PE file or Database file, (shouldn't appear, cuz file selecting dialog filters the file type)
		ANALYZER_PE_LOAD_FAIL,
		ANALYZER_DATABASE_LOAD_FAIL,
		ANALYZER_PE_NOT_X64
	};

	enum _AnalyzerSaveStatus
	{
		ANALYZER_SAVE_SUCCESS,
		ANALYZER_EMPTY_PATH,
		ANALYZER_SAVE_FAIL 
	};


	class IAnalyzer
	{
	public:
		virtual ~IAnalyzer() = default;
		virtual bool           IsLoaded() const = 0;

		virtual IDisassembler* GetDisassembler() = 0;
		virtual Database*      GetDatabase() = 0;

		virtual uintptr_t      GetImagebase() const = 0;
		virtual void           RebaseProgram(uintptr_t imagebase) = 0;

		virtual unsigned int   GetComponentLastError(_OacoreComponent component) const = 0;
		virtual void           SetComponentLastError(_OacoreComponent component, int error) = 0;

		virtual _AnalyzerLoadStatus LoadFile(const std::string& path) = 0;
		virtual _AnalyzerSaveStatus SaveFile(const std::string& path) = 0;

	public:
		// for thread safe balabala
		virtual void           _SetDestructCallback(const std::function<void(IAnalyzer*)>& callback) = 0;
	};

	void OACORE_API CreateAnalyzer(std::shared_ptr<IAnalyzer>& ptr);
}
