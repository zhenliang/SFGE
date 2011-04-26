#pragma once

#include "ui_widget.h"

class ENGINE_API UIButton : public UIWidget
{
public:
  UIButton();
  virtual ~UIButton() {}

  virtual void Update(float delta);
  virtual void Render(RenderTarget& target) const;

  float GetHoveredMaxScale() const { return hoveredMaxScale_; }
  float GetHoveredScaleSpeed() const { return hoveredScaleSpeed_; }

  void SetHoveredMaxScale(float val) { hoveredMaxScale_ = val; }
  void SetHoveredScaleSpeed(float val) { hoveredScaleSpeed_ = val; }

public:
  static const std::string NORMAL_ANIM_;
  static const std::string HOVERED_ANIM_;
  static const std::string PRESSED_ANIM_;
  static const std::string DISABLED_ANIM_;

protected:
  virtual void PostSetAnim(const std::string name, Animation& anim);

private:
  bool hasNormalAnim_;
  bool hasHoveredAnim_;
  bool hasPressedAnim_;
  bool hasDisabledAnim_;

  float hoveredMaxScale_;
  float hoveredScaleSpeed_;
  float pressedMinScale_;
  float pressedScaleSpeed_;
};
