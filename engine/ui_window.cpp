#include "ui_window.h"

#include <util\container.h>
#include <util\delegate.h>

#include "ui_button.h"

const std::string UIWindow::CLOSE_BUTTON = "_closeButton";

namespace
{
  template <bool visible>
  void SetParentVisibleFunc(UIWidget* widget)
  {
    if (widget && widget->GetParent())
      widget->GetParent()->SetVisibled(visible);
  }
}

UIWindow::UIWindow()
{
  InitCloseButton();
}

UIButton* UIWindow::GetCloseButton()
{
  return dynamic_cast<UIButton*>(util::Get(widgets_, CLOSE_BUTTON));
}

void UIWindow::InitCloseButton()
{
  UIButton* closeBtn = new UIButton;
  util::MultiDelegate1<UIWidget*>* onReleased = new util::MultiDelegate1<UIWidget*>;
  *onReleased += util::NewDelegate(SetParentVisibleFunc<false>);
  closeBtn->SetOnReleased(onReleased);
  AddWidget(closeBtn, CLOSE_BUTTON);
}