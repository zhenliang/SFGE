
template <class Container, class Functor>
inline void Vist(Container& container, Functor& functor)
{
  std::for_each(container.begin(), container.end(), functor);
}

template <class Container>
inline bool Contain(Container& container, const typename Container::key_type& key)
{
  return container.find(key) != container.end();
}

template <class Container>
inline bool Remove(Container& container, const typename Container::key_type& key)
{
  if (Contain(container, key))
  {
    container.erase(key);
    return true;
  }

  return false;
}

template <class Container>
inline bool Insert(Container& container, const typename Container::value_type& value)
{
  return container.insert(container.begin(), value) != container.end();
}

template <class Container>
inline typename Container::mapped_type& Get(
  Container& container, const typename Container::key_type& key)
{
  static Container::mapped_type value;

  if (Contain(container, key))
    return container.find(key)->second;
  else
    assert(false);

  return value;
}

