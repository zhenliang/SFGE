#pragma once

// ÞðÆúµÄ´úÂë

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

// usage:
//
// #include "debug_new.h"
//
// int main()
// {
//   int* num = new int;
//   _CrtDumpMemoryLeaks();
// }

// link: http://msdn.microsoft.com/en-us/library/e5ewb1h3(v=VS.80)