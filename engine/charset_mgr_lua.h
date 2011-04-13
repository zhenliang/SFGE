#pragma once

struct luaL_Reg;
struct lua_State;

extern luaL_Reg kCharsetMgrLib[];

int AddCharset(lua_State* L);

