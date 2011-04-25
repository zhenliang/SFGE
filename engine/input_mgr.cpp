#include "input_mgr.h"

InputManager::InputManager() 
: mouseX_()
, mouseY_()
{
  Reset();
}

bool InputManager::IsKeyDown( Key::Code code ) const
{
  return keyDowns_[code];
}

bool InputManager::IsMouseButtonDown( Mouse::Button button ) const
{
  return mouseButtonDowns_[button];
}

bool InputManager::GetKeyState( Key::Code code ) const
{
  return keyStates_[code];
}

bool InputManager::GetMouseButtonState( Mouse::Button button ) const
{
  return mouseButtonStates_[button];
}

bool InputManager::IsKeyReleased( Key::Code code ) const
{
  return keyReleases_[code];
}

bool InputManager::IsMouseButtonReleased( Mouse::Button button ) const
{
  return mouseButtonReleases_[button];
}

int InputManager::GetMouseX() const
{
  return mouseX_;
}

int InputManager::GetMouseY() const
{
  return mouseY_;
}

void InputManager::OnEvent( const Event& event )
{
  Key::Code keyCode = event.Key.Code;
  Mouse::Button mouseBtn = event.MouseButton.Button;

  switch (event.Type)
  {
    // Key events
  case Event::KeyPressed :  
    keyDowns_[keyCode] = (keyStates_[keyCode] == false);
    keyStates_[keyCode] = true;  
    break;
  case Event::KeyReleased : 
    keyReleases_[keyCode] = (keyStates_[keyCode] == true); 
    keyStates_[keyCode] = false; 
    break;

    // Mouse event
  case Event::MouseButtonPressed :  
    mouseButtonDowns_[mouseBtn] = (mouseButtonStates_[mouseBtn] == false);
    mouseButtonStates_[mouseBtn] = true;
    break;
  case Event::MouseButtonReleased : 
    mouseButtonReleases_[mouseBtn] = (mouseButtonStates_[mouseBtn] == true) ; 
    mouseButtonStates_[mouseBtn] = false; 
    break;

    // Mouse move event
  case Event::MouseMoved :
    mouseX_ = event.MouseMove.X;
    mouseY_ = event.MouseMove.Y;
    break;

    // Lost focus event : we must reset all persistent states
  case Event::LostFocus :
    {
      Reset();
      break;
    }
  }
}

void InputManager::EndUpdate()
{
  ResetDownInfos();
  ResetReleaseInfos();
}

void InputManager::Reset()
{
  ResetDownInfos();
  ResetStateInfos();
  ResetReleaseInfos();
}

void InputManager::ResetDownInfos()
{
  memset(keyDowns_, 0, sizeof(keyDowns_));
  memset(mouseButtonDowns_, 0, sizeof(mouseButtonDowns_));
}

void InputManager::ResetStateInfos()
{
  memset(keyStates_, 0, sizeof(keyStates_));
  memset(mouseButtonStates_, 0, sizeof(mouseButtonStates_));
}

void InputManager::ResetReleaseInfos()
{
  memset(keyReleases_, 0, sizeof(keyReleases_));
  memset(mouseButtonReleases_, 0, sizeof(mouseButtonReleases_));
}
