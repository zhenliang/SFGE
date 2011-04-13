#pragma once

struct luaL_Reg;
struct lua_State;

extern luaL_Reg kSoundMgrLib[];

int ReigsterSound(lua_State* L);

