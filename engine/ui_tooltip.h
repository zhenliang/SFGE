#pragma once

#include "engine.h"

namespace UITooltip
{

void ENGINE_API Set(const String& tip, float left = 0.0f, float top = 0.0f);
void ENGINE_API Draw(RenderTarget& target);
void ENGINE_API Reset();

}