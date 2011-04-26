#include "util_sprite.h"

void SetCenter(Sprite& sprite, float factorX /*= 0.5f*/, float factorY /*= 0.5f*/)
{
  IntRect rect = sprite.GetSubRect();
  Vector2f center(rect.GetWidth() * factorX, rect.GetHeight() * factorY);
  sprite.SetCenter(center);
}

void SetImage(Sprite& sprite, Image& img, 
                         const IntRect& subRect /*= IntRect(0.0f, 0.0f, 0.0f, 0.0f)*/)
{
  sprite.SetImage(img);

  // 没提供 subRect 则按图片大小来设置 subRect

  if (subRect.GetHeight() == 0)
    sprite.SetSubRect(IntRect(0.0f, 0.0f, img.GetWidth(), img.GetHeight()));
  else 
    sprite.SetSubRect(subRect);
}