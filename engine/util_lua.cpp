#pragma once

#include "util_lua.h"

#include <lua/lua.hpp>
#include <util/lua_table.h>

void SetColor(lua_State* L, Color& color)
{
  assert(lua_istable(L, -1));

  if (util::HasField(L, 1))
    color.r = util::GetField_Integer(L, 1);
  if (util::HasField(L, 2))
    color.g = util::GetField_Integer(L, 2);
  if (util::HasField(L, 3))
    color.b = util::GetField_Integer(L, 3);
  if (util::HasField(L, 4))
    color.a = util::GetField_Integer(L, 4);

  if (util::HasField(L, "r"))
    color.r = util::GetField_Integer(L, "r");
  if (util::HasField(L, "g"))
    color.g = util::GetField_Integer(L, "g");
  if (util::HasField(L, "b"))
    color.b = util::GetField_Integer(L, "b");
  if (util::HasField(L, "a"))
    color.a = util::GetField_Integer(L, "a");
}

void SetVector2f(lua_State* L, Vector2f& vector2f)
{
  assert(lua_istable(L, -1));

  if (util::HasField(L, 1))
    vector2f.x = util::GetField_Number(L, 1);

  if (util::HasField(L, 2))
    vector2f.y = util::GetField_Number(L, 2);
}