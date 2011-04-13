#pragma once

struct luaL_Reg;
struct lua_State;

extern luaL_Reg kImgMgrLib[];

int LoadImage(lua_State* L);
int GetImage(lua_State* L);

