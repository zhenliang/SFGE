#include "charset_mgr_lua.h"

#include <lua\lua.hpp>

#include "charset_mgr.h"

luaL_Reg kCharsetMgrLib[] = 
{
  {"AddCharset", AddCharset},
  {NULL, NULL}
};

int AddCharset( lua_State* L )
{
  std::string key = lua_tostring(L, 1);
  std::string charset = lua_tostring(L, 2);
  bool result = CharsetManager::GetInstance().AddCharset(key, charset);
  lua_pushboolean(L, result);
  return 1;
}
