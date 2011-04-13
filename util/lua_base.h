#pragma once

#include <lua/lua.hpp>

namespace util
{
	inline int ToPositiveIndex(lua_State* L, int index);

	#include "lua_base.inl"
}