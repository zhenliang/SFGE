#include "input_mgr.h"
#include <iostream>

InputManager::InputManager() 
: mouseX_()
, mouseY_()
{
	Reset();
}

bool InputManager::IsKeyDown( Key::Code keyCode ) const
{
	return keyDowns_[keyCode];
}

bool InputManager::IsMouseButtonDown( Mouse::Button button ) const
{
	return mouseButtonDowns_[button];
}

bool InputManager::GetKeyState( Key::Code keyCode ) const
{
	return keyStates_[keyCode];
}

bool InputManager::GetMouseButtonState( Mouse::Button button ) const
{
	return mouseButtonStates_[button];
}

bool InputManager::IsKeyReleased( Key::Code keyCode ) const
{
	return keyReleases_[keyCode];
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

void InputManager::OnEvent( const Event& eventReceived )
{
	Key::Code keyCode = eventReceived.Key.Code;
	Mouse::Button button = eventReceived.MouseButton.Button;

	switch (eventReceived.Type)
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
		mouseButtonDowns_[button] = (mouseButtonStates_[button] == false);
		mouseButtonStates_[button] = true;
		break;
	case Event::MouseButtonReleased : 
		mouseButtonReleases_[button] = (mouseButtonStates_[button] == true) ; 
		mouseButtonStates_[button] = false; 
		break;

		// Mouse move event
	case Event::MouseMoved :
		mouseX_ = eventReceived.MouseMove.X;
		mouseY_ = eventReceived.MouseMove.Y;
		break;

		// Lost focus event : we must reset all persistent states
	case Event::LostFocus :
		{
			Reset();
			break;
		}

	default :
		break;
	}
}

void InputManager::Reset()
{
	ResetDowns();
	ResetStates();
	ResetReleases();
}

void InputManager::ResetStates()
{
	for (int i = 0; i < Key::Count; ++i)
		keyStates_[i] = false;

	for (int i = 0; i < Mouse::ButtonCount; ++i)
		mouseButtonStates_[i] = false;
}

void InputManager::ResetDowns()
{
	for (int i = 0; i < Key::Count; ++i)
		keyDowns_[i] = false;

	for (int i = 0; i < Mouse::ButtonCount; ++i)
		mouseButtonDowns_[i] = false;
}

void InputManager::ResetReleases()
{
	for (int i = 0; i < Key::Count; ++i)
		keyReleases_[i] = false;

	for (int i = 0; i < Mouse::ButtonCount; ++i)
		mouseButtonReleases_[i] = false;
}

void InputManager::EndUpdate()
{
	ResetDowns();
	ResetReleases();
}
