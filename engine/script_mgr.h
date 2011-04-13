#pragma once

#include <lua\lua.hpp>

#include <util\i_get_instance.h>

#include "engine.h"

class ENGINE_API ScriptManager : public util::IGetInstance<ScriptManager> 
{
public:
	ScriptManager();
	~ScriptManager();

	inline void DoString(const std::string& str);
	inline void DoFile(const std::string& file);

	inline void RegisterFunc(const std::string& name, lua_CFunction func);
	inline void RegisterVar(const std::string& name, void* var);

	inline lua_State* GetLuaState();

	inline int GetInt(const std::string& name);
	inline float GetFloat(const std::string& name);
	inline double GetDouble(const std::string& name);
	inline std::string GetString(const std::string& name);
	template <class T>
	inline T* GetUserdata(const std::string& name);

private:
	lua_State* luaState_;
};

#include "script_mgr.inl"
