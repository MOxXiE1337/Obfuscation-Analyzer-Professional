#pragma once
#include "Common/File.h"

#include "Interfaces/IPELoader.h"

namespace oacore
{
	

	class CPELoader : public IPELoader
	{
	private:
		CONST _TCHAR*         m_filePath;

		DWORD64               m_imagebase;
		SIZE_T                m_imagesize;
		DWORD64               m_oepOffset;
		
		IMAGE_DOS_HEADER      m_dosHeader;
		IMAGE_NT_HEADERS64    m_ntHeaders;
		PIMAGE_SECTION_HEADER m_sectionHeaders;
		SIZE_T                m_numberOfSections;

	private:
		PE_LOAD_STATUS              CopySections(File& file);
		PE_LOAD_STATUS              MapFileToMemory(File& file);

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
		PE_LOAD_STATUS               LoadFile(CONST _TCHAR* path);
		
	};
}
