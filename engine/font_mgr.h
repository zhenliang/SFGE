#pragma once

#include <string>

#include <util\i_get_instance.h>

#include "engine.h"

extern ENGINE_API Uint32 ourDefaultCharset[];

class ENGINE_API FontManager : public util::IGetInstance<FontManager>
{
public:
	FontManager() {}
	virtual ~FontManager() {}

	bool LoadFont(const std::string& file, const std::string& key, unsigned int charSize = 30, 
		const Unicode::Text& charset = ourDefaultCharset);
	Font& GetFont(const std::string& key);

private:
	typedef std::map<const std::string, Font> Fonts;
	Fonts fonts_;
};