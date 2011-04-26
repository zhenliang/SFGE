#pragma once

namespace util
{

// 使用动态库版本
// util 模块需定义 UTIL_DYNAMIC 和 _USRDLL
// 使用 util 的模块需要定义 UTIL_DYNAMIC
//
// 使用静态库版本
// util 模块和使用 util 的模块都不能定义 UTIL_DYNAMIC

#ifdef UTIL_DYNAMIC 
  #ifdef _USRDLL
    #define UTIL_API __declspec(dllexport)
  #else
    #define UTIL_API __declspec(dllimport)
  #endif
#else
  #define UTIL_API
#endif

}
