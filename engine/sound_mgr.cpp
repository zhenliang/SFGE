#include "sound_mgr.h"

#include <util\container.h>

#include "soundbuf_mgr.h"

namespace 
{
    bool IsStop(const SoundManager::Sounds::value_type& pair)
    {
        const Sound& sound = pair.second;
        return sound.GetStatus() == Sound::Stopped;
    }
}

bool SoundManager::RegisterSound(const std::string& soundKey, const std::string& soundbufKey)
{
    return util::Insert(bufMap_, std::make_pair(soundKey, soundbufKey));
}

void SoundManager::PlaySound(const std::string& soundKey, bool loop /*= false*/, 
    float pitch /*= 1.f*/, float volume /*= 100.f*/, const Vector3f& position /*= Vector3f(0, 0, 0)*/)
{
    EraseStoppedSounds();
   
    std::string bufKey = util::Get(bufMap_, soundKey);
    SoundBuffer& buf = SoundbufManager::GetInstance().GetSoundbuf(bufKey);
    Sound sound(buf, loop, pitch, volume, position);
    sounds_.push_back(std::make_pair(soundKey, sound));

    sounds_.rbegin()->second.Play();
}

void SoundManager::EraseStoppedSounds()
{
    Sounds::iterator firstToErase = std::remove_if(sounds_.begin(), sounds_.end(), IsStop);
    sounds_.erase(firstToErase, sounds_.end());
}
