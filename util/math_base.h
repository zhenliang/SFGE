#pragma once

#include "util.h"
#include <assert.h>

namespace util
{
  #define UTIL_POW2(x) ((x)*(x))

  inline bool IsPowerOfTwo(int n);

  // align ±ØÐëÊÇ 2 µÄÃÝ
  inline unsigned int RoundUp(unsigned int n, unsigned int align);

  template <class T1, class T2, class T3>
  inline T1 Clam(const T1& num, const T2& low, const T3& high);
  template <class T1, class T2>
  inline T1 ClamUp(const T1& num, const T2& low);
  template <class T1, class T2>
  inline T1 ClamDown(const T1& num, const T2& high);

  template <class Num, class Begin, class End>
  inline bool InRange(Num num, Begin begin, End end);
  template <class NumX, class NumY, class Left, class Top, class Right, class Bottom>
  inline bool InRect(NumX x, NumY y, Left left, Top top, Right right, Bottom bottom);

  #include "math_base.inl"
}
