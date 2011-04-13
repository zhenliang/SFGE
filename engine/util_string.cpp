#include "util_string.h"

bool ENGINE_API String_IsEmpty( const String& string )
{
	return (string.GetRect().GetWidth() == 0);
}

void ENGINE_API String_AddStyle( String& string, String::Style style )
{
	string.SetStyle(string.GetStyle() | style);
}

void ENGINE_API String_RemoveStyle( String& string, String::Style style )
{
	string.SetStyle(string.GetStyle() & ~style);
}