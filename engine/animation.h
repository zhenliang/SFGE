#pragma once

#include "engine.h"

class ENGINE_API Animation : public Sprite
{
public:
	Animation();	
	Animation(const Image& img, int row, int column, int totalFrames, float fps,
		const Vector2f& position = Vector2f(0, 0),
		const Vector2f& scale = Vector2f(1, 1),
		float rotation = 0.f,
		const Color& col = Color(255, 255, 255, 255));
	virtual ~Animation();

	void Update(float delta);

	int GetRow() const;
	int GetColumn() const { return column_; }
	int GetTotalFrames() const { return totalFrames_; }
	float GetFPS() const { return fps_; }

	void SetRow(int val);
	void SetColumn(int val);
	void SetTotalFrames(int val);
	void SetFPS(float val);

private:
	void UpdateSubRect();
	void UpdateTotalFrames();
	void UpdateCurFrame(float delta);

protected:
	int row_;
	int column_;
	int totalFrames_;
	float fps_;

	int curFrame_;
	float timePerFrame_;
	float timeSinceLastFrame_;
};