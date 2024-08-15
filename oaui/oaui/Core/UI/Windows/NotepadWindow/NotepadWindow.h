#pragma once

#pragma once
#include "oaui/Core/UI/Window.h"
#include "oaui/Core/UI/UI.h"

#define OAUI_NOTEPAD_WINDOW_MAX_BUFFER_LEN (4 * 1024 * 1024)

namespace oaui
{
	class NotepadWindow : public Window
	{
	private:
		char m_notepadContent[OAUI_NOTEPAD_WINDOW_MAX_BUFFER_LEN];
	public:
		NotepadWindow();

		char* GetNotepadContent();
		void ClearNotepadContent();

		void Render(UI* ui);
	};
}
