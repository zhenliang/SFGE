
void ScriptManager::DoString(const std::string& str)
{
  if (0 != luaL_dostring(luaState_, str.c_str()))
    util::Logger::GetInstance().Log("fail dostring" + str);
}

void ScriptManager::DoFile( const std::string& path )
{
  if (luaL_dofile(luaState_, path.c_str()))
    util::Logger::GetInstance().Log("fail " + path);
  else 
    util::Logger::GetInstance().Log("ok " + path);
}

void ScriptManager::RegisterFunc(const std::string& name, lua_CFunction func)
{
  lua_register(luaState_, name.c_str(), func);
}

void ScriptManager::RegisterVar( const std::string& name, void* var )
{
  lua_pushlightuserdata(luaState_, var);
  lua_setglobal(luaState_, name.c_str());
}

int ScriptManager::GetInt( const std::string& name )
{
  lua_getglobal(luaState_, name.c_str());
  assert(lua_isnumber(luaState_, -1));
  int result = static_cast<int>(lua_tointeger(luaState_, -1)); 
  lua_pop(luaState_, 1);
  return result;
}

float ScriptManager::GetFloat( const std::string& name )
{
  return static_cast<float>(GetDouble(name));
}

double ScriptManager::GetDouble( const std::string& name )
{
  lua_getglobal(luaState_, name.c_str());
  assert(lua_isnumber(luaState_, -1));
  double result = lua_tonumber(luaState_, -1); 
  lua_pop(luaState_, 1);
  return result;
}

std::string ScriptManager::GetString( const std::string& name )
{
  lua_getglobal(luaState_, name.c_str());
  assert(lua_isstring(luaState_, -1));
  std::string result = lua_tostring(luaState_, -1); 
  lua_pop(luaState_, 1);
  return result;
}

template <class T>
T* ScriptManager::GetUserdata( const std::string& name )
{
  lua_getglobal(luaState_, name.c_str());
  assert(lua_islightuserdata(luaState_, -1));
  T* result = static_cast<T*>(lua_touserdata(luaState_, -1));
  lua_pop(luaState_, 1);
  return result;
}

lua_State* ScriptManager::GetLuaState()
{
  return luaState_;
}