#include "ui_mgr.h"

#include "script_mgr.h"

UIWidget* UIManager::Create(int type)
{
  // TODO:
  return NULL;
}

UIWidget* UIManager::Create(const std::string& luafile)
{
	ScriptManager& scriptMgr = ScriptManager::GetInstance();
	scriptMgr.DoFile(luafile);
	return scriptMgr.GetUserdata<UIWidget>("UIWidgetPtr");
}