#pragma once

#include <util/i_get_instance.h>

#include "engine.h"

class Object;

class ENGINE_API SceneManager : public util::IGetInstance<SceneManager>
{
public:
	typedef std::map<std::string, Object*> Objects;

	SceneManager();
	virtual ~SceneManager();

	void Update(float delta);
	void Render(RenderTarget& target) const;

	bool AddObject(Object* obj, const std::string& prefix = "");
	bool AddObject(const std::string& name, Object* obj);
	bool RemoveObject(const std::string& name);
	Object* GetObject(const std::string& name) const;
	Objects& GetAllObjects() const;

private:
	void ClearDeadObjects();

private:
	mutable Objects objects_;
};

std::string GetUniqueName(std::string prefix = "");
