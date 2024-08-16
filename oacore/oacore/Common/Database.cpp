#include "Database.h"
#include "oacore/Utils/Utils.h"

#include "tinyxml2.h"

namespace oacore
{
	DatabaseNode* _FindNodeByKey(DatabaseNode* node, const std::string& name, int order = 0, bool autoCreate = false)
	{
		std::string::size_type split = name.find('.');

		if (split == std::string::npos)
		{
			DatabaseNode* result = node->FindNodeInChild(name, order);

			if (result == nullptr)
			{
				if (autoCreate)
				{
					DatabaseNode* newNode = new DatabaseNode{ name };
					node->InsertChildNode(newNode);
					return newNode;
				}
			}
			return result;
		}

		std::string curNode = name.substr(0, split);
		std::string nextNode = name.substr(split + 1, name.size() - split - 1);

		DatabaseNode* result = node->FindNodeInChild(curNode);

		if (result == nullptr)
		{
			if (autoCreate)
			{
				DatabaseNode* newNode = new DatabaseNode{ curNode };
				node->InsertChildNode(newNode);
				result = _FindNodeByKey(newNode, nextNode, order, autoCreate);
			}
		}
		else
		{
			result = _FindNodeByKey(result, nextNode, order, autoCreate);
		}
		return result;
	}

	void _LoadXMLIntoDatabase(oacore::DatabaseNode* node, tinyxml2::XMLElement* element)
	{
		using namespace tinyxml2;

		if (element == nullptr)
			return;

		for (XMLElement* curElement = element; curElement; curElement = curElement->NextSiblingElement())
		{
			oacore::DatabaseNode* newNode = new oacore::DatabaseNode{ curElement->Name()};


			if (curElement->GetText())
				newNode->SetText(curElement->GetText());

			node->InsertChildNode(newNode);

			_LoadXMLIntoDatabase(newNode, curElement->FirstChildElement());
		}
	}

	void _BuildXMLTree(tinyxml2::XMLElement* element, DatabaseNode* node)
	{
		using namespace tinyxml2;

		if (element == nullptr)
			return;

		oacore::DatabaseNode* curNode = node;
		while(curNode)
		{
			XMLElement* newElement = element->InsertNewChildElement(curNode->Name().c_str());

			if (!curNode->Text().empty())
				newElement->SetText(curNode->Text().c_str());

			_BuildXMLTree(newElement, curNode->ChildNode());
			curNode = curNode->NextSiblingNode();
		}
	}

	Database::Database()
	{
		m_root = new DatabaseNode("DatabaseRoot");
	}

	Database::~Database()
	{
		delete m_root;
	}

	std::string Database::_GetValue(const std::string& name, int order)
	{
		DatabaseNode* node = _FindNodeByKey(m_root, name, order, false);
		if (node == nullptr)
			return OACORE_DATABASE_ERROR_STRING;
		return node->Text();
	}

	void Database::_SetValue(const std::string& name, const std::string& value, int order)
	{
		DatabaseNode* node = _FindNodeByKey(m_root, name, order, true);
		node->SetText(value);
	}

	DatabaseNode* Database::GetRoot()
	{
		return m_root;
	}

	_DatabaseLoadStatus Database::LoadFile(const std::string& path)
	{
		_DatabaseLoadStatus status = DATABASE_LOAD_SUCCESS;
		Clear();

		using namespace tinyxml2;

		tinyxml2::XMLDocument doc{};

		XMLError error = doc.LoadFile(path.c_str());

		if (error == XML_ERROR_FILE_COULD_NOT_BE_OPENED || error == XML_ERROR_FILE_NOT_FOUND)
			return DATABASE_FILE_OPEN_FAIL;

		if (error != XML_SUCCESS)
			return DATABASE_XML_PARSE_FAIL;

		_LoadXMLIntoDatabase(m_root, doc.RootElement());

		return status;
	}

	_DatabaseSaveStatus Database::SaveFile(const std::string& path)
	{
		using namespace tinyxml2;

		tinyxml2::XMLDocument doc{};

		XMLDeclaration* declaration = doc.NewDeclaration();
		XMLComment* comment = doc.NewComment(" Obfuscation Analyzer Professional Database File ");
		XMLText* newLineText = doc.NewText("\n");
		doc.InsertEndChild(declaration);
		doc.InsertEndChild(comment);
		doc.InsertEndChild(newLineText);

		oacore::DatabaseNode* curNode = m_root->ChildNode();
		while(curNode)
		{
			XMLElement* newElement = doc.NewElement(curNode->Name().c_str());
			if (!curNode->Text().empty())
				newElement->SetText(curNode->Text().c_str());

			_BuildXMLTree(newElement, curNode->ChildNode());
			doc.InsertEndChild(newElement);
			curNode = curNode->NextSiblingNode();
		}

		if (doc.SaveFile(path.c_str()) != XML_SUCCESS)
			return DATABASE_SAVE_TO_FILE_FAIL;
		return DATABASE_SAVE_SUCCESS;
	}

