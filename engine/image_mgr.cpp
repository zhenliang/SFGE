#include "image_mgr.h"

#include <util\container.h>

bool ImageManager::LoadImage( std::string file, std::string key )
{
	Image image;
	if (!image.LoadFromFile(file))
		assert(false);
	return util::Insert(images_, std::make_pair(key, image));
}

Image& ImageManager::GetImage( std::string key )
{
	if (util::Contain(images_, key))
		return images_[key];
		
	assert(false);
	static Image nullImage;
	return nullImage;
}