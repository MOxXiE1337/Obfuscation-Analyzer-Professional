#pragma once
#include "oacore.h"

namespace oacore
{
	enum PE_LOAD_STATUS
	{
		PE_LOAD_SUCCESS,
		PE_FILE_DOESNT_EXIST,
		PE_NOT_A_PE_FILE,
		PE_READ_DOS_HEADER_FAIL,
		PE_READ_NT_HEADERS_FAIL,
		PE_READ_SECTION_HEADERS_FAIL,
		PE_COPY_SECTION_FAIL,
		PE_ALLOC_MEMORY_FAIL,
		PE_NOT_X64
	};

	class IPELoader
	{
	public:
		virtual ~IPELoader() = default;
	public:
		virtual DWORD64                      GetImagebase() = 0;
		virtual SIZE_T                       GetImagesize() = 0;
		virtual DWORD64 			         GetEntrypoint() = 0;
		virtual CONST PIMAGE_DOS_HEADER      GetDosHeader() = 0;
		virtual CONST PIMAGE_NT_HEADERS      GetNTHeaders() = 0;
		virtual CONST PIMAGE_FILE_HEADER     GetFileHeader() = 0;
		virtual CONST PIMAGE_OPTIONAL_HEADER GetOptionalHeader() = 0;
		virtual CONST PIMAGE_SECTION_HEADER  GetSectionHeaders() = 0;
		virtual SIZE_T                       GetNumberOfSections() = 0;
	public:
		// Normally u shouldn't call these interal functions, for loading database
		virtual VOID                         _SetImagebase(DWORD64 imagebase) = 0;
		virtual VOID                         _SetImagesize(DWORD64 imagesize) = 0;
		virtual VOID 			             _SetEntrypoint(DWORD64 rva) = 0;
		virtual VOID                         _SetSectionHeaders(CONST PIMAGE_SECTION_HEADER* headers) = 0;
		virtual VOID                         _SetNumberOfSections(SIZE_T number) = 0;
	public:
		virtual PE_LOAD_STATUS               LoadFile(CONST _TCHAR* path) = 0;
	};
}
