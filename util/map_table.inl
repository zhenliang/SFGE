
template <class Key, class Value>
bool MapTable<Key, Value>::AddItem( Key key, Value& value )
{
	return util::Insert(items_, std::make_pair(key, value));
}

template <class Key, class Value>
Value& MapTable<Key, Value>::GetItem( Key key )
{
	return util::Get(items_, key);
}
