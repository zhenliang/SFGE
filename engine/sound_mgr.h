#pragma once

#include <list>

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API SoundManager : public util::IGetInstance<SoundManager>
{
public:
  typedef std::map<std::string, std::string> BufMap;
  typedef std::list< std::pair<std::string, Sound> > Sounds;

public:
  SoundManager() {}
  virtual ~SoundManager() {}

  bool RegisterSound(const std::string& soundKey, const std::string& bufKey);
  void PlaySound(const std::string& soundKey, bool loop = false, float pitch = 1.f, 
    float volume = 100.f, const Vector3f& position = Vector3f(0.f, 0.f, 0.f));

  void EraseStoppedSounds();

private:
  BufMap bufMap_;
  Sounds sounds_;
};