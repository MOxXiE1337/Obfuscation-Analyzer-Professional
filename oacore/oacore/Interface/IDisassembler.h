#pragma once
#include "oacore/oacore.h"

#include "zydis/Zydis.h"

namespace oacore
{
	struct DecodedInstruction
	{
		ZydisDecodedInstruction Instruction;
		std::array<ZydisDecodedOperand, ZYDIS_MAX_OPERAND_COUNT> Operands;
	};

	class IDisassembler
	{
	public:
		virtual ~IDisassembler() = default;

		// If numberOfInstructions == -1, it will disassemble until reaches address_end, return the instruction number that disassembler disassembled
		virtual size_t Disassemble(uintptr_t address, uintptr_t address_end, size_t numberOfInstructions = 1) = 0;

		virtual DecodedInstruction* GetInstruction(uintptr_t address) = 0;
		virtual std::unordered_map<uintptr_t, std::shared_ptr<DecodedInstruction>>& GetInstructions() = 0;
	};
}
