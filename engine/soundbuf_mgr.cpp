#include "soundbuf_mgr.h"

#include <util\container.h>

bool SoundbufManager::LoadSoundbuf(std::string path, std::string key)
{
  SoundBuffer buf;
  if (!buf.LoadFromFile(path))
    assert(false);
  return util::Insert(soundbufs_, std::make_pair(key, buf));
}

SoundBuffer& SoundbufManager::GetSoundbuf( std::string key )
{
  if (util::Contain(soundbufs_, key))
    return soundbufs_[key];

  assert(false);
  static SoundBuffer nullbuf;
  return nullbuf;
}