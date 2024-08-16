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

	size_t CDisassembler::Disassemble(uintptr_t address, uintptr_t address_end, size_t numberOfInstructions)
	{
		size_t    count = 0;
		size_t    instructionsDisassembled = 0;
		uintptr_t curAddress = address;

		while (curAddress < address_end && count < numberOfInstructions)
		{
			if (m_instructionCache.find(curAddress) != m_instructionCache.end())
			{
				count++;
				curAddress += m_instructionCache[curAddress]->Instruction.length;
				continue;
			}

			if (IsBadReadPtr((void*)curAddress, sizeof(uint8_t)) == TRUE)
			{
				return instructionsDisassembled;
			}

			ZydisDecodedInstruction instruction{};
			std::array<ZydisDecodedOperand, 10> operands;
			if (ZYAN_FAILED(ZydisDecoderDecodeFull(&m_decoder, (void*)curAddress, address_end - curAddress, &instruction, operands.data())))
			{
				Record(0, "[ CDisassembler ] Failed to disassemble address %p, skipping 1 byte", curAddress);
				count++;
				curAddress++;
				continue;
			}

			m_instructionCache[curAddress] = std::make_shared<DecodedInstruction>(DecodedInstruction{ instruction,operands });

			count++;
			curAddress += instruction.length;
		}

		return instructionsDisassembled;
	}

	DecodedInstruction* CDisassembler::GetInstruction(uintptr_t address)
	{
		auto it = m_instructionCache.find(address);
		if (it == m_instructionCache.end())
		{
			if (Disassemble(address, address + ZYDIS_MAX_INSTRUCTION_LENGTH, 1) == 0)
				return nullptr;
			it = m_instructionCache.find(address);
		}

		return it != m_instructionCache.end() ? it->second.get() : nullptr;
	}

	std::unordered_map<uintptr_t, std::shared_ptr<DecodedInstruction>>& CDisassembler::GetInstructions()
	{
		return m_instructionCache;
	}

}

