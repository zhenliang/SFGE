#pragma once

#include "ui_widget.h"

// 对于 UILine ，SetTopLeft 和 SetWidthHeight 分别为设置起点和终点

class ENGINE_API UILine : public UIWidget
{
public:
  UILine();
  virtual ~UILine() {}

  virtual void Update(float delta);
  virtual void Render(RenderTarget& target) const;

  virtual void PostSetTopLeft();
  virtual void PostSetWidthHeight();

  virtual void SetAlpha(float val);

  void SetThickness(float thickness);
  void SetColor(Color color);

private:
  void RebuildLineShape();

private:
  Shape lineShape_;
  float thickness_;
  Color color_;
};