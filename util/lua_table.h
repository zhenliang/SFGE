#pragma once

#include <string>

#include "util.h"

struct lua_State;

namespace util
{
	UTIL_API int PrintTable(lua_State* L);

	UTIL_API bool HasField(lua_State* L, int key);
	UTIL_API bool HasField(lua_State* L, int index, int key);
	UTIL_API bool HasField(lua_State* L, const std::string& key);
	UTIL_API bool HasField(lua_State* L, int index, const std::string& key);

    // TODO: GetField 系列功能增强，添加设置默认返回值的参数

    UTIL_API bool GetField_Boolean(lua_State* L, int key);
    UTIL_API bool GetField_Boolean(lua_State* L, int index, int key);
	UTIL_API bool GetField_Boolean(lua_State* L, const std::string& key);
	UTIL_API bool GetField_Boolean(lua_State* L, int index, const std::string& key);
    UTIL_API bool SafeGetField_Boolean(lua_State* L, const std::string& key);
    UTIL_API bool SafeGetField_Boolean(lua_State* L, int index, const std::string& key);

	UTIL_API int GetField_Integer(lua_State* L, int key);
	UTIL_API int GetField_Integer(lua_State* L, int index, int key);
	UTIL_API int GetField_Integer(lua_State* L, const std::string& key);
	UTIL_API int GetField_Integer(lua_State* L, int index, const std::string& key);

	UTIL_API double GetField_Number(lua_State* L, int key);
	UTIL_API double GetField_Number(lua_State* L, int index, int key);
	UTIL_API double GetField_Number(lua_State* L, const std::string& key);
	UTIL_API double GetField_Number(lua_State* L, int index, const std::string& key);
    UTIL_API double SafeGetField_Number(lua_State* L, int key);
    UTIL_API double SafeGetField_Number(lua_State* L, int index, int key); 
    UTIL_API double SafeGetField_Number(lua_State* L, const std::string& key);
    UTIL_API double SafeGetField_Number(lua_State* L, int index, const std::string& key);

    UTIL_API std::string GetField_String(lua_State* L, int key);
    UTIL_API std::string GetField_String(lua_State* L, int index, int key);
    UTIL_API std::string GetField_String(lua_State* L, const std::string& key);
    UTIL_API std::string GetField_String(lua_State* L, int index, const std::string& key);
    UTIL_API std::string SafeGetField_String(lua_State* L, int key);
    UTIL_API std::string SafeGetField_String(lua_State* L, int index, int key);
    UTIL_API std::string SafeGetField_String(lua_State* L, const std::string& key);
    UTIL_API std::string SafeGetField_String(lua_State* L, int index, const std::string& key);

	// 为什么返回 void* 时导出函数指示器要在 void* 前面才能编译通过？

	UTIL_API void* GetField_LightUserdata(lua_State* L, const std::string& key); 
	UTIL_API void* GetField_LightUserdata(lua_State* L, int index, const std::string& key); 

	UTIL_API void* GetField_Userdata(lua_State* L, const std::string& key);
	UTIL_API void* GetField_Userdata(lua_State* L, int index, const std::string& key);
}