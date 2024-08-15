#pragma once
#include "oacore/oacore.h"

namespace oacore
{
	enum _PELoadStatus
	{
		PE_LOAD_SUCCESS,
		PE_FILE_DOESNT_EXIST,
		PE_NOT_A_PE_FILE,
		PE_READ_DOS_HEADER_FAIL,
		PE_READ_NT_HEADERS_FAIL,
		PE_READ_SECTION_HEADERS_FAIL,
		PE_COPY_SECTION_FAIL,
		PE_ALLOC_MEMORY_FAIL,
		PE_NOT_X64,

		PE_DATABASE_CORRUPTED
	};

	class IPELoader
	{
	public:
		virtual ~IPELoader() = default;
	};
}
