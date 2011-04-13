#include "util_drawable.h"

void SetAlpha( Drawable& obj, float alpha )
{
	const_cast<Color&>(obj.GetColor()).a = alpha;
}
