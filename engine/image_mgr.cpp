#include "image_mgr.h"

#include <util\container.h>

namespace
{
  const Image kProxyImage = Image(10, 10);
}

bool ImageManager::LoadImage(const std::string& path, const std::string& key)
{
  static Image image;

  if (!image.LoadFromFile(path))
  {
    assert(false);
    image = kProxyImage;
  }

  return util::Insert(images_, std::make_pair(key, image));
}

Image& ImageManager::GetImage(const std::string& key)
{
  if (util::Contain(images_, key))
    return images_[key];

  assert(false);
  static Image image = kProxyImage;
  return image;
}