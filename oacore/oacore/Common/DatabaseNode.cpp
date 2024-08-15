#include "Database.h"

namespace oacore
{
	void _DeleteChildNodes(DatabaseNode* node)
	{	
		DatabaseNode* current = node;
		DatabaseNode* next = nullptr;
		while (current)
		{
			next = current->NextSiblingNode();
			delete current;
			current = next;
		}

	}

	DatabaseNode::DatabaseNode(const std::string& name) 
	{
		m_lock = new std::shared_mutex;
		m_name = new std::string{ name };
		m_text = new std::string{};
		m_childNode = nullptr;
		m_prevSiblingNode = nullptr;
		m_nextSiblingNode = nullptr;
	}

	DatabaseNode::~DatabaseNode()
	{
		DeleteChildNodes();
		delete m_lock;
		delete m_name;
		delete m_text;
	}

	void DatabaseNode::Lock()
	{
		m_lock->lock();
	}

	void DatabaseNode::LockShared()
	{
		m_lock->lock_shared();
	}

	void DatabaseNode::Unlock()
	{
		m_lock->unlock();
	}

	void DatabaseNode::UnlockShared()
	{
		m_lock->lock_shared();
	}

	std::string DatabaseNode::Name()
	{
		std::shared_lock<std::shared_mutex> guard{ *m_lock };
		return *m_name;
	}

	std::string DatabaseNode::Text()
	{
		std::shared_lock<std::shared_mutex> guard{ *m_lock };
		return *m_text;
	}

	void DatabaseNode::SetText(const std::string& test)
	{
		std::unique_lock<std::shared_mutex> guard{ *m_lock };
		*m_text = test;
	}

	DatabaseNode* DatabaseNode::PrevSiblingNode()
	{
		std::shared_lock<std::shared_mutex> guard{ *m_lock };
		return m_prevSiblingNode;
	}

	DatabaseNode* DatabaseNode::NextSiblingNode()
	{
		std::shared_lock<std::shared_mutex> guard{ *m_lock };
		return m_nextSiblingNode;
	}

	DatabaseNode* DatabaseNode::ChildNode()
	{
		std::shared_lock<std::shared_mutex> guard{ *m_lock };
		return m_childNode;
	}

	void DatabaseNode::InsertChildNode(DatabaseNode* node)
	{
		std::unique_lock<std::shared_mutex> guard{ *m_lock };
		std::unique_lock<std::shared_mutex> node_guard{ *node->m_lock };

		if (node != nullptr)
		{
			// Only node without siblings is allowed to insert
			if (node->m_prevSiblingNode == nullptr && node->m_nextSiblingNode == nullptr)
			{
				if (m_childNode == nullptr)
				{
					m_childNode = node;
				}
				else
				{
					DatabaseNode* lastSiblingNode = m_childNode;
					while (lastSiblingNode->NextSiblingNode())
					{
						lastSiblingNode = lastSiblingNode->NextSiblingNode();
					}

					node->m_prevSiblingNode = lastSiblingNode;
					node->m_nextSiblingNode = nullptr;

					lastSiblingNode->Lock();
					lastSiblingNode->m_nextSiblingNode = node;
					lastSiblingNode->Unlock();
				}
			}
		}
	}

	DatabaseNode* DatabaseNode::FindNodeInChild(const std::string& name, int order)
	{
		std::shared_lock<std::shared_mutex> guard{ *m_lock };

		if (order == -1)
			return nullptr; // For directly create new element

		DatabaseNode* node = m_childNode;
		int           curOrder = 0;
		while (node)
		{
			if(*node->m_name == name)
			{
				if (order == curOrder)
					return node;
				curOrder++;
			}
			node = node->NextSiblingNode();
		}

		return nullptr;
	}

	size_t DatabaseNode::GetChildNodesNumber()
	{
		std::shared_lock<std::shared_mutex> guard{ *m_lock };

		size_t num = 0;
		DatabaseNode* node = m_childNode;

		while (node)
		{
			num++;
			node = node->NextSiblingNode();
		}

		return num;
	}

	void DatabaseNode::DeleteChildNodes()
	{
		std::unique_lock<std::shared_mutex> guard{ *m_lock };
		_DeleteChildNodes(m_childNode);
		m_childNode = nullptr;
	}
}

