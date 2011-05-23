#include "ui_button.h"

const std::string UIButton::NORMAL_ANIM_ = "_normal";
const std::string UIButton::HOVERED_ANIM_ = "_hovered";
const std::string UIButton::PRESSED_ANIM_ = "_pressed";
const std::string UIButton::DISABLED_ANIM_ = "_disabled";

UIButton::UIButton() 
: hasNormalAnim_()
, hasHoveredAnim_()
, hasPressedAnim_()
, hasDisabledAnim_()
, hoveredMaxScale_(1.2f)
, hoveredScaleSpeed_(1.0f / 120.0f)
, pressedMinScale_(1.0f)
, pressedScaleSpeed_(1.0f / 20.0f)
{

}

void UIButton::Update( float delta )
{
  if (!visibled_)
    return;

  // 更新对应状态的动画

  if (!enabled_ && hasDisabledAnim_)
    anims_[DISABLED_ANIM_].Update(delta);
  else if (pressed_ && hasPressedAnim_)
    anims_[PRESSED_ANIM_].Update(delta);
  else if (hovered_ && hasHoveredAnim_)
    anims_[HOVERED_ANIM_].Update(delta);
  else if (hasNormalAnim_)
    anims_[NORMAL_ANIM_].Update(delta);

  // 鼠标悬挂与否时的缩放

  if (hoveredMaxScale_ != -1.0f && hasNormalAnim_)
  {
    Animation& anim = anims_[NORMAL_ANIM_];
    float curRelateScale = anim.GetScale().x;
    float originRelateScale = widthHeight_.x / anim.GetSubRect().GetWidth();
    float relateMaxScale = originRelateScale * hoveredMaxScale_;
    float relateMinScale = originRelateScale * pressedMinScale_;

    if (hovered_)
    {
      // 鼠标未按下与按下时的缩放

      if (!pressed_)
      {
        if (curRelateScale < relateMaxScale)
          anim.Scale(Vector2f(1.0f + hoveredScaleSpeed_, 1.0f + hoveredScaleSpeed_));
        else if (curRelateScale > relateMaxScale)
          anim.SetScale(Vector2f(relateMaxScale, relateMaxScale));
      }
      else
      {
        if (curRelateScale > relateMinScale)
          anim.Scale(Vector2f(1.0f - pressedScaleSpeed_, 1.0f - pressedScaleSpeed_));
        else if (curRelateScale < relateMinScale)
          anim.SetScale(Vector2f(relateMinScale, relateMinScale));
      }
    }
    else
    {
      if (curRelateScale > originRelateScale)
        anim.Scale(Vector2f(1.0f - hoveredScaleSpeed_, 1.0f - hoveredScaleSpeed_));
      else if ((originRelateScale - curRelateScale) > hoveredScaleSpeed_)
        anim.Scale(Vector2f(1.0f + hoveredScaleSpeed_, 1.0f + hoveredScaleSpeed_));
      else 
        anim.SetScale(Vector2f(originRelateScale, originRelateScale));
    }
  }

  __super::Update(delta);
}

void UIButton::Render( RenderTarget& target ) const
{
  if (!visibled_)
    return;

  if (!enabled_ && hasDisabledAnim_)
    target.Draw(anims_[DISABLED_ANIM_]);
  else if (pressed_ && hasPressedAnim_)
    target.Draw(anims_[PRESSED_ANIM_]);
  else if (hovered_ && hasHoveredAnim_)
    target.Draw(anims_[HOVERED_ANIM_]);
  else if (hasNormalAnim_)
    target.Draw(anims_[NORMAL_ANIM_]);

  __super::Render(target);
}

void UIButton::PostSetAnim( const std::string name, Animation& anim )
{
  __super::PostSetAnim(name, anim);

  if (!hasNormalAnim_ && name == NORMAL_ANIM_)
    hasNormalAnim_ = true;
  if (!hasHoveredAnim_ && name == HOVERED_ANIM_)
    hasHoveredAnim_ = true;
  if (!hasPressedAnim_ && name == PRESSED_ANIM_)
    hasPressedAnim_ = true;
  if (!hasDisabledAnim_ && name == DISABLED_ANIM_)
    hasDisabledAnim_ = true;
}
