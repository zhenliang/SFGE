#pragma once

#include "engine.h"

struct ENGINE_API RenderVisitor
{
  RenderVisitor(RenderTarget& target) 
    : target_(target)
  {

  }

  template <class T>
  void operator()(T* e) const
  {
    e->Render(target_);
  }

  template <class T>
  void operator()(T& e) const 
  {
    e.Render(target_);
  }

  RenderTarget& target_;
};

struct ENGINE_API RenderVisitor_Second
{
  RenderVisitor_Second(RenderTarget& target)
    : target_(target)
  {

  }

  template <class T>
  void Render(T& e) const
  {
    e.Render(target_);
  }

  template <class T>
  void Render(T* e) const
  {
    e->Render(target_);
  }

  template <class T>
  void operator()(T& pair) const
  {
    Render(pair.second);
  }

  RenderTarget& target_;
};

struct ENGINE_API DrawVisitor_Second
{
  DrawVisitor_Second(RenderTarget& target)
    : target_(target)
  {

  }

  template <class T>
  void Draw(T& e) const
  {
    target_.Draw(e);
  }

  template <class T>
  void Draw(T* e) const
  {
    target_.Draw(*e);
  }

  template <class T>
  void operator()(T& pair) const
  {
    Draw(pair.second);
  }

  RenderTarget& target_;
};
