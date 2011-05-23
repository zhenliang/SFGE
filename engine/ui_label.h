#pragma once

#include "ui_widget.h"

// 当 SetWidthHeight 的时候，如果其中一个为 0 ，则点击检测将起不到作用。
// 因为用于检测的矩形已经成为直线，所以 label 的 SetWidthHeight 有两个意义，
// Width 为矩形的长，Height 为矩形的长河字体的 size 大小

class ENGINE_API UILabel : public UIWidget
{
public:
	UILabel();
	virtual ~UILabel() {}

	virtual void Render(RenderTarget& target) const;
	virtual void SetAlpha(float val);
    virtual void PostSetTopLeft();

	String& GetString() { return string_; }
	void SetString(const String& str);

	void SetSize(float size);
	void SetText(std::string text);
	void SetText(std::wstring text);
	void SetColor(Color color);

    virtual void OnMouseEnter();
    virtual void OnMouseLeft();
    virtual void OnPressed();

    // 设置鼠标悬挂时的 Style ，当鼠标划出的时候其风格会被撤销，划入则恢复
    // 默认为 -1 ，表示鼠标划入划出时不做操作
    void SetHoveredStyle(int style);

private:
	void RecomputeWidthHeight();

private:
	String string_;
    int hoveredStyle_;
};
