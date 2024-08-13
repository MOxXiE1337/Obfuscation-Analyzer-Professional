#pragma once
#include "Interfaces/IDisassembler.h"

#include "zydis/Zydis.h"

namespace oacore
{
	class CDisassembler : public IDisassembler
	{
	private:


		ZydisDecoder m_decoder;

	public:
		CDisassembler();
		~CDisassembler();

	};
}
