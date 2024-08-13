#include "Config.h"

tinyxml2::XMLElement* FindElement(tinyxml2::XMLElement* node, const std::string& name)
{
	tinyxml2::XMLElement* cur = node->FirstChildElement();
	while (cur)
	{
		if (name == cur->Name())
			return cur;
		cur = cur->NextSiblingElement();
	}
	return nullptr;
}

bool ResolveNodes(std::unordered_map<std::string, std::string>& db, const std::string path, tinyxml2::XMLElement* node)
{
	for (tinyxml2::XMLElement* cur = node; cur; cur = cur->NextSiblingElement())
	{
		if (cur->GetText())
		{
			if (db.count(path + cur->Name()) != 0) // repetition is not allowed to appear
				return false;
			else
				db[path + cur->Name()] = cur->GetText();
		}
		else
		{
			// resolve child
			bool result = ResolveNodes(db, path + cur->Name() + ".", cur->FirstChildElement());
			if (!result)
				return false;
		}
	}
	return true;
}

void SplitPath(const std::string& path, std::list<std::string>& result)
{
	std::string::size_type position;
	position = path.find('.');

	if (position == std::string::npos)
	{
		result.push_back(path);
	}
	else
	{
		result.push_back(path.substr(0, position));
		SplitPath(path.substr(position + 1), result);
	}
}

void SaveNode(tinyxml2::XMLElement* parent, std::list<std::string>& path, const std::string& val)
{
	std::string cur_path = path.front();

	tinyxml2::XMLElement* ele = FindElement(parent, cur_path);

	// val element
	if (path.size() == 1)
	{

		if (!ele)
			ele = parent->InsertNewChildElement(cur_path.c_str());
		ele->SetText(val.c_str());
		return;
	}

	// pop current path
	path.pop_front();

	// if existed step in
	if (ele)
		SaveNode(ele, path, val);
	else
		SaveNode(parent->InsertNewChildElement(cur_path.c_str()), path, val);
}

//void SaveNode()


namespace oaui
{


	Config::Config(const std::string& rootName)
	{
		m_root = rootName;
	}

	_ConfigResolveStatus Config::LoadFile(const std::string& path)
	{
		Clear();
		m_path = path;

		using namespace tinyxml2;
		tinyxml2::XMLDocument doc{};

		if (_access(path.c_str(), 0) == -1)
			return CONFIG_FILE_DOESNT_EXIST;

		if (doc.LoadFile(path.c_str()) != XML_SUCCESS)
			return CONFIG_RESOLVE_FAIL;

		// resolve config...
		XMLElement* root = doc.RootElement();

		if (root == nullptr)
			return CONFIG_RESOLVE_FAIL;

		if (std::string(root->Name()) != m_root)
			return CONFIG_RESOLVE_FAIL;

		if (!ResolveNodes(m_db, "", root->FirstChildElement()))
		{
			Clear();
			return CONFIG_RESOLVE_FAIL;
		}
		

		return CONFIG_RESOLVE_SUCCESS;
	}

	bool Config::Save(const std::string& path, bool compact)
	{
		// remove old config
		remove(m_path.c_str());

		using namespace tinyxml2;

		// build config file
		tinyxml2::XMLDocument doc{};

		XMLDeclaration* declaration = doc.NewDeclaration();

		// root element
		XMLElement* root = doc.NewElement(m_root.c_str());
		doc.InsertFirstChild(root);

		
		std::list<std::string> splited_path{};

		// for each flat db
		for (auto& i : m_db)
		{
			splited_path.clear();
			SplitPath(i.first, splited_path);
			SaveNode(root, splited_path, i.second);
		}
	
		// save file
		if (path.empty())
		{
			if (doc.SaveFile(m_path.c_str(), compact) != XML_SUCCESS)
				return false;
			return true;
		}

		if (doc.SaveFile(path.c_str(), compact) != XML_SUCCESS)
			return false;

		return true;
	}

	ConfigFlatDatabase& oaui::Config::GetFlatDatabase()
	{
		return m_db;
	}

	void Config::Clear()
	{
		m_db.clear();
	}
}

