#pragma once

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API SoundbufManager : public util::IGetInstance<SoundbufManager>
{
public:
	SoundbufManager() {}
	virtual ~SoundbufManager() {}

	bool LoadSoundbuf(std::string file, std::string key);
	SoundBuffer& GetSoundbuf(std::string key);

private:
	typedef std::map<std::string, SoundBuffer> Soundbufs;
	Soundbufs soundbufs_;
};