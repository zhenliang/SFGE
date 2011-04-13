#include "ui_mgr.h"

#include "script_mgr.h"

UIWidget* UIManager::Create( std::string luafile )
{
	ScriptManager& scriptMgr = ScriptManager::GetInstance();
	scriptMgr.DoFile(luafile);
	return scriptMgr.GetUserdata<UIWidget>("UIWidgetPtr");
}