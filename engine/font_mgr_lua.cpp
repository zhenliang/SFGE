#include "font_mgr_lua.h"

#include <lua\lua.hpp>

#include "charset_mgr.h"
#include "font_mgr.h"

luaL_Reg kFontMgrLib[] = 
{
	{"LoadFont", LoadFont},
	{"GetFont", GetFont},
	{NULL, NULL}
};

int LoadFont( lua_State* L )
{
	bool result = false;

	int paraNum = lua_gettop(L);
	assert(paraNum >= 2 && paraNum <= 4 );

	std::string file = lua_tostring(L, 1);
	std::string key = lua_tostring(L, 2);
	if (paraNum == 2)
	{
		result = FontManager::GetInstance().LoadFont(file, key);
	}
	else if (paraNum == 3)
	{
		int charSize = lua_tointeger(L, 3);
		result = FontManager::GetInstance().LoadFont(file, key, charSize);
	}
	else if (paraNum == 4)
	{
		int charSize = lua_tointeger(L, 3);
		std::string charsetKey = lua_tostring(L, 4);
		const Unicode::Text& charset = CharsetManager::GetInstance().GetCharset(charsetKey);
		result = FontManager::GetInstance().LoadFont(file, key, charSize, charset);
	}
	
	lua_pushboolean(L, result);

	return 1;
}

int GetFont( lua_State* L )
{
	std::string key = lua_tostring(L, 1);
	Font& font = FontManager::GetInstance().GetFont(key);
	lua_pushlightuserdata(L, &font);
	return 1;
}