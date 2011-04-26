#include "object.h"

Object::Object() 
: name_()
, dead_()
, userData()
, textUserData()
{

}

Object::~Object()
{

}

void Object::Update( float delta )
{
  if (dead_)
    return;

  OnUpdate(delta);
}

void Object::Render( RenderTarget& target )
{
  if (dead_)
    return;

  OnRender(target);
}