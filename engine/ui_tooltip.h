#pragma once

#include "engine.h"

namespace UITooltip
{

  ENGINE_API void Set(const String& tip, float left = 0.0f, float top = 0.0f);
  ENGINE_API void Draw(RenderTarget& target);
  ENGINE_API void Reset();

}