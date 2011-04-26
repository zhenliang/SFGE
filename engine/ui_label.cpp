#include "ui_label.h"

#include "util_drawable.h"
#include "util_string.h"

UILabel::UILabel()
: UIWidget()
, string_()
, hoveredStyle_(-1)
{

}

void UILabel::Render( RenderTarget& target ) const
{
  if (!visibled_)
    return;

  __super::Render(target);
  target.Draw(string_);
}

void UILabel::PostSetTopLeft()
{
  __super::PostSetTopLeft();
  string_.SetPosition(topLeft_);
}

void UILabel::SetText( std::string text )
{
  string_.SetText(text);
  RecomputeWidthHeight();
}

void UILabel::SetText( std::wstring text )
{
  string_.SetText(text);
  RecomputeWidthHeight();
}

void UILabel::SetColor( Color color )
{
  string_.SetColor(color);
}

void UILabel::SetSize( float size )
{
  string_.SetSize(size);
  RecomputeWidthHeight();
}

void UILabel::RecomputeWidthHeight()
{
  FloatRect rect = string_.GetRect();
  SetWidthHeight(Vector2f(rect.GetWidth(), rect.GetHeight()));
}

void UILabel::SetString( const String& str )
{
  string_ = str;
  string_.SetPosition(topLeft_);
  RecomputeWidthHeight();
}

void UILabel::SetAlpha( float val )
{
  __super::SetAlpha(val);
  ::SetAlpha(string_, alpha_);
}

void UILabel::SetHoveredStyle(int style)
{
  hoveredStyle_ = style;
}

void UILabel::OnMouseEnter()
{
  __super::OnMouseEnter();
  if (hoveredStyle_ != -1)
    String_AddStyle(string_, String::Underlined);
}

void UILabel::OnMouseLeft()
{
  __super::OnMouseLeft();
  if (hoveredStyle_ != -1)
    String_RemoveStyle(string_, String::Underlined);
}

void UILabel::OnPressed()
{
  __super::OnPressed();
  if (hoveredStyle_ != -1)
    String_RemoveStyle(string_, String::Underlined);
}
