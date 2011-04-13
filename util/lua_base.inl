

int ToPositiveIndex( lua_State* L, int index )
{
	assert(index != 0);
	return index > 0 ? index : lua_gettop(L) - (-index)+ 1;
}