#include "sound_mgr_lua.h"

#include <lua/lua.hpp>

#include "sound_mgr.h"

luaL_Reg kSoundMgrLib[] = 
{
    {"RegisterSound", ReigsterSound},
    {NULL, NULL}
};

int ReigsterSound(lua_State* L)
{
    std::string sndKey = lua_tostring(L, 1);
    std::string bufKey = lua_tostring(L, 2);
    bool result = SoundManager::GetInstance().RegisterSound(sndKey, bufKey);
    lua_pushboolean(L, result);
    return 1;
}
