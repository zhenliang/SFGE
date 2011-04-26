#include "ui_tooltip.h"

#include "ui_cfg.h"
#include "util_drawable.h"
#include "util_string.h"

namespace UITooltip
{
  namespace
  {
    String tip_;
    Sprite background_;
    bool emptyTip_ = true;

    float setTime; // 记录设置的时间，用于延长显示
    float delayTime = kTooptipDelayTime; // 延迟出现时间
    float fadeInTime = kTooptipFadeinTime; // 淡入过程时间长度

    const float BACKGROUND_EXPEND_SIZE_X = 10.0f;
    const float BACKGROUND_EXPEND_SIZE_Y = 8.0f;
    const Color EMPTY_BACKGROUND_DEFAULT_COL = Color(97, 104, 255, 240);
  }

  void SetBackground(const Sprite& background)
  {
    background_ = background_;
  }

  void UITooltip::Set( const String& tip , float left /*= 0.0f*/, float top /*= 0.0f*/)
  {
    tip_ = tip;
    emptyTip_ = String_IsEmpty(tip);

    // 设置位置

    tip_.SetPosition(left + BACKGROUND_EXPEND_SIZE_X, top + BACKGROUND_EXPEND_SIZE_Y);

    // 设置背景的大小，如果是非图片背景，则同时设置其背景颜色

    float width = tip_.GetRect().GetWidth() + BACKGROUND_EXPEND_SIZE_X * 2;
    float height = tip_.GetRect().GetHeight() + BACKGROUND_EXPEND_SIZE_Y * 2;
    background_.Resize(width, height);
    background_.SetPosition(left, top);
    if (background_.GetImage() == NULL)
      background_.SetColor(EMPTY_BACKGROUND_DEFAULT_COL);

    // 记录设置时间

    setTime = static_cast<float>(clock());
  }

  void Draw(RenderTarget& target)
  {
    if (!emptyTip_ && (clock() - setTime > delayTime * 1000))
    {
      float alpha = 255 * (clock() - setTime - delayTime * 1000) / (fadeInTime * 1000);
      alpha = alpha > 255 ? 255 : alpha;

      SetAlpha(background_, alpha);
      SetAlpha(tip_, alpha);

      target.Draw(background_);
      target.Draw(tip_);
    }
  }

  void Reset()
  {
    Set(String());
  }

}
