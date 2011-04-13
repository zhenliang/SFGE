#include "soundbuf_mgr_lua.h"

#include <lua\lua.hpp>

#include "soundbuf_mgr.h"

luaL_Reg kSoundbufMgrLib[] =
{
	{"LoadSoundbuf", LoadSoundbuf},
	{"GetSoundbuf", GetSoundbuf},
	{NULL, NULL}
};

int LoadSoundbuf( lua_State* L )
{
	std::string file = lua_tostring(L, 1);
	std::string key = lua_tostring(L, 2);
	bool result = SoundbufManager::GetInstance().LoadSoundbuf(file, key);
	lua_pushboolean(L, result);
	return 1;
}

int GetSoundbuf( lua_State* L )
{
	std::string key = lua_tostring(L, 1);
	SoundBuffer& buf = SoundbufManager::GetInstance().GetSoundbuf(key);
	lua_pushlightuserdata(L, &buf);
	return 1;
}
