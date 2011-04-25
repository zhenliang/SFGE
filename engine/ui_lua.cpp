#include "ui_lua.h"

#include <lua\lua.hpp>
#include <util\lua_table.h>

#include "image_mgr.h"
#include "script_mgr.h"
#include "soundbuf_mgr.h"
#include "string_mgr.h"
#include "ui_button.h"
#include "ui_label.h"
#include "ui_line.h"
#include "ui_panel.h"
#include "ui_progressbar.h"
#include "ui_window.h"
#include "util_lua.h"
#include "util_sprite.h"

void RegisterUICreators()
{
  ScriptManager& scriptMgr = ScriptManager::GetInstance();
  scriptMgr.RegisterFunc("Button", Button);
  scriptMgr.RegisterFunc("Label", Label);
  scriptMgr.RegisterFunc("Line", Line);
  scriptMgr.RegisterFunc("Panel", Panel);
  scriptMgr.RegisterFunc("Progressbar", Progressbar);
  scriptMgr.RegisterFunc("Window", Window_);
}

namespace
{
  void SetName(lua_State* L, UIWidget* widget)
  {
    if (util::HasField(L, "name"))
    {
      std::string name = util::GetField_String(L, "name");
      widget->SetName(name);
    }
  }

  void SetTopLeftWidthHeight(lua_State* L, UIWidget* widget)
  {
    if (util::HasField(L, "top") && util::HasField(L, "left"))
    {
      float left = util::GetField_Number(L, "left");
      float top = util::GetField_Number(L, "top");
      widget->SetTopLeft(Vector2f(left, top));
    }

    if (util::HasField(L, "width") && util::HasField(L, "height"))
    {
      float width = util::GetField_Number(L, "width");
      float height = util::GetField_Number(L, "height");
      widget->SetWidthHeight(Vector2f(width, height));
    }
  }

  void SetAnim(lua_State* L, UIWidget* widget, std::string widgetAnimKey, std::string luaAnimFieldKey)
  {
    if (util::HasField(L, luaAnimFieldKey.c_str()))
    {
      std::string imgKey = util::GetField_String(L, luaAnimFieldKey);
      if (!imgKey.empty())
      {
        Animation anim;
        Image& img = ImageManager::GetInstance().GetImage(imgKey);
        SetImage(anim, img);
        widget->SetAnim(widgetAnimKey, anim);
      }
    }
  }

  void SetTooltip(lua_State* L, UIWidget* widget)
  {
    if (util::HasField(L, "tooltipStringKey"))
    {
      std::string tooltipStringKey = util::GetField_String(L, "tooltipStringKey");
      if (!tooltipStringKey.empty())
      {
        String& str = StringManager::GetInstance().GetString(tooltipStringKey);
        widget->SetTooltip(str);
      }
    }

    if (util::HasField(L, "tooltipTopleft"))
    {
      lua_getfield(L, -1, "tooltipTopleft");
      Vector2f topleft;
      SetVector2f(L, topleft);
      lua_pop(L, 1);
      widget->SetTooltipTopLeft(topleft);
    }

    if (util::HasField(L, "useRelativeTooltipTopleft"))
    {
      bool useRelativeTooltipTopleft = util::GetField_Boolean(L, "useRelativeTooltipTopleft");
      widget->SetUseRelativeTooltipTopLeft(useRelativeTooltipTopleft);
    }
  }

  void SetTextUserData(lua_State* L, UIWidget* widget)
  {
    if (util::HasField(L, "textUserData"))
    {
      std::string textUserData = util::GetField_String(L, "textUserData");
      if (!textUserData.empty())
        widget->SetTextUserData(textUserData);
    }
  }

  void SetPressedSoundKey(lua_State* L, UIWidget* widget)
  {
    if (util::HasField(L, "pressedSoundKey"))
      widget->SetPressedSoundKey(util::GetField_String(L, "pressedSoundKey"));
  }

  void AddWidget(lua_State* L, UIWidget* widget)
  {
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) 
    {
      if (lua_islightuserdata(L, -1))
      {
        UIWidget* subWidget = static_cast<UIWidget*>(lua_touserdata(L, -1));
        widget->AddWidget(subWidget, subWidget->GetName());
      }

      lua_pop(L, 1); 
    }
  }

  void SetButton(lua_State* L, UIButton* btn)
  {
    SetName(L, btn);
    SetTopLeftWidthHeight(L, btn);
    SetAnim(L, btn, UIButton::NORMAL_ANIM_, "normalAnim");
    SetAnim(L, btn, UIButton::HOVERED_ANIM_, "hoveredAnim");
    SetAnim(L, btn, UIButton::PRESSED_ANIM_, "pressedAnim");
    SetAnim(L, btn, UIButton::DISABLED_ANIM_, "disabledAnim");

    AddWidget(L, btn);
  }

}

