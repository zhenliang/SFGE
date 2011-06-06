#pragma once

#include "animation.h"
#include "engine.h"

#include <util\delegate.h>

class ENGINE_API UIWidget
{
public:
  typedef util::MultiDelegate1<UIWidget*>* CallBack;
  typedef std::map<std::string, Animation> Anims;
  typedef std::multimap<std::string, UIWidget*> Widgets;

  UIWidget();
  virtual ~UIWidget();

  virtual void Update(float delta);
  virtual void Render(RenderTarget& target) const;

  std::string GetName() const { return name_; }
  void SetName(std::string val) { name_ = val; }

  float GetTop() const { return topLeft_.y; }
  float GetLeft() const { return topLeft_.x; }
  float GetBottom() const { return topLeft_.y + widthHeight_.y; }
  float GetRight() const { return topLeft_.x + widthHeight_.x; }
  float GetWidth() const { return widthHeight_.x; }
  float GetHeight() const { return widthHeight_.y; }
  Vector2f GetTopLeft() const { return topLeft_; }
  Vector2f GetBottomRight() const { return topLeft_ + widthHeight_; }
  Vector2f GetWidthHeight() const { return widthHeight_; }

  void SetTop(float top);
  void SetLeft(float left);
  void SetWidth(float width);
  void SetHeight(float height);
  void SetTopLeft(Vector2f val);
  void SetWidthHeight(Vector2f val);

  virtual void Move(Vector2f delta);

  Animation& GetAnim(const std::string& name);
  void SetAnim(const std::string& name, Animation anim);

  UIWidget* GetParent() const { return parent_; }
  void AddWidget(UIWidget* widget, const std::string& name = "");
  UIWidget* GetWidget(const std::string& name);
  template <class T> T* GetWidget(const std::string& name);
  Widgets& GetAllWidgets() { return widgets_; }
  void RemoveWidget(const std::string& name);

  String GetTooltip() const { return tooltip_; }
  Vector2f& GetTooltipTopLeft() { return tooltipTopLeft_; }
  bool GetUseRelativeTooltipTopLeft() const { return useRelativeTooltipTopLeft_; }
  void SetTooltip(const String& val) { tooltip_ = val; }
  void SetTooltipTopLeft(const Vector2f& val) { tooltipTopLeft_ = val; }
  void SetUseRelativeTooltipTopLeft(bool val) { useRelativeTooltipTopLeft_ = val; }

  bool GetEnabled() const { return enabled_; }
  bool GetVisibled() const { return visibled_; }
  float GetAlpha() const { return alpha_; }

  void SetEnabled(bool val);
  void SetVisibled(bool val);
  void SetVisibled(const std::string& key, bool val);
  virtual void SetAlpha(float val);

  CallBack GetOnMouseEnter() const { return onMouseEnter_; }
  CallBack GetOnMouseLeft() const { return onMouseLeft_; }
  CallBack GetOnPressed() const { return onPressed_; }
  CallBack GetOnReleased() const { return onReleased_; }

  void SetOnMouseEnter(CallBack val) { if (onMouseEnter_) delete onMouseEnter_; onMouseEnter_ = val; }
  void SetOnMouseLeft(CallBack val) { if (onMouseLeft_) delete onMouseLeft_; onMouseLeft_ = val; }
  void SetOnPressed(CallBack val) { if (onPressed_) delete onPressed_; onPressed_ = val; }
  void SetOnReleased(CallBack val) { if (onReleased_) delete onReleased_; onReleased_ = val; }

  std::string GetPressedSoundKey() const { return pressedSoundKey_; }
  void SetPressedSoundKey(std::string val) { pressedSoundKey_ = val; }

  void* GetUserData() const { return userData; }
  std::string GetTextUserData() const { return textUserData; }

  void SetUserData(void* val) { userData = val; }
  void SetTextUserData(const std::string& val) { textUserData = val; }

  static bool GetDrawDebugShape() { return drawDebugShape_; }
  static void SetDrawDebugShape(bool val) { drawDebugShape_ = val; }

protected:
  virtual void PostSetTopLeft();
  virtual void PostSetWidthHeight();
  virtual void PostSetAnim(const std::string name, Animation& anim);

  virtual void OnMouseEnter();
  virtual void OnMouseLeft();
  virtual void OnPressed();
  virtual void OnReleased();

  void SetParent(UIWidget* val);
  void MoveAnims();
  void ResizeAnims();
  void RebuildDebugShape();
  void ResetStates();

protected:
  std::string name_;

  Vector2f topLeft_;
  Vector2f widthHeight_;

  mutable Anims anims_;

  UIWidget* parent_;
  Widgets widgets_;

  String tooltip_;
  Vector2f tooltipTopLeft_;
  bool useRelativeTooltipTopLeft_;

  CallBack onMouseEnter_;
  CallBack onMouseLeft_;
  CallBack onPressed_;
  CallBack onReleased_;

  bool enabled_;
  bool hovered_;
  bool pressed_;
  bool visibled_;

  float alpha_;

  std::string pressedSoundKey_;

  void* userData;
  std::string textUserData;

  Shape debugShape_;
  static bool drawDebugShape_;
};

template <class T>
T* UIWidget::GetWidget(const std::string& name)
{
  return dynamic_cast<T*>(GetWidget(name));
}
