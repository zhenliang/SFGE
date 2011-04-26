#include "util_string.h"

bool String_IsEmpty(const String& string)
{
  return (string.GetRect().GetWidth() == 0);
}

void String_AddStyle(String& string, String::Style style)
{
  string.SetStyle(string.GetStyle() | style);
}

void String_RemoveStyle(String& string, String::Style style)
{
  string.SetStyle(string.GetStyle() & ~style);
}