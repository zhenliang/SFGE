#include "string_mgr_lua.h"

#include <lua\lua.hpp>
#include <util\string.h>

#include "font_mgr.h"
#include "string_mgr.h"

luaL_Reg kStringMgrLib[] = 
{
  {"AddString", AddString},
  {"GetString", GetString},
  {NULL, NULL}
};

int AddString( lua_State* L )
{
  bool result = false;

  int paraNum = lua_gettop(L);
  assert(paraNum >=2 && paraNum <= 4);

  std::string key = lua_tostring(L, 1);
  std::string str = lua_tostring(L, 2);
  std::wstring wstr = util::S2WS(str);

  if (paraNum == 2)
    result = StringManager::GetInstance().AddString(key, wstr);
  else if (paraNum == 3)
  {
    std::string fontKey = lua_tostring(L, 3);
    Font& font = FontManager::GetInstance().GetFont(fontKey);
    result = StringManager::GetInstance().AddString(key, wstr, font);
  }
  else if (paraNum == 4)
  {
    std::string fontKey = lua_tostring(L, 3);
    Font& font = FontManager::GetInstance().GetFont(fontKey);
    int size = lua_tointeger(L, 4);
    result = StringManager::GetInstance().AddString(key, wstr, font, size);
  }

  lua_pushboolean(L, result);

  return 1;
}

int GetString( lua_State* L )
{
  // TODO: 需要的时候实现它
  std::cout<<"StringManager::GetString() is currently not implemented.";
  return 0;
}