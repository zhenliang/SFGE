#pragma once

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API StringManager : public util::IGetInstance<StringManager>
{
public:
	StringManager() {}
	virtual ~StringManager() {}

	bool AddString(std::string key, std::wstring value, 
		const Font& font = Font::GetDefaultFont(), float size = 30.0f);
	bool AddString(std::string key, String value);
	bool AddStrings(std::string file);
	String& GetString(std::string key);

private:
	typedef std::map<std::string, String> Strings;
	Strings strings_;
};