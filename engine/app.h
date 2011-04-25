#pragma once

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API App : public RenderWindow, public util::IGetInstance<App>
{
public:
  App() {}
  virtual ~App() {}
};