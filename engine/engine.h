#pragma once

// 使用动态库版本
// engine 模块需定义 ENGINE_DYMAMIC 和 _USRDLL
// 使用 engine 的模块需要定义 ENGINE_DYMAMIC
//
// 使用静态库版本
// engine 模块和使用 engine 的模块都不能定义 ENGINE_DYMAMIC

#ifdef ENGINE_DYMAMIC
  #ifdef _USRDLL
    #define ENGINE_API __declspec(dllexport)
  #else
    #define ENGINE_API __declspec(dllimport)
  #endif
#else
  #define ENGINE_API 
#endif
