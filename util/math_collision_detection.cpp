#include "math_collision_detection.h"

#include "math_base.h"

namespace util
{
  bool CircleTest( float x1, float y1, float r1, float x2, float y2, float r2 )
  {
    float minDistance = UTIL_POW2(r1 + r2);
    float curDistance = UTIL_POW2(x1 - x2) + UTIL_POW2(y1 - y2);
    return curDistance < minDistance;
  }
}
