#pragma once

#include "engine.h"

void ENGINE_API SetCenter(Sprite& sprite, float factorX = 0.5f, float factorY = 0.5f);
void ENGINE_API SetImage(Sprite& sprite, Image& img, const IntRect& subRect = IntRect(0, 0, 0, 0));
