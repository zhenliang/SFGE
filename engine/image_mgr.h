#pragma once

#include <string>

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API ImageManager : public util::IGetInstance<ImageManager>
{
public:
	ImageManager() {}
	virtual ~ImageManager() {}

	bool LoadImage(std::string file, std::string key);
	Image& GetImage(std::string key);

private:
	typedef std::map<std::string, Image> Images;
	Images images_;
};
