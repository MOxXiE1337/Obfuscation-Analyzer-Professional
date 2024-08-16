#include "oacore.h"

namespace oacore
{
	void _DefaultRecord(const char* text)
	{
	}

	InfoRecordFn Log = _DefaultRecord;
	InfoRecordFn Warn = _DefaultRecord;
	InfoRecordFn Error = _DefaultRecord;

	void Record(int id, const char* text, ...)
	{
		static char buffer[512] = { 0 };
		va_list ap;
		va_start(ap, text);
		vsprintf_s(buffer, text, ap);
		va_end(ap);
		(&Log)[id](buffer);
	}

	InfoRecordFn oacore::SetRecordHook(int id, InfoRecordFn hook)
	{
		if (id > 2 || id < 0)
			return nullptr;
		InfoRecordFn old = (&Log)[id];
		(&Log)[id] = hook;
		return old;
	}
}

