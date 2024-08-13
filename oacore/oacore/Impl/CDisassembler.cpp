#include "CDisassembler.h"

namespace oacore
{
	CDisassembler::CDisassembler()
	{

		// initialize zydis decoder
		ZydisDecoderInit(&m_decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
	}
	CDisassembler::~CDisassembler()
	{
	}

}

