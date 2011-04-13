#pragma once

struct luaL_Reg;
struct lua_State;

extern luaL_Reg kStringMgrLib[];

int AddString(lua_State* L);
int GetString(lua_State* L);



