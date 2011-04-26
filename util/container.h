#pragma once

#include <algorithm>
#include <map>
#include <utility>

namespace util
{
  #define UTIL_FOREACH(i, container, type) \
    for( type::iterator i = (container).begin(); i != (container).end(); ++i )

  #define UTIL_CONST_FOREACH(i, container, type) \
    for( type::const_iterator i = (container).begin(); i != (container).end(); ++i )

  template <class Container, class Functor>
  inline void Vist(Container& container, Functor& functor);

  template <class Container, class Key>
  inline bool Contain(Container& container, Key& key);

  template <class Container, class Key>
  inline bool Remove(Container& container, Key& key);

  template <class Container, class ValueType>
  inline bool Insert(Container& container, ValueType& value);

  // TODO: 如何把两个 Get 合并？

  template <class Key, class Value>
  inline Value& Get(std::map<Key, Value>& container, const Key& key);

  template <class Key, class Value>
  inline Value& Get(std::multimap<Key, Value>& container, const Key& key);

  #include "container.inl"
}