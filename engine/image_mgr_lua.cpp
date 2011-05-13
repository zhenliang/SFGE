#include "image_mgr_lua.h"

#include <lua\lua.hpp>

#include "image_mgr.h"

luaL_Reg kImgMgrLib[] =
{
  {"LoadImage", LoadImage},
  {"GetImage", GetImage},
  {NULL, NULL}
};

int LoadImage(lua_State* L)
{
  std::string path = lua_tostring(L, 1);
  std::string key = lua_tostring(L, 2);
  bool result = ImageManager::GetInstance().LoadImage(path, key);
  lua_pushboolean(L, result);
  return 1;
}

#define METHOD(class, name) { #name, class::name }

const char* LuaImage::className_ = "Image";
const luaL_reg LuaImage::methods_[] = 
{
  METHOD(LuaImage, SetSmooth),
  {0, 0},
};

int LuaImage::SetSmooth(lua_State* L)
{
  assert(lua_gettop(L) == 2);

#if 1
  Image* image = *static_cast<Image**>(luaL_checkudata(L, 1, LuaImage::className_));
#else // lua_unboxpointer
  Image* image = (Image*)(*(void **)(lua_touserdata(L, 1)));
#endif
  
  bool smooth = lua_toboolean(L, 2);
  image->SetSmooth(smooth);

  return 0;
}

void LuaImage::Register(lua_State* L)
{
  lua_newtable(L);
  int methodTable = lua_gettop(L);

  luaL_newmetatable(L, className_);
  int metaTable = lua_gettop(L);

  lua_pushstring(L, "__metatable");
  lua_pushvalue(L, methodTable);
  lua_settable(L, metaTable);

  lua_pushstring(L, "__index");
  lua_pushvalue(L, methodTable);
  lua_settable(L, metaTable);

  lua_pushstring(L, "__gc");
  lua_pushcfunction(L, LuaImage::GC);
  lua_settable(L, metaTable);

  lua_pop(L, 1); // drop metatable
  luaL_register(L, NULL, LuaImage::methods_); // fill methodtable
  lua_pop(L, 1); // drop methodtable
}

int LuaImage::GC(lua_State* L)
{
  return 0;
}

int GetImage(lua_State* L)
{
  std::string key = lua_tostring(L, 1);

#if 1
  Image** boxptr = static_cast<Image**>(lua_newuserdata(L, sizeof(Image*)));
  *boxptr = &ImageManager::GetInstance().GetImage(key);
#else // lua_boxpointer
  Image* image = &ImageManager::GetInstance().GetImage(key);
  *(void**)(lua_newuserdata(L, sizeof(void*))) = image;
#endif
  
  luaL_getmetatable(L, LuaImage::className_);
  lua_setmetatable(L, -2);

  return 1;
}