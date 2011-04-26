#pragma once

#include "engine.h"

ENGINE_API bool String_IsEmpty(const String& string);
ENGINE_API void String_AddStyle(String& string, String::Style style);
ENGINE_API void String_RemoveStyle(String& string, String::Style style);