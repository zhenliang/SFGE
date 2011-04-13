#include "ui_line.h"

#include "util_drawable.h"

UILine::UILine() :
lineShape_(),
color_(),
thickness_(1.0f)
{

}

void UILine::PostSetTopLeft()
{
	__super::PostSetTopLeft();
	RebuildLineShape();
}

void UILine::PostSetWidthHeight()
{
	__super::PostSetWidthHeight();
	RebuildLineShape();
}

void UILine::SetColor( Color color )
{
	color_ = color;
	RebuildLineShape();
}

void UILine::SetThickness( float thickness )
{
	thickness_ = thickness;
	RebuildLineShape();
}

void UILine::RebuildLineShape()
{
	lineShape_ = Shape::Line(topLeft_, topLeft_ + widthHeight_, thickness_, color_);
}

void UILine::Render( RenderTarget& target ) const
{
	if (!visibled_)
		return;

	target.Draw(lineShape_);
}

void UILine::Update( float delta )
{
	if (!visibled_)
		return;
}

void UILine::SetAlpha( float val )
{
	__super::SetAlpha(val);
	::SetAlpha(lineShape_, alpha_);
}