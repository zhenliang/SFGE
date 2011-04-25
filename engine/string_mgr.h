#pragma once

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API StringManager : public util::IGetInstance<StringManager>
{
public:
  StringManager() {}
  virtual ~StringManager() {}

  bool AddString(const std::string& key, const std::wstring& value, 
    const Font& font = Font::GetDefaultFont(), float size = 30.f);
  bool AddString(const std::string& key, const String& value);
  bool AddStrings(const std::string& path);
  String& GetString(const std::string& key);

private:
  typedef std::map<std::string, String> Strings;
  Strings strings_;
};