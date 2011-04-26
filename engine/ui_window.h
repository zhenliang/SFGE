#pragma once

#include "ui_panel.h"

class UIButton;

class ENGINE_API UIWindow : public UIPanel
{
public:
  UIWindow();
  virtual ~UIWindow() {}

  UIButton* GetCloseButton();

private:
  void InitCloseButton();

public:
  static const std::string CLOSE_BUTTON;
};
