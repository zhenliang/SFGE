#pragma once

#include "engine.h"

#include <util\i_get_instance.h>

class UIWidget;

enum UITypes
{
	UIT_Begin,

	UIT_Button,
	UIT_Plane,
	UIT_Line,
	UIT_Label,
	UIT_Tooltip,
	UIT_Window,

	UIT_End
};

class ENGINE_API UIManager : public util::IGetInstance<UIManager>
{
public:
	UIManager() {}
	virtual ~UIManager() {}

	UIWidget* Create(int type) { return NULL; }
	UIWidget* Create(std::string luafile);
};