#include "ui_panel.h"

const std::string UIPanel::NORMAL_ANIM_ = "_normal";
const std::string UIPanel::DISABLED_ANIM_ = "_disabled";

UIPanel::UIPanel() 
: hasNormalAnim_()
, hasDisabledAnim_()
{
}

void UIPanel::Update( float delta )
{
  if (!visibled_ )
    return;

  if (!enabled_ && hasDisabledAnim_)
    anims_[DISABLED_ANIM_].Update(delta);
  else if (hasNormalAnim_)
    anims_[NORMAL_ANIM_].Update(delta);

  __super::Update(delta);
}

void UIPanel::Render( RenderTarget& target ) const
{
  if (!visibled_)
    return;

  if (!enabled_ && hasDisabledAnim_)
    target.Draw(anims_[DISABLED_ANIM_]);
  else if (hasNormalAnim_)
    target.Draw(anims_[NORMAL_ANIM_]);

  __super::Render(target);
}

void UIPanel::PostSetAnim( const std::string name, Animation& anim )
{
  __super::PostSetAnim(name, anim);

  if (!hasNormalAnim_ && name == NORMAL_ANIM_)
    hasNormalAnim_ = true;
  if (!hasDisabledAnim_ && name == DISABLED_ANIM_)
    hasDisabledAnim_ = true;
}