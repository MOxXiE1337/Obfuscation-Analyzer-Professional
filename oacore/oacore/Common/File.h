#pragma once
#include "oacore.h"

namespace oacore
{
	class OACORE_API File
	{
	private:
		FILE*  m_fd;
	public:
		File() = default;
		File(CONST _TCHAR* path, CONST _TCHAR* mode);
		~File();

		BOOL   Open(CONST _TCHAR* path, CONST _TCHAR* mode);
		VOID   Close();
		SIZE_T Size();
		BOOL Read(LONG offset, VOID* buffer, SIZE_T size);
		BOOL Write(LONG offset, CONST VOID* buffer, SIZE_T size);
	};
}
