#include "image_mgr_lua.h"

#include <lua\lua.hpp>

#include "image_mgr.h"

luaL_Reg kImgMgrLib[] =
{
	{"LoadImage", LoadImage},
	{"GetImage", GetImage},
	{NULL, NULL}
};

int LoadImage( lua_State* L )
{
	std::string file = lua_tostring(L, 1);
	std::string key = lua_tostring(L, 2);
	bool result = ImageManager::GetInstance().LoadImage(file, key);
	lua_pushboolean(L, result);
	return 1;
}

int GetImage( lua_State* L )
{
	std::string key = lua_tostring(L, 1);
	Image& img = ImageManager::GetInstance().GetImage(key);
	lua_pushlightuserdata(L, &img);
	return 1;
}
