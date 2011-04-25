#include "scene_mgr.h"

#include <sstream>

#include <util\container.h>
#include <util\vistors.h>

#include "object.h"
#include "util_vistors.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
  util::Vist(objects_, util::DeleteVisitor_Second());
}

void SceneManager::Update(float delta)
{
  util::Vist(objects_, util::UpdateVisitor_Second(delta));
  ClearDeadObjects();
}

void SceneManager::Render(RenderTarget& target) const
{
  util::Vist(objects_, RenderVisitor_Second(target));
}

bool SceneManager::AddObject(const std::string& name, Object* obj)
{
  return util::Insert(objects_, std::make_pair(name, obj));
}

bool SceneManager::AddObject(Object* obj , const std::string& namePrefix /*= ""*/)
{
  return AddObject(GetUniqueName(namePrefix), obj);
}

bool SceneManager::RemoveObject(const std::string& name)
{
  return util::Remove(objects_, name);
}

Object* SceneManager::GetObject(const std::string& name) const
{
  return util::Get(objects_, name);
}

SceneManager::Objects& SceneManager::GetAllObjects() const
{
  return objects_;
}

void SceneManager::ClearDeadObjects() 
{
  Objects::iterator i = objects_.begin(); 
  Objects::iterator end = objects_.end();
  while (i != end)
  {
    Objects::iterator dead = end;

    if (i->second->GetDead())
      dead = i;

    ++i;

    if (dead != end)
    {
      delete dead->second;
      objects_.erase(dead);
    }
  }
}

std::string GetUniqueName( std::string prefix /*= ""*/ )
{
  static long long nextId = 0;
  std::stringstream ss;
  ss << nextId++;
  return prefix + "_" + ss.str();
}
