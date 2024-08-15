#include "oacore.h"

namespace oacore
{
	void _DefaultRecord(const char* text)
	{

	}

	InfoRecordFn Log = _DefaultRecord;
	InfoRecordFn Warn = _DefaultRecord;
	InfoRecordFn Error = _DefaultRecord;

	InfoRecordFn oacore::SetRecordHook(int id, InfoRecordFn hook)
	{
		if (id > 2 || id < 0)
			return nullptr;
		InfoRecordFn old = (&Log)[id];
		(&Log)[id] = hook;
		return old;
	}
}

