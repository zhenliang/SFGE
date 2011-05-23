#include <numeric>
#include <vector>

#include <util/container.h>

#define TEST_SUITE UtilContainer

TEST(Foreach)
{
  // 测试 UTIL_FOREACH 是否能够遍历一个容器

  std::vector<int> vec;
  vec.resize(99, 1); // 99 个值为 1 的元素

  // 统计执行的次数并累加各个元素值

  int cnt = 0;
  int sum = 0;
  UTIL_FOREACH(i, vec, std::vector<int>)
  {
    sum += *i;
    ++cnt;
  }

  CHECK(cnt == vec.size());
  CHECK(sum == std::accumulate(vec.begin(), vec.end(), 0));
}

TEST(ConstForeach)
{
  // 测试 UTIL_CONST_FOREACH 是否能够遍历一个容器

  std::vector<int> vec;
  vec.resize(99, 1); // 99 个值为 1 的元素

  // 统计执行的次数并累加各个元素值

  int cnt = 0;
  int sum = 0;
  UTIL_CONST_FOREACH(i, vec, std::vector<int>)
  {
    sum += *i;
    ++cnt;
  }

  CHECK(cnt == vec.size());
  CHECK(sum == std::accumulate(vec.begin(), vec.end(), 0));
}