#include "UI.h"

#include "Core/Loader/Loader.h"

namespace oaui
{
	void UI::NotepadWindow()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		if (!Loader::GetInstance().IsLoaded())
			return;

		if (m_notepadBuffer == nullptr)
		{	
			m_notepadBuffer = (char*)malloc(1024 * 1024 * 8); // a 8 MB buffer
			memset(m_notepadBuffer, 0, 1024 * 1024 * 8);
		}

		if (!m_showNotepadWindow)
			return;

		ImGui::Begin(u8"\uE620 Database notepad", &m_showNotepadWindow, ImGuiWindowFlags_NoCollapse);
		
		ImGui::InputTextMultiline("##Database notepad", m_notepadBuffer, 1024 * 1024 * 8, { ImGui::GetWindowSize().x - style.WindowPadding.x * 2,ImGui::GetWindowSize().y - style.WindowPadding.y * 2 - 25 });
		
		ImGui::End();
	}
}