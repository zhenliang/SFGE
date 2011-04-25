#include "image_mgr.h"

#include <util\container.h>

bool ImageManager::LoadImage(const std::string path, const std::string& key)
{
  Image image;
  if (!image.LoadFromFile(path))
    assert(false);
  return util::Insert(images_, std::make_pair(key, image));
}

Image& ImageManager::GetImage(const std::string& key)
{
  if (util::Contain(images_, key))
    return images_[key];

  assert(false);
  static Image nullImage;
  return nullImage;
}