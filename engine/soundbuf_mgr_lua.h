#pragma once

struct luaL_Reg;
struct lua_State;

extern luaL_Reg kSoundbufMgrLib[];

int LoadSoundbuf(lua_State* L);
int GetSoundbuf(lua_State* L);

