#include "util_sprite.h"

void SetCenter( Sprite& sprite, float factorX /*= 0.5f*/, float factorY /*= 0.5f*/ )
{
	IntRect rect = sprite.GetSubRect();
	Vector2f center(rect.GetWidth() * factorX, rect.GetHeight() * factorY);
	sprite.SetCenter(center);
}

void ENGINE_API SetImage( Sprite& sprite, Image& img, 
						 const IntRect& subRect /*= IntRect(0.0f, 0.0f, 0.0f, 0.0f)*/ )
{
	sprite.SetImage(img);
	if (subRect.GetHeight() == 0)
		sprite.SetSubRect(IntRect(0.0f, 0.0f, img.GetWidth(), img.GetHeight()));
	else 
		sprite.SetSubRect(subRect);
}