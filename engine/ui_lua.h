#pragma once

struct lua_State;

void RegisterUICreators();

int Button(lua_State* L);
int Label(lua_State* L);
int Line(lua_State* L);
int Panel(lua_State* L);
int Progressbar(lua_State* L);
int Window_(lua_State* L);
int Widget(lua_State* L);