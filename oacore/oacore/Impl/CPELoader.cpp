#include "CPELoader.h"

namespace oacore
{
    PE_LOAD_STATUS CPELoader::CopySections(File& file)
    {
        for (UINT u = 0; u < m_numberOfSections; u++)
        {
            IMAGE_SECTION_HEADER& cur = m_sectionHeaders[u];

            if (!file.Read(cur.PointerToRawData, (PVOID)(m_imagebase + cur.VirtualAddress), cur.SizeOfRawData))
                return PE_COPY_SECTION_FAIL;

            DWORD oldProtect = PAGE_READWRITE;
            DWORD newProtect = PAGE_READONLY;

            if (cur.Characteristics & IMAGE_SCN_MEM_WRITE)
            {
                newProtect = PAGE_READWRITE;
            }
            else
            {
                if (cur.Characteristics & IMAGE_SCN_MEM_EXECUTE)
                    newProtect = PAGE_EXECUTE_READ;
            }
            VirtualProtect((PVOID)(m_imagebase + cur.VirtualAddress), cur.Misc.VirtualSize, newProtect, &oldProtect);
        }
        
        return PE_LOAD_SUCCESS;
    }

    PE_LOAD_STATUS CPELoader::MapFileToMemory(File& file)
    {
        // Read dos header from file
        if (!file.Read(0, &m_dosHeader, sizeof(IMAGE_DOS_HEADER)))
            return PE_READ_DOS_HEADER_FAIL;

        // Check magic number
        if (m_dosHeader.e_magic != 0x5A4D)
            return PE_NOT_A_PE_FILE;

        // Read NT headers (only x64 is supported)
        if (!file.Read(m_dosHeader.e_lfanew, &m_ntHeaders, sizeof(IMAGE_NT_HEADERS64)))
            return PE_READ_NT_HEADERS_FAIL;
            
        // Check signature
        if (m_ntHeaders.Signature != 0x4550)
            return PE_NOT_A_PE_FILE;

        if (m_ntHeaders.FileHeader.Machine != IMAGE_FILE_MACHINE_AMD64)
            return PE_NOT_X64;
            
        // Read section headers
        m_numberOfSections = m_ntHeaders.FileHeader.NumberOfSections;
        m_sectionHeaders = (PIMAGE_SECTION_HEADER)malloc(sizeof(IMAGE_SECTION_HEADER) * m_numberOfSections);

        if (!m_sectionHeaders)
            return PE_ALLOC_MEMORY_FAIL;

        if (!file.Read(m_dosHeader.e_lfanew + sizeof(IMAGE_NT_HEADERS64), m_sectionHeaders, sizeof(IMAGE_SECTION_HEADER) * m_numberOfSections))
            return PE_READ_SECTION_HEADERS_FAIL;

        // Setup info
        m_imagesize = m_ntHeaders.OptionalHeader.SizeOfImage;

        // Allocate a flat view memory
        m_imagebase = (DWORD64)VirtualAlloc(NULL, m_imagesize, MEM_COMMIT, PAGE_READWRITE);

        if (m_imagebase == 0)
            return PE_ALLOC_MEMORY_FAIL;

        m_oepOffset = m_ntHeaders.OptionalHeader.AddressOfEntryPoint;

        return CopySections(file);
    }

    CPELoader::~CPELoader()
    {
        if (m_imagebase != 0)
        {
            VirtualFree((LPVOID)m_imagebase, m_imagesize, MEM_FREE);
            m_imagebase = 0;
        }
        if (m_sectionHeaders != nullptr)
        {
            free(m_sectionHeaders);
            m_sectionHeaders = nullptr;
        }
    }

    DWORD64 CPELoader::GetImagebase()
    {
        return m_imagebase;
    }

    SIZE_T CPELoader::GetImagesize()
    {
        return m_imagesize;
    }

    DWORD64 CPELoader::GetEntrypoint()
    {
        return m_imagebase + m_oepOffset;
    }

    CONST PIMAGE_DOS_HEADER CPELoader::GetDosHeader()
    {
        return &m_dosHeader;
    }

    CONST PIMAGE_NT_HEADERS CPELoader::GetNTHeaders()
    {
        return &m_ntHeaders;
    }

    CONST PIMAGE_FILE_HEADER CPELoader::GetFileHeader()
    {
        return &m_ntHeaders.FileHeader;
    }

    CONST PIMAGE_OPTIONAL_HEADER CPELoader::GetOptionalHeader()
    {
        return &m_ntHeaders.OptionalHeader;
    }

    CONST PIMAGE_SECTION_HEADER CPELoader::GetSectionHeaders()
    {
        return m_sectionHeaders;
    }

    SIZE_T CPELoader::GetNumberOfSections()
    {
        return m_numberOfSections;
    }

    VOID CPELoader::_SetImagebase(DWORD64 imagebase)
    {
        m_imagebase = imagebase;
    }

    VOID CPELoader::_SetImagesize(DWORD64 imagesize)
    {
        m_imagebase = imagesize;
    }

    VOID CPELoader::_SetEntrypoint(DWORD64 rva)
    {

    }

    VOID CPELoader::_SetSectionHeaders(CONST PIMAGE_SECTION_HEADER* headers)
    {

    }

    VOID CPELoader::_SetNumberOfSections(SIZE_T number)
    {

    }

    PE_LOAD_STATUS CPELoader::LoadFile(CONST _TCHAR* path)
    {
        File file{};
        PE_LOAD_STATUS status = PE_LOAD_SUCCESS;

        if (!file.Open(path, _T("rb")))
            return PE_FILE_DOESNT_EXIST;

        status = MapFileToMemory(file);  

        return status;
    }
}

