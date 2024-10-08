#pragma once
#include "oacore/oacore.h"

#define OACORE_DATABASE_ERROR_STRING "6-?9syz $@/hae0qSs4B.xtcm,aWh}Cz" // random generated

namespace oacore
{
	struct BinaryData
	{
		void* Data;
		size_t Size;
		bool   ShouldFree;

		BinaryData() = default;

		template <typename T>
		BinaryData(const T& obj)
		{
			Size = sizeof(T);
			Data = reinterpret_cast<void*>(&obj);
			ShouldFree = false;
		}

		~BinaryData()
		{
			if (ShouldFree)
				free(Data);
		}
	};

	class OACORE_API DatabaseNode
	{
	private:
		std::shared_mutex* m_lock;
		std::string*  m_name;
		std::string*  m_text;

		DatabaseNode* m_prevSiblingNode;
		DatabaseNode* m_nextSiblingNode;
		DatabaseNode* m_childNode;
	public:

		DatabaseNode(const std::string& name);
		~DatabaseNode();

		void Lock();
		void LockShared();
		void Unlock();
		void UnlockShared();

		std::string   Name();
		std::string   Text();
		void          SetText(const std::string& test);
		DatabaseNode* PrevSiblingNode();
		DatabaseNode* NextSiblingNode();
		DatabaseNode* ChildNode();

		void          InsertChildNode(DatabaseNode* node);
		DatabaseNode* FindNodeInChild(const std::string& name, int order = 0);
		size_t        GetChildNodesNumber();
		void          DeleteChildNodes();
	};

	enum _DatabaseLoadStatus
	{
		DATABASE_LOAD_SUCCESS,
		DATABASE_FILE_OPEN_FAIL,
		DATABASE_XML_PARSE_FAIL,

		// for database loading
		DATABASE_CORRUPTED
	};

	enum _DatabaseSaveStatus
	{
		DATABASE_SAVE_SUCCESS,
		DATABASE_SAVE_TO_FILE_FAIL
	};

	class OACORE_API Database
	{
	private:
		DatabaseNode* m_root;

	public:
		std::string             _GetValue(const std::string& name, int order = 0);
		void                    _SetValue(const std::string& name, const std::string& value, int order = -1);

	public:
		Database();
		~Database();

		DatabaseNode*           GetRoot();

		_DatabaseLoadStatus     LoadFile(const std::string& path);
		_DatabaseSaveStatus     SaveFile(const std::string& path);

		template <typename T>
		bool                    GetValue(const std::string& name, T& value, int order = 0);
		template <typename T>
		bool                    SetValue(const std::string& name, const T& value, int order = -1);
		void                    Clear();
	};
}
