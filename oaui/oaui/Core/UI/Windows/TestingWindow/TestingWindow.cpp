#ifndef NDEBUG

#include "TestingWindow.h"

#include "oaui/Core/State/State.h"
#include "oacore/Interface/IDisassembler.h"

ZydisFormatter formatter;

namespace oaui
{
	void _DisassemblerTest(UI* ui)
	{
		if (ImGui::CollapsingHeader("Disassembler Test"))
		{
			std::shared_ptr<oacore::IAnalyzer> analyzer = State::GetInstance().GetAnalyzer();
			oacore::IDisassembler* disassembler = analyzer->GetDisassembler();
			auto &instructions = disassembler->GetInstructions();

			for (auto& i : instructions)
			{
				char buffer[256];
				ZydisFormatterFormatInstruction(&formatter, &i.second->Instruction, i.second->Operands.data(),
					i.second->Instruction.operand_count_visible, buffer, sizeof(buffer), i.first, ZYAN_NULL);

				ImGui::Text("%p | %s", i.first, buffer);
			}
		}
	}

	TestingWindow::TestingWindow() : Window(true)
	{
		ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);
	}

	void TestingWindow::Render(UI* ui)
	{
		ImGui::Begin("Testing");

		_DisassemblerTest(ui);

		ImGui::End();
	}
}

#endif
