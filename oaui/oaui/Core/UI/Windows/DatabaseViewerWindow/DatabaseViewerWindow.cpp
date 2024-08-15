#include "DatabaseViewerWindow.h"

#include "oaui/Core/State/State.h"

namespace oaui
{
	void _RenderDatabaseTree(oacore::DatabaseNode* node)
	{
		if (node == nullptr)
			return;

		if (node->ChildNode() == nullptr)
		{
			ImGui::BulletText("%s: %s", node->Name().c_str(), node->Text().c_str());
			return;
		}

		if (ImGui::TreeNode((node->Name() + "##" + std::to_string(reinterpret_cast<uintptr_t>(node))).c_str()))
		{
			oacore::DatabaseNode* curNode = node->ChildNode();
			while (curNode)
			{
				_RenderDatabaseTree(curNode);
				curNode = curNode->NextSiblingNode();
			}
			ImGui::TreePop();
		}
	}


	DatabaseViewerWindow::DatabaseViewerWindow() : Window(false)
	{
	}

	void DatabaseViewerWindow::Render(UI* ui)
	{
		State* state = ui->GetState();
		oacore::Database* database = state->GetDatabase();
		oacore::DatabaseNode* root = database->GetRoot();
		oacore::DatabaseNode* curNode = root->ChildNode();

		if (!state->GetAnalyzer()->IsLoaded())
			return;

		ImGui::Begin(u8"\uE7E8 Database viewer", &m_show, ImGuiWindowFlags_NoCollapse);

		while (curNode)
		{
			if (ImGui::CollapsingHeader(curNode->Name().c_str(), ImGuiTreeNodeFlags_None))
			{
				ImGui::SetCursorPosX(20);
				_RenderDatabaseTree(curNode->ChildNode());
			}
			curNode = curNode->NextSiblingNode();
		}

		ImGui::End();


	}
}

