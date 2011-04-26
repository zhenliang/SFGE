#include "animation.h"

namespace
{
  const int DEFAULT_ROW = 1;
  const int DEFAULT_COLUMN = 1;
  const int DEFAULT_TOTAL_FRAMES = DEFAULT_ROW * DEFAULT_COLUMN;
  const float DEFAULT_FPS = 10.0f;
}

Animation::Animation()
: Sprite()
, row_(DEFAULT_ROW)
, column_(DEFAULT_COLUMN)
, totalFrames_(DEFAULT_TOTAL_FRAMES)
, fps_(DEFAULT_FPS)
, curFrame_()
, timePerFrame_(1.0f/DEFAULT_FPS)
, timeSinceLastFrame_()
{

}

Animation::Animation(const Image& img, int row, int column, int totalFrames, float fps,
                     const Vector2f& position /*= Vector2f(0, 0)*/,
                     const Vector2f& scale /*= Vector2f(1, 1)*/, float rotation /*= 0.f*/,
                     const Color& col /*= Color(255, 255, 255, 255)*/)
                     : Sprite(img, position, scale, rotation, col)
                     , row_(DEFAULT_ROW)
                     , column_(DEFAULT_COLUMN)
                     , totalFrames_(DEFAULT_TOTAL_FRAMES)
                     , fps_(DEFAULT_FPS)
                     , curFrame_()
                     , timePerFrame_(1.0f/DEFAULT_FPS)
                     , timeSinceLastFrame_()
{
  RecomputeSubRect();
}

Animation::~Animation()
{

}

void Animation::Update( float delta )
{
  if (timeSinceLastFrame_ >= timePerFrame_)
  {
    while (timeSinceLastFrame_ >= timePerFrame_)
    {
#if 0 // 这种方法在 timeSinceLastFrame 过大的时候会占用太多时间

      timeSinceLastFrame_ -= timePerFrame_;
      if (++curFrame_ >= totalFrames_)
        curFrame_ = 0;

#else // 用触发避免了 timeSiceLastFarm 的性能损失，但在通常时候都比第一种方法耗时多

      int cnt = timeSinceLastFrame_ / timePerFrame_;
      timeSinceLastFrame_ -= cnt * timePerFrame_;
      curFrame_ += cnt;
      if (curFrame_ >= totalFrames_)
        curFrame_ = 0;
#endif
    }

    RecomputeSubRect();
  }

  timeSinceLastFrame_ += delta;
}

void Animation::SetRow( int val )
{
  row_ = val;
  RecomputeTotalFrames();
  RecomputeSubRect();
}

void Animation::SetColumn( int val )
{
  column_ = val;
  RecomputeTotalFrames();
  RecomputeSubRect();
}

void Animation::SetTotalFrames( int val )
{
  assert(val >= 1);
  assert(val <= row_ * column_);
  totalFrames_ = val;
}

void Animation::SetFPS( float val )
{
  fps_ = val;
  timePerFrame_ = 1.0f / fps_;
}

void Animation::RecomputeSubRect()
{
  assert(GetImage());
  float width = GetImage()->GetWidth() / column_;
  float height = GetImage()->GetHeight() / row_;
  float x = width * (curFrame_ % column_);
  float y = height * (curFrame_ % row_);
  IntRect subRect(x, y, x + width, y + height);
  SetSubRect(subRect);
}

void Animation::RecomputeTotalFrames()
{
  int maxFrame = row_ * column_;
  totalFrames_ = std::min(totalFrames_, maxFrame);
}
