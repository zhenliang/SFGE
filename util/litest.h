#pragma once

#include <iostream>
#include <string>

// 用法
//
// ﻿#include "litest.h" 
// 
// // 定义测试套件名称，可选，默认为 DefaultSuite
// // 凡在该定义之后的 Test 都属于该套件
// 
// #define TEST_SUITE DemoSuite
// 
// // 测试样例
// 
// TEST(SimpleDemo)
// {
//   // 输出错误信息
// 
//   FAIL("a fail msg"); 
// 
//   // 判断
// 
//   CHECK(1 > 2); 
// }
// 
// int main()
// {
//   std::cin.ignore();
//   return 0;
//

typedef void (*TestFunc)(const std::string& suite, const std::string& name);
inline bool RunTestFunc(TestFunc func, const std::string& suite, const std::string& name) {
  func(suite, name); return true; 
}

#define TEST_SUITE DefaultSuite
#define TEST(name) TEST_UNIT(TEST_SUITE, name)
#define TEST_UNIT(suite, name) TEST_UNIT_IMPL(suite, name)
#define TEST_UNIT_IMPL(suite, name) \
  void TestFunc_##suite##_##name(const std::string&, const std::string&); \
  bool kTestDirver_##suite##_##name = RunTestFunc(TestFunc_##suite##_##name, #suite, #name); \
  void TestFunc_##suite##_##name(const std::string& suite_, const std::string& name_) 

#define CHECK(condition) if (!(condition)) Fail(suite_, name_, __FILE__, __LINE__, #condition);
#define FAIL(msg) Fail(suite_, name_, __FILE__, __LINE__, #msg);

inline void Fail(const std::string& suite, const std::string& test, const std::string& file, 
                 long line, const std::string& msg)
{
  std::cout << "Suite: " << suite <<std::endl;
  std::cout << "Test : " << test  <<std::endl;
  std::cout << "Fail : " << msg   <<std::endl;
  std::cout << "File : " << file  <<std::endl;
  std::cout << "Line : " << line  <<std::endl;
  std::cout << std::endl;
}