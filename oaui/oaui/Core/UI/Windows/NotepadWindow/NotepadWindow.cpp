#include "NotepadWindow.h"
#include "oaui/Core/State/State.h"
#include "oaui/Utils/Utils.h"

#include "imgui_internal.h"
#include "imstb_textedit.h"

namespace oaui
{
	NotepadWindow::NotepadWindow() : Window()
	{
		m_notepadContent[0] = '\0';
	}

	char* NotepadWindow::GetNotepadContent()
	{
		return m_notepadContent;
	}

	void NotepadWindow::ClearNotepadContent()
	{
		m_notepadContent[0] = '\0';
	}

	void NotepadWindow::Render(UI* ui)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		oacore::IAnalyzer* analyzer = ui->GetState()->GetAnalyzer();
		
		if(!analyzer->IsLoaded())
			return;

		ImGui::Begin(u8"\uE620 Database notepad", &m_show, ImGuiWindowFlags_NoCollapse);

		if (ImGui::BeginPopupContextWindow())
		{
			ImGui::PushStyleColor(ImGuiCol_Border, { 0,0,0,0 });
			if (ImGui::Button("Close"))
			{
				Close();
				ImGui::CloseCurrentPopup();
			}
	
			ImGui::PopStyleColor();
			ImGui::EndPopup();
		}

		ImGui::InputTextMultiline("##Database notepad", m_notepadContent, OAUI_NOTEPAD_WINDOW_MAX_BUFFER_LEN, { ImGui::GetWindowSize().x - style.WindowPadding.x * 2,ImGui::GetWindowSize().y - style.WindowPadding.y * 2 - 25 });	

		if (ImGui::BeginPopupContextItem())
		{
			ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 0));
			if (ImGui::Button("Clear"))
			{
				ClearNotepadContent();
				ImGui::CloseCurrentPopup();
			}
			ImGui::PopStyleColor();
			ImGui::EndPopup();
		}

		ImGui::End();
	}



}

