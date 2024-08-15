#pragma once
#include "oaui/Core/UI/Window.h"
#include "oaui/Core/UI/UI.h"


namespace oaui
{
	// The saving window will only appear when you open another file or exit while the file is already open
	class SavingWindow : public Window
	{
	private:
		bool m_openOpenFileDialog;
		bool m_shouldExitProgram;
		bool m_isProgramExiting;
		bool m_loadDraggedFile;
		std::string m_draggedFilePath;

	public:
		SavingWindow();

		// Open file selecting file dialog and load new file
		void OpenOpenFileDialog();
		void CloseOpenFileDialog();
		void ExitProgram();
		bool IsProgramExiting();
		void LoadDraggedFile(const std::string& path);

		void Render(UI* ui);
	};
}
