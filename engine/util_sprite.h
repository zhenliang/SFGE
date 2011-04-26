#pragma once

#include "engine.h"

ENGINE_API void SetCenter(Sprite& sprite, float factorX = 0.5f, float factorY = 0.5f);
ENGINE_API void SetImage(Sprite& sprite, Image& img, const IntRect& subRect = IntRect(0, 0, 0, 0));
