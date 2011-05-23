#include "script_mgr.h"

#include "charset_mgr_lua.h"
#include "font_mgr_lua.h"
#include "image_mgr.h"
#include "image_mgr_lua.h"
#include "sound_mgr_lua.h"
#include "soundbuf_mgr_lua.h"
#include "string_mgr_lua.h"
#include "ui_lua.h"

namespace native_type_setters
{
  // 注意，所有 setter 都未处理有没有符号

  int SetBool(lua_State* L)
  {
    void* adr = lua_touserdata(L, 1);
    bool val = lua_toboolean(L, 2);
    *static_cast<bool*>(adr) = val; // 必须是对应指针，否则赋值不正确，下同
    return 0;
  }

  // 注意此函数在 lua 内必须以整数值来赋值，用字符 'x' 赋值会不正确

  int SetChar(lua_State* L)
  {
    void* adr = lua_touserdata(L, 1);
    int val = lua_tointeger(L, 2);
    *static_cast<char*>(adr) = val;
    return 0;
  }

  int SetInt(lua_State* L)
  {
    void* adr = lua_touserdata(L, 1);
    int val = lua_tointeger(L, 2);
    *static_cast<int*>(adr) = val;
    return 0;
  }

  int SetFloat(lua_State* L)
  {
    void* adr = lua_touserdata(L, 1);
    float val = lua_tonumber(L, 2);
    *static_cast<float*>(adr) = val;
    return 0;
  }

  int SetDouble(lua_State* L)
  {
    void* adr = lua_touserdata(L, 1);
    double val = lua_tonumber(L, 2);
    *static_cast<double*>(adr) = val;
    return 0;
  }

  int SetChars(lua_State* L)
  {
    void* adr = lua_touserdata(L, 1);
    const char* val = lua_tostring(L, 2);
    strcpy(static_cast<char*>(adr), val);
    return 0;
  }

  int SetString(lua_State* L)
  {
    void* adr = lua_touserdata(L, 1);
    const char* val = lua_tostring(L, 2);
    *static_cast<std::string*>(adr) = val;
    return 0;
  }
}

namespace 
{
  void RegisterNativeTypeSetters()
  {
    using namespace native_type_setters;

    ScriptManager& scriptMgr = ScriptManager::GetInstance();

    scriptMgr.RegisterFunc("SetBool", SetBool);
    scriptMgr.RegisterFunc("SetChar", SetChar);
    scriptMgr.RegisterFunc("SetInt", SetInt);
    scriptMgr.RegisterFunc("SetFloat", SetFloat);
    scriptMgr.RegisterFunc("SetDouble", SetDouble);
    scriptMgr.RegisterFunc("SetChars", SetChars);
    scriptMgr.RegisterFunc("SetString", SetString);
  }

  void OpenEngineLibs(lua_State* L)
  {
    luaL_openlib(L, "CharsetManager", kCharsetMgrLib, 0);
    luaL_openlib(L, "FontManager", kFontMgrLib, 0);
    luaL_openlib(L, "ImageManager", kImgMgrLib, 0);
    luaL_openlib(L, "SoundManager", kSoundMgrLib, 0);
    luaL_openlib(L, "SoundbufManager", kSoundbufMgrLib, 0);
    luaL_openlib(L, "StringManager", kStringMgrLib, 0);

    LuaImage::Register(L);
  }
}

ScriptManager::ScriptManager() :
luaState_()
{
  luaState_ = lua_open(); 
  luaL_openlibs(luaState_);

  OpenEngineLibs(luaState_);
  RegisterNativeTypeSetters();
  RegisterUICreators();
}

ScriptManager::~ScriptManager()
{
  lua_close(luaState_);
}
