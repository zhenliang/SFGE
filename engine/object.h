#pragma once

#include "engine.h"

class ENGINE_API Object
{
public:
	Object();
	virtual ~Object();

	void Update(float delta);
	void Render(RenderTarget& target);

	bool GetDead() const { return dead_; }
	std::string GetName() const { return name_; }
	void* GetUserData() const { return userData; }
	std::string GetTextUserData() const { return textUserData; }

	void SetDead(bool dead) { dead_ = dead; }
	void SetName(const std::string& name) { name_ = name; }
	void SetUserData(void* val) { userData = val; }	
	void SetTextUserData(std::string val) { textUserData = val; }

	virtual void OnUpdate(float delta) {}
	virtual void OnRender(RenderTarget& target) {}

protected:
	std::string name_;
	bool dead_;

	void* userData;
	std::string textUserData;
};
