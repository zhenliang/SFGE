#pragma once

#include "engine.h"

bool ENGINE_API String_IsEmpty(const String& string);
void ENGINE_API String_AddStyle(String& string, String::Style style);
void ENGINE_API String_RemoveStyle(String& string, String::Style style);