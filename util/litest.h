#pragma once

// home.zhenliang@gmail.com 

// 实现原理
//
// TestUnit 为每个测试单元的基类
// 而宏 TEST 根据传入的名称生成对应的子类（TestUnit_SuiteName_TestName）和其 Run 方法
// TEST 定义子类之后声明一个全局变量（kTestUnit_SuiteName_TestName）
// 而因为每个 TestUnit 在创建的时候自动调用 Run 方法
// 故每个 TestUnit 都在自己被创建过程中自动进行测试，达到自动测试的目的

#include <sstream>
#include <iostream>

namespace util
{
  class TestUnit
  {
  public:
    TestUnit(const std::string& suite, const std::string& name);
    virtual void Run() = 0;

  protected:
    std::string suite_;
    std::string name_;
  };

  template <class T1, class T2>
  void Fail(const std::string& suite, const std::string& test, const std::string& file, long line,
    const T1& expected, const T2& actual);
  void Fail(const std::string& suite, const std::string& test, const std::string& file, long line,
    const std::string& msg);

  #include "litest.inl"
}
