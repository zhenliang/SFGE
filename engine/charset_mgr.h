#pragma once

#include <map>

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API CharsetManager : public util::IGetInstance<CharsetManager>
{
public:
	CharsetManager() {}
	virtual ~CharsetManager() {}

	bool AddCharset(const std::string& key, const std::string& charset);
	bool LoadCharset(const std::string& key, const std::string& file);
	const Unicode::Text& GetCharset(std::string key);

private:
	typedef std::map<std::string, Unicode::Text> Charsets;
	Charsets charsets_;
};