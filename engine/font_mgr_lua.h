#pragma once

struct luaL_Reg;
struct lua_State;

extern luaL_Reg kFontMgrLib[];

int LoadFont(lua_State* L);
int GetFont(lua_State* L);