int Button( lua_State* L )
{
  UIButton* btn = new UIButton;

  SetName(L, btn);
  SetTopLeftWidthHeight(L, btn);
  SetTooltip(L, btn);
  SetAnim(L, btn, UIButton::NORMAL_ANIM_, "normalAnim");
  SetAnim(L, btn, UIButton::HOVERED_ANIM_, "hoveredAnim");
  SetAnim(L, btn, UIButton::PRESSED_ANIM_, "pressedAnim");
  SetAnim(L, btn, UIButton::DISABLED_ANIM_, "disabledAnim");
  SetTextUserData(L, btn);
  SetPressedSoundKey(L, btn);

  AddWidget(L, btn);

  lua_pushlightuserdata(L, btn);

  return 1;
}

int Label( lua_State* L )
{
  UILabel* label = new UILabel;

  SetName(L, label);
  SetTopLeftWidthHeight(L, label);
  SetTooltip(L, label);
  SetTextUserData(L, label);
  SetPressedSoundKey(L, label);

  if (util::HasField(L, "hoveredStyle"))
  {
    int style = util::GetField_Number(L, "hoveredStyle");
    label->SetHoveredStyle(style);
  }

  if (util::HasField(L, "stringKey"))
  {
    std::string stringKey = util::GetField_String(L, "stringKey");
    if (!stringKey.empty())
      label->SetString(StringManager::GetInstance().GetString(stringKey));
  }

  if (util::HasField(L, "color"))
  {
    String& str = label->GetString();
    Color& color = const_cast<Color&>(str.GetColor());
    lua_getfield(L, -1, "color");
    SetColor(L, color);
    lua_pop(L, 1);
  }

  lua_pushlightuserdata(L, label);

  return 1;
}

int Line(lua_State* L)
{
  UILine* line = new UILine;
  SetName(L, line);
  SetTopLeftWidthHeight(L, line);
  SetTooltip(L, line);
  SetTextUserData(L, line);
  lua_pushlightuserdata(L, line);
  return 1;
}

int Panel( lua_State* L )
{
  UIPanel* panel = new UIPanel;

  SetName(L, panel);
  SetTopLeftWidthHeight(L, panel);
  SetTooltip(L, panel);
  SetAnim(L, panel, UIPanel::NORMAL_ANIM_, "normalAnim");
  SetAnim(L, panel, UIPanel::DISABLED_ANIM_, "disabledAnim");
  SetTextUserData(L, panel);

  AddWidget(L, panel);

  lua_pushlightuserdata(L, panel);

  return 1;
}

int Progressbar(lua_State* L)
{
  UIProgressbar* progressbar = new UIProgressbar;

  SetName(L, progressbar);
  SetTopLeftWidthHeight(L, progressbar);
  SetTooltip(L, progressbar);
  SetAnim(L, progressbar, UIProgressbar::BOTTOM_ANIM_, "bottomAnim");
  SetAnim(L, progressbar, UIProgressbar::MID_ANIM_, "midAnim");
  SetAnim(L, progressbar, UIProgressbar::TOP_ANIM_, "topAnim");
  SetTextUserData(L, progressbar);

  AddWidget(L, progressbar);

  lua_pushlightuserdata(L, progressbar);

  return 1;
}

int Window_( lua_State* L )
{
  UIWindow* window = new UIWindow;

  SetName(L, window);
  SetTopLeftWidthHeight(L, window);
  SetTooltip(L, window);
  SetAnim(L, window, UIPanel::NORMAL_ANIM_, "normalAnim");
  SetAnim(L, window, UIPanel::DISABLED_ANIM_, "disabledAnim");
  SetTextUserData(L, window);

  AddWidget(L, window);

  // ÅäÖÃ¹Ø±Õ°´Å¥

  if (util::HasField(L, "closeBtn"))
  {
    lua_pushstring(L, "closeBtn");
    lua_gettable(L, -2);
    if (lua_istable(L, -1))
      SetButton(L, window->GetCloseButton());
    lua_pop(L, 1);
  }

  lua_pushlightuserdata(L, window);

  return 1;
}
