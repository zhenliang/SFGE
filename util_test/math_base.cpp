#include <util/math_base.h>
#include <math.h>

#define TEST_SUITE math_base

using namespace util;

TEST(IsPowerOfTwo)
{
  CHECK(!IsPowerOfTwo(-1));
  CHECK(!IsPowerOfTwo(-0));
  CHECK(!IsPowerOfTwo(0));

  CHECK(IsPowerOfTwo(1));
  CHECK(IsPowerOfTwo(2));
  CHECK(!IsPowerOfTwo(3));
  CHECK(IsPowerOfTwo(4));
  CHECK(!IsPowerOfTwo(5));
  CHECK(!IsPowerOfTwo(6));
  CHECK(!IsPowerOfTwo(7));
  CHECK(IsPowerOfTwo(8));
  CHECK(!IsPowerOfTwo(9));
}

TEST(RoundUp)
{
  CHECK(RoundUp(0, 2) == 0);
  CHECK(RoundUp(1, 2) == 2);
  CHECK(RoundUp(3, 2) == 4);
  CHECK(RoundUp(4, 2) == 4);
  CHECK(RoundUp(5, 2) == 6);
  CHECK(RoundUp(6, 2) == 6);
  CHECK(RoundUp(7, 2) == 8);
  CHECK(RoundUp(8, 2) == 8);
  CHECK(RoundUp(9, 2) == 10);
  CHECK(RoundUp(10, 2) == 10);

  CHECK(RoundUp(0, 8) == 0);
  CHECK(RoundUp(1, 8) == 8);
  CHECK(RoundUp(3, 8) == 8);
  CHECK(RoundUp(4, 8) == 8);
  CHECK(RoundUp(5, 8) == 8);
  CHECK(RoundUp(6, 8) == 8);
  CHECK(RoundUp(7, 8) == 8);
  CHECK(RoundUp(8, 8) == 8);
  CHECK(RoundUp(9, 8) == 16);
  CHECK(RoundUp(10, 8) == 16);

  for (unsigned int n = 0; n < 10; ++n)
  {
    for (unsigned int alignOffset = 1; alignOffset < 10; ++alignOffset)
    {
      unsigned int align = 1 << alignOffset;
      int expected = ceil((static_cast<float>(n) / align)) * align;
      CHECK(RoundUp(n, align) == expected);
    }
  }
}