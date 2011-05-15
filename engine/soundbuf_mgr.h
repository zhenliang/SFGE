#pragma once

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API SoundbufManager : public util::IGetInstance<SoundbufManager>
{
public:
  SoundbufManager() {}
  virtual ~SoundbufManager() {}

  bool LoadSoundbuf(const std::string& path, const std::string& key);
  SoundBuffer& GetSoundbuf(const std::string& key);

private:
  typedef std::map<std::string, SoundBuffer> Soundbufs;
  Soundbufs soundbufs_;
};