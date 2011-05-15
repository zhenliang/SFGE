
template <class Key, class Value>
bool MapTable<Key, Value>::AddItem(const Key& key, const Value& value)
{
  return util::Insert(items_, std::make_pair<Key, Value>(key, value));
}

template <class Key, class Value>
Value& MapTable<Key, Value>::GetItem(const Key& key)
{
  return util::Get(items_, key);
}
