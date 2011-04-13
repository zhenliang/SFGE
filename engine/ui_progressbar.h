#pragma once

#include "ui_widget.h"

class ENGINE_API UIProgressbar : public UIWidget
{
public:
    UIProgressbar();
    virtual ~UIProgressbar() {}

    virtual void Update(float delta);
    virtual void Render(RenderTarget& target) const;

    virtual void PostSetTopLeft();
    virtual void PostSetWidthHeight();
    virtual void PostSetAnim(const std::string name, Animation& anim);

    float GetMaxValue() const { assert(maxValue_ > 1e-10); return maxValue_; }
    float GetCurValue() const { return curValue_; }

    void SetMaxValue(float val);
    void SetCurValue(float val);

private:
    void UpdateMidAnim();

public:
    static const std::string BOTTOM_ANIM_;
    static const std::string MID_ANIM_;
    static const std::string TOP_ANIM_;

private:
    bool hasMidAnim_;

    float maxValue_;
    float curValue_;
};