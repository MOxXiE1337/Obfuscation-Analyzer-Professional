#pragma once
#include "oacore/Interface/IDisassembler.h"

namespace oacore
{
	class CDisassembler : public IDisassembler
	{
	private:
		ZydisDecoder m_decoder;
		
		std::unordered_map<uintptr_t, std::shared_ptr<DecodedInstruction>> m_instructionCache;

	public:
		CDisassembler();
		~CDisassembler();

		size_t Disassemble(uintptr_t address, uintptr_t address_end, size_t numberOfInstructions = 1);
		DecodedInstruction* GetInstruction(uintptr_t address);
		std::unordered_map<uintptr_t, std::shared_ptr<DecodedInstruction>>& GetInstructions();

	};
}
