#include "UI.h"

#include "Core/Loader/Loader.h"

namespace oaui
{
	void UI::SectionsWindow()
	{
		Loader& loader = Loader::GetInstance();
		ImGuiStyle& style = ImGui::GetStyle();

		oacore::IPELoader* peLoader = nullptr;

		if (!Loader::GetInstance().IsLoaded())
			return;

		if (!m_showSectionsWindow)
			return;

		peLoader = loader.GetAnalyzer()->GetPELoader();

		ImGui::Begin(u8"\uE78C Sections", &m_showSectionsWindow, ImGuiWindowFlags_NoCollapse);

		if (ImGui::BeginTable("##Sections Table", 4, ImGuiTableFlags_Resizable))
		{
			ImGui::TableSetupColumn("Name");
			ImGui::TableSetupColumn("Start");
			ImGui::TableSetupColumn("End");
			ImGui::TableSetupColumn("Protect");

			ImGui::TableHeadersRow();

			for (int row = 0; row < peLoader->GetNumberOfSections(); row++)
			{
				IMAGE_SECTION_HEADER& curSection = peLoader->GetSectionHeaders()[row];

				ImGui::TableNextRow();

				// Name
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(u8"\uE78C %s", curSection.Name);

				// Start
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%p", loader.GetAnalyzer()->GetImagebase() + curSection.VirtualAddress);

				// End
				ImGui::TableSetColumnIndex(2);
				ImGui::Text("%p", loader.GetAnalyzer()->GetImagebase() + curSection.VirtualAddress + curSection.Misc.VirtualSize);

				// Protect
				ImGui::TableSetColumnIndex(3);
				std::string protect{};

				if (curSection.Characteristics & IMAGE_SCN_MEM_EXECUTE)
					protect += "E ";
				else
					protect += "- ";
				if (curSection.Characteristics & IMAGE_SCN_MEM_READ)
					protect += "R ";
				else
					protect += "- ";
				if(curSection.Characteristics & IMAGE_SCN_MEM_WRITE)
					protect += "W ";
				else
					protect += "- ";

				ImGui::Text(protect.c_str());
				
			}
			ImGui::EndTable();
		}

	
		ImGui::End();
	}
}