#pragma once

#include "util.h"

namespace util
{
  struct UTIL_API DeleteVisitor
  {
    template <class T>
    void operator()(T* e) const
    {
      delete e; // 注意 DLL 内存空间问题
    }
  };

  struct UTIL_API DeleteVisitor_Second
  {
    template <class T>
    void operator()(T& e) const
    {
      delete e.second;
    }
  };

  struct UTIL_API UpdateVisitor 
  {
    explicit UpdateVisitor(float delta) 
      : delta_(delta) 
    {

    }

    template <class T>
    void operator()(T* e) const
    {
      e->Update(delta_);
    }

    template <class T>
    void operator()(T& e) const 
    {
      e.Update(delta_);
    }

    float delta_;
  };

  struct UTIL_API UpdateVisitor_Second
  {
    explicit UpdateVisitor_Second(float& delta)
      : delta_(delta)
    {

    }

    template <class T>
    void Update(T& e) const
    {
      e.Update(delta_);
    }

    template <class T>
    void Update(T* e) const
    {
      e->Update(delta_);
    }

    template <class T>
    void operator()(T& e) const
    {
      Update(e.second);
    }

    float delta_;
  };
}