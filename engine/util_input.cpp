#include "util_input.h"

bool IsKeyReleased( const Event& event, Key::Code keyCode )
{
	return (event.Type == Event::KeyReleased && event.Key.Code == keyCode);
}