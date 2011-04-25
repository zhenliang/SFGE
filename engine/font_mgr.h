#pragma once

#include <string>

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API FontManager : public util::IGetInstance<FontManager>
{
public:
  FontManager() {}
  virtual ~FontManager() {}

  bool LoadFont(const std::string& path, const std::string& key, unsigned int charSize = 30, 
    const Unicode::Text& charset = "");
  Font& GetFont(const std::string& key);

private:
  typedef std::map<std::string, Font> Fonts;
  Fonts fonts_;
};