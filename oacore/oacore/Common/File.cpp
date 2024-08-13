

#include "File.h"

namespace oacore
{
	File::File(const _TCHAR* path, const _TCHAR* mode)
	{
		Open(path, mode);
	}

	File::~File()
	{
		Close();
	}

	BOOL File::Open(CONST _TCHAR* path, CONST _TCHAR* mode)
	{
		m_fd = _tfopen(path, mode);

		if (m_fd)
			return TRUE;
		else
			return FALSE;
	}
	VOID File::Close()
	{
		if (m_fd)
		{
			fclose(m_fd);
			m_fd = NULL;
		}
	}
	SIZE_T File::Size()
	{
		if (m_fd == NULL)
			return -1;

		fseek(m_fd, 0, SEEK_END);
		return ftell(m_fd);
	}
	BOOL File::Read(LONG offset, VOID* buffer, SIZE_T size)
	{
		if (m_fd == NULL)
			return FALSE;

		fseek(m_fd, offset, SEEK_SET);
		
		if (fread(buffer, sizeof(CHAR), size, m_fd) != size)
			return FALSE;

		return TRUE;
	}

	BOOL File::Write(LONG offset, CONST VOID* buffer, SIZE_T size)
	{
		if (m_fd == NULL)
			return FALSE;

		fseek(m_fd, offset, SEEK_SET);

		if (fwrite(buffer, sizeof(CHAR), size, m_fd) != size)
			return FALSE;

		return TRUE;
	}
}