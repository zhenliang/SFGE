#include "ui_widget.h"

#include <util\container.h>
#include <util\math_base.h>
#include <util\vistors.h>

#include "input_mgr.h"
#include "sound_mgr.h"
#include "ui_cfg.h"
#include "ui_tooltip.h"
#include "ui_window.h"
#include "util_drawable.h"
#include "util_sprite.h"
#include "util_string.h"
#include "util_vistors.h"

#ifdef _DEBUG
bool UIWidget::drawDebugShape_ = false;
#else
bool UIWidget::drawDebugShape_ = false;
#endif

UIWidget::UIWidget()
: name_()
, topLeft_()
, widthHeight_(Vector2f(100.0f, 100.0f))
, anims_()
, parent_()
, widgets_()
, tooltip_()
, tooltipTopLeft_()
, useRelativeTooltipTopLeft_()
, onMouseEnter_()
, onMouseLeft_()
, onPressed_()
, onReleased_()
, enabled_(true)
, hovered_()
, pressed_()
, visibled_(true)
, alpha_(255)
, textUserData()
, userData()
, debugShape_()
{
  RebuildDebugShape();
}

UIWidget::~UIWidget()
{
  // TODO: DLL 内存空间问题

#if 0
  delete onMouseEnter_;
  delete onMouseLeft_;
  delete onPressed_;
  delete onReleased_;
#endif

  util::Vist(widgets_, util::DeleteVisitor_Second());
}

void UIWidget::Update( float delta )
{
  if (!enabled_ || !visibled_)
    return;

  // 更新子节点

  util::Vist(widgets_, util::UpdateVisitor_Second(delta));

  // 更新子节点时后可能令到自己的状态改变，所以再次判断

  if (!enabled_ || !visibled_)
    return;

  // 更新自身

  const InputManager& input = InputManager::GetInstance();

  float mx = static_cast<float>(input.GetMouseX());
  float my = static_cast<float>(input.GetMouseY());

  if (util::InRect(mx, my, topLeft_.x, topLeft_.y, topLeft_.x + widthHeight_.x,
    topLeft_.y + widthHeight_.y))
  { 
    // 鼠标刚进入
    if (!hovered_)
    {
      OnMouseEnter();
      return;
    }

    // 鼠标按下
    if (input.IsMouseButtonDown(Mouse::Left))
    {
      OnPressed();
      return;
    }

    // 鼠标松开
    if (pressed_ && input.IsMouseButtonReleased(Mouse::Left))
    {
      OnReleased();
      return;
    }
  }
  else
  {
    // 鼠标刚移出
    if (hovered_)
    {
      OnMouseLeft();
      return;
    }
  }
}

void UIWidget::Render( RenderTarget& target ) const
{
  if (!visibled_)
    return;

  util::Vist(widgets_, RenderVisitor_Second(target));

  if (drawDebugShape_)
    target.Draw(debugShape_);

  // 当鼠标悬浮，并且自己的 tooltip 不为空的时候才渲染
  // 如果自己为空依然渲染，可能会屏蔽掉其它元件的 tooltip

  if (hovered_ && !String_IsEmpty(tooltip_))
    UITooltip::Draw(target);
}

void UIWidget::ResetStates()
{
  enabled_ = true;
  hovered_ = false;
  pressed_ = false;
  visibled_ = true;
}

void UIWidget::OnMouseEnter()
{
  hovered_ = true;

  if (!String_IsEmpty(tooltip_))
  {
    if (useRelativeTooltipTopLeft_)
      UITooltip::Set(tooltip_, topLeft_.x + tooltipTopLeft_.x, topLeft_.y + tooltipTopLeft_.y);
    else 
      UITooltip::Set(tooltip_, tooltipTopLeft_.x, tooltipTopLeft_.y);
  }

  if (onMouseEnter_) 
    (*onMouseEnter_)(this);
}

void UIWidget::OnMouseLeft()
{
  if (onMouseLeft_) 
    (*onMouseLeft_)(this);

  if (!String_IsEmpty(tooltip_))
    UITooltip::Reset();

  hovered_ = false;
  pressed_ = false;
}

void UIWidget::OnPressed()
{
  pressed_ = true;

  if (!pressedSoundKey_.empty()) 
    SoundManager::GetInstance().PlaySound(pressedSoundKey_);

  if (onPressed_) 
    (*onPressed_)(this);
}

void UIWidget::OnReleased()
{
  if (onReleased_) 
    (*onReleased_)(this);
  pressed_ = false;
}

void UIWidget::AddWidget( UIWidget* widget, const std::string& name /*= ""*/ )
{
  assert(widget != NULL);
  if (util::Insert(widgets_, std::make_pair(name, widget)))
    widget->SetParent(this);
}

UIWidget* UIWidget::GetWidget( const std::string& name )
{
  return util::Get(widgets_, name);
}

