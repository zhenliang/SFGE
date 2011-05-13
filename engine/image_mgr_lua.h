#pragma once

#include <lua\lua.hpp>

#include "engine.h"

struct luaL_Reg;
struct lua_State;

extern luaL_Reg kImgMgrLib[];

int LoadImage(lua_State* L);
int GetImage(lua_State* L);

struct LuaImage
{
  static const char* className_;
  static const luaL_reg methods_[];

  static void Register(lua_State* L);
  static int GC(lua_State* L);

  static int SetSmooth(lua_State* L);
};

