#pragma once

#include <string>

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API ImageManager : public util::IGetInstance<ImageManager>
{
public:
  ImageManager() {}
  virtual ~ImageManager() {}

  bool LoadImage(const std::string& path, const std::string& key);
  Image& GetImage(const std::string& key);

private:
  typedef std::map<std::string, Image> Images;
  Images images_;
};
