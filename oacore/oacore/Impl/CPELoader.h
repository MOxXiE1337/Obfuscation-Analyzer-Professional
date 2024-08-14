#pragma once

#include "Interfaces/IPELoader.h"

namespace oacore
{
	

	class CPELoader : public IPELoader
	{
	private:
		std::string           m_filePath;

		uintptr_t             m_imagebase;
		uintptr_t             m_imagesize;
		DWORD64               m_oepOffset;
		
		IMAGE_DOS_HEADER      m_dosHeader;
		IMAGE_NT_HEADERS64    m_ntHeaders;
		PIMAGE_SECTION_HEADER m_sectionHeaders;
		size_t                m_numberOfSections;

	private:

	public:
		~CPELoader();

	public:

		DWORD64                      GetImagebase();
		SIZE_T                       GetImagesize();
		DWORD64 		             GetEntrypoint();
		CONST PIMAGE_DOS_HEADER      GetDosHeader();
		CONST PIMAGE_NT_HEADERS      GetNTHeaders();
		CONST PIMAGE_FILE_HEADER     GetFileHeader();
		CONST PIMAGE_OPTIONAL_HEADER GetOptionalHeader();
		CONST PIMAGE_SECTION_HEADER  GetSectionHeaders();
		SIZE_T                       GetNumberOfSections();


	public:
		VOID                         _SetImagebase(DWORD64 imagebase);
		VOID                         _SetImagesize(DWORD64 imagesize);
		VOID 			             _SetEntrypoint(DWORD64 rva);
		VOID                         _SetSectionHeaders(CONST PIMAGE_SECTION_HEADER* headers);
		VOID                         _SetNumberOfSections(SIZE_T number);

	public:
		PE_LOAD_STATUS               LoadFile(CONST _TCHAR* path);
		
	};
}
