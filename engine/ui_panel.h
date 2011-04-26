#pragma once

#include "ui_widget.h"

class ENGINE_API UIPanel : public UIWidget
{
public:
  UIPanel();
  virtual ~UIPanel() {}

  virtual void Update(float delta);
  virtual void Render(RenderTarget& target) const;

public:
  static const std::string NORMAL_ANIM_;
  static const std::string DISABLED_ANIM_;

protected:
  virtual void PostSetAnim(const std::string name, Animation& anim);

private:
  bool hasNormalAnim_;
  bool hasDisabledAnim_;
};