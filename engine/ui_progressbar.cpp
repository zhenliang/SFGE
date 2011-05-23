#include "ui_progressbar.h"

#include <util\container.h>
#include <util\math_base.h>

#include "util_sprite.h"

const std::string UIProgressbar::BOTTOM_ANIM_ = "_bottom";
const std::string UIProgressbar::MID_ANIM_ = "_mid";
const std::string UIProgressbar::TOP_ANIM_ = "_top";

UIProgressbar::UIProgressbar()
: hasMidAnim_()
, maxValue_(100.f)
, curValue_()
{

}

void UIProgressbar::Update(float delta)
{
  if (!visibled_)
    return;

  __super::Update(delta);

  UTIL_FOREACH(i, anims_, Anims)
    i->second.Update(delta);
}

void UIProgressbar::Render(RenderTarget& target) const
{
  if (!visibled_)
    return;

  UTIL_FOREACH(i, anims_, Anims)
    target.Draw(i->second);

  __super::Render(target);
}

void UIProgressbar::PostSetTopLeft()
{
  __super::PostSetTopLeft();
  if (hasMidAnim_)
    anims_[MID_ANIM_].SetX(GetLeft());
}

void UIProgressbar::PostSetWidthHeight()
{
  __super::PostSetWidthHeight();
  UpdateMidAnim();
}

void UIProgressbar::PostSetAnim(const std::string name, Animation& anim)
{
  __super::PostSetAnim(name, anim);

  if (name == MID_ANIM_)
  {
    hasMidAnim_ = true;
    UpdateMidAnim();
    SetCenter(anims_[MID_ANIM_], 0.f, 0.5f);
    anims_[MID_ANIM_].SetX(GetLeft());
  }
}

void UIProgressbar::UpdateMidAnim()
{
  if (!hasMidAnim_)
    return;

  Vector2f size = GetWidthHeight();
  size.x *= curValue_ / maxValue_;
  size.x = util::ClamUp(size.x, 1.f); // 下限 1 像素，size.x <= 0 则在 SFML 内部不作处理
  anims_[MID_ANIM_].Resize(size);
}

void UIProgressbar::SetMaxValue(float val)
{
  maxValue_ = val;
  UpdateMidAnim();
}

void UIProgressbar::SetCurValue(float val)
{
  curValue_ = val;
  UpdateMidAnim();
}
