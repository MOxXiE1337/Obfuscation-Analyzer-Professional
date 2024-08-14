#include "Database.h"

namespace oacore
{
	void _DeleteChildNodes(DatabaseNode* node)
	{	
		DatabaseNode* current = node;
		DatabaseNode* next = nullptr;
		while (node)
		{
			next = node->NextSiblingNode;
			delete node;
			node = next;
		}

	}

	DatabaseNode::DatabaseNode(const std::string& name)
	{
		Name = new std::string{ name };
		Text = new std::string{};
		ChildNode = nullptr;
		PrevSiblingNode = nullptr;
		NextSiblingNode = nullptr;
	}

	DatabaseNode::~DatabaseNode()
	{
		DeleteChildNodes();
	}

	void DatabaseNode::InsertChildNode(DatabaseNode* node)
	{
		if (node != nullptr)
		{
			// Only node without siblings is allowed to insert
			if (node->PrevSiblingNode == nullptr && node->NextSiblingNode == nullptr)
			{
				if (ChildNode == nullptr)
				{
					ChildNode = node;
				}
				else
				{
					DatabaseNode* lastSiblingNode = ChildNode;
					while (lastSiblingNode->NextSiblingNode)
					{
						lastSiblingNode = lastSiblingNode->NextSiblingNode;
					}

					node->PrevSiblingNode = lastSiblingNode;
					node->NextSiblingNode = nullptr;

					lastSiblingNode->NextSiblingNode = node;
				}
			}
		}
	}

	DatabaseNode* DatabaseNode::FindNodeInChild(const std::string& name, int order)
	{
		if (order == -1)
			return nullptr; // For directly create new element

		DatabaseNode* node = ChildNode;
		int           curOrder = 0;
		while (node)
		{
			if(*node->Name == name)
			{
				if (order == curOrder)
					return node;
				curOrder++;
			}
			node = node->NextSiblingNode;
		}

		return nullptr;
	}

	size_t DatabaseNode::GetChildNodesNumber()
	{
		size_t num = 0;
		DatabaseNode* node = ChildNode;

		while (node)
		{
			num++;
			node = node->NextSiblingNode;
		}

		return num;
	}

	void DatabaseNode::DeleteChildNodes()
	{
		_DeleteChildNodes(ChildNode);
		ChildNode = nullptr;
	}
}