	void Database::Clear()
	{
		m_root->DeleteChildNodes();
	}

	typedef const char* CStringType;

	template bool OACORE_API Database::GetValue<int>(const std::string& name, int& value, int order);
	template bool OACORE_API Database::GetValue<unsigned int>(const std::string& name, unsigned int& value, int order);
	template bool OACORE_API Database::GetValue<float>(const std::string& name, float& value, int order);
	template bool OACORE_API Database::GetValue<double>(const std::string& name, double& value, int order);
	template bool OACORE_API Database::GetValue<bool>(const std::string& name, bool& value, int order);
	template bool OACORE_API Database::GetValue<std::string>(const std::string& name, std::string& value, int order);
	template bool OACORE_API Database::GetValue<BinaryData>(const std::string& name, BinaryData& value, int order);

	template <typename T>
	bool Database::GetValue(const std::string& name, T& value, int order)
	{
		std::string result = _GetValue(name, order);

		if constexpr (std::is_same<T, int>::value)
		{
			return Utils::String2Int(result, value);
		}
		if constexpr (std::is_same<T, unsigned int>::value)
		{
			return Utils::String2UInt(result, value);
		}
		if constexpr (std::is_same<T, float>::value)
		{
			return Utils::String2Float(result, value);
		}
		if constexpr (std::is_same<T, double>::value)
		{
			return Utils::String2Double(result, value);
		}
		if constexpr (std::is_same<T, bool>::value)
		{
			return Utils::String2Bool(result, value);
		}
		if constexpr (std::is_same<T, std::string>::value)
		{
			if (result == OACORE_DATABASE_ERROR_STRING)
				return false;
			value = result;
			return true;
		}
		if constexpr (std::is_same<T, BinaryData>::value)
		{
			std::string base64DecodedData = Utils::Base64Decode(result);
			value.Size = base64DecodedData.size();

			if (value.Data == NULL)
			{
				value.Data = malloc(value.Size);
				value.ShouldFree = true;
			}
			if(value.Data != nullptr)
				memcpy(value.Data, base64DecodedData.data(), value.Size);
		}

		return true;
	}

	template bool OACORE_API Database::SetValue<int>(const std::string& name, const int& value, int order);
	template bool OACORE_API Database::SetValue<unsigned int>(const std::string& name, const unsigned int& value, int order);
	template bool OACORE_API Database::SetValue<float>(const std::string& name, const float& value, int order);
	template bool OACORE_API Database::SetValue<double>(const std::string& name, const double& value, int order);
	template bool OACORE_API Database::SetValue<bool>(const std::string& name, const bool& value, int order);
	template bool OACORE_API Database::SetValue<CStringType>(const std::string& name, const CStringType& value, int order);
	template bool OACORE_API Database::SetValue<std::string>(const std::string& name, const std::string& value, int order);
	template bool OACORE_API Database::SetValue<BinaryData>(const std::string& name, const BinaryData& value, int order);

	template<typename T>
	bool Database::SetValue(const std::string& name, const T& value, int order)
	{
		std::string result{};
		std::stringstream stream{};

		if constexpr (std::is_same<T, int>::value
			|| std::is_same<T, float>::value
			|| std::is_same<T, double>::value
			)
		{
			stream << value;
			stream >> result;
		}
		if constexpr (std::is_same<T, unsigned int>::value)
		{
			stream << std::hex << std::uppercase << value;
			stream >> result;
			result = "0x" + result;
		}
		if constexpr (std::is_same<T, bool>::value)
		{
			result = Utils::Bool2String(value);
		}
		if constexpr (std::is_same<T, std::string>::value || std::is_same<T, CStringType>::value)
		{
			result = value;
		}
		if constexpr (std::is_same<T, BinaryData>::value)
		{
			if (value.Data == NULL || value.Size == 0)
				return false;

			result = Utils::Base64Encode((BYTE*)value.Data, value.Size);
		}

		_SetValue(name, result, order);

		return true;
	}

}