namespace
{
  struct MoveFunctor_Second
  {
    MoveFunctor_Second(Vector2f delta) : delta_(delta) { }
    template <class T>
    void operator()(T& e) const { e.second->Move(delta_); }
    Vector2f delta_;
  };
}

void UIWidget::SetTopLeft( Vector2f val )
{
  Vector2f delta(val.x - topLeft_.x, val.y - topLeft_.y);
  topLeft_ = val;
  util::Vist(widgets_, MoveFunctor_Second(delta));
  PostSetTopLeft();
}

void UIWidget::RebuildDebugShape()
{
  debugShape_ = Shape::Rectangle(topLeft_.x, topLeft_.y, topLeft_.x + widthHeight_.x, 
    topLeft_.y + widthHeight_.y, Color(0, 255, 255), 1.0f, Color(0, 0, 255));
  debugShape_.EnableFill(false);
}

void UIWidget::PostSetTopLeft()
{
  MoveAnims();
  RebuildDebugShape();
}

void UIWidget::PostSetWidthHeight()
{
  ResizeAnims();
  RebuildDebugShape();
}

void UIWidget::SetWidthHeight( Vector2f val )
{
  widthHeight_ = val;
  PostSetWidthHeight();
}

Animation& UIWidget::GetAnim(const std::string& name )
{
  return util::Get(anims_, name);
}

void UIWidget::SetAnim( const std::string& name, Animation anim )
{
  anims_[name] = anim;
  PostSetAnim(name, anims_[name]);
}

void UIWidget::PostSetAnim( const std::string name, Animation& anim )
{
  SetCenter(anim);
  anim.Resize(widthHeight_);
  anim.SetPosition(topLeft_ + widthHeight_ * 0.5f);
}

void UIWidget::MoveAnims()
{
  UTIL_FOREACH(i, anims_, Anims)
    i->second.SetPosition(topLeft_ + widthHeight_ * 0.5f);
}

void UIWidget::ResizeAnims()
{
  UTIL_FOREACH(i, anims_, Anims)
    i->second.Resize(widthHeight_);
}

void UIWidget::SetParent( UIWidget* val )
{
  assert(parent_ == NULL); 
  parent_ = val;
}

namespace
{
  struct SetEnabledFunctor_Second
  {
    explicit SetEnabledFunctor_Second(bool enabled) : enabled_(enabled) { }
    template <class T>
    void operator()(T keyMapped) const { keyMapped.second->SetEnabled(enabled_); }
    bool enabled_;
  };
}

void UIWidget::SetEnabled( bool val )
{
  enabled_ = val;

  if (!enabled_)
  {
    hovered_ = false;
    pressed_ = false;
  }

  util::Vist(widgets_, SetEnabledFunctor_Second(enabled_));
}

namespace
{
  struct SetVisibledFunctor_Second
  {
    explicit SetVisibledFunctor_Second(bool visibled) : visibled_(visibled) { }
    template <class T>
    void operator()(T& e) const { e.second->SetVisibled(visibled_); }
    bool visibled_;
  };
}

void UIWidget::SetVisibled( bool val )
{
  visibled_ = val;
  util::Vist(widgets_, SetVisibledFunctor_Second(visibled_));
}

void UIWidget::SetVisibled(const std::string& key, bool val)
{
  UIWidget* widget = GetWidget(key);
  if (widget)
    widget->SetVisibled(val);
}

namespace
{
  struct SetAlphaFunctor_Second
  {
    explicit SetAlphaFunctor_Second(float alpha) : alpha_(alpha) { }
    template <class T>
    void operator()(T& e) const { e.second->SetAlpha(alpha_); }
    float alpha_;
  };

  struct SetAnimAlphaFunctor_Second
  {
    explicit SetAnimAlphaFunctor_Second(float alpha) : alpha_(alpha) { }
    template <class T>
    void operator()(T& e) const { ::SetAlpha(e.second, alpha_); }
    float alpha_;
  };
}

void UIWidget::SetAlpha( float val )
{
  alpha_ = val;
  util::Vist(anims_, SetAnimAlphaFunctor_Second(alpha_));
  util::Vist(widgets_, SetAlphaFunctor_Second(alpha_));
}

void UIWidget::Move( Vector2f delta )
{
  Vector2f newTopLeft(topLeft_.x + delta.x, topLeft_.y + delta.y);
  SetTopLeft(newTopLeft);
}

void UIWidget::SetTop( float top )
{
  Vector2f topLeft(topLeft_.x, top); SetTopLeft(topLeft);
}

void UIWidget::SetLeft( float left )
{
  Vector2f topLeft(left, topLeft_.y); SetTopLeft(topLeft);
}

void UIWidget::SetWidth( float width )
{
  Vector2f widthHeight(width, widthHeight_.y); SetWidthHeight(widthHeight);
}

void UIWidget::SetHeight( float height )
{
  Vector2f widthHeight(widthHeight_.x, height); SetWidthHeight(widthHeight);
}

