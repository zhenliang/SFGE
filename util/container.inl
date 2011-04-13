
template <class Container, class Functor>
inline void Vist(Container& container, Functor& functor)
{
	std::for_each(container.begin(), container.end(), functor);
}

template <class Container, class Key>
inline bool Contain(Container& container, Key& key)
{
	return container.find(key) != container.end();
}

template <class Container, class Key>
inline bool Remove(Container& container, Key& key)
{
	if (Contain(container, key))
	{
		container.erase(key);
		return true;
	}

	return false;
}

template <class Container, class ValueType>
inline bool Insert(Container& container, ValueType& value)
{
	return container.insert(container.begin(), value) != container.end();
}

// TODO: 如何把两个 Get 合并？

template <class Key, class Value>
inline Value& Get(std::map<Key, Value>& container, const Key& key)
{
	static Value value;

	if (Contain(container, key))
		return container.find(key)->second;
	else
		assert(false);

	return value;
}

template <class Key, class Value>
inline Value& Get(std::multimap<Key, Value>& container, const Key& key)
{
	static Value value;

	if (Contain(container, key))
		return container.find(key)->second;
	else
		assert(false);

	return value;
}