#pragma once

#include <algorithm>
#include <map>
#include <utility>

namespace util
{
  // 用 iterator 遍历容器
  #define UTIL_FOREACH(i, container, type) \
    for( type::iterator i = (container).begin(); i != (container).end(); ++i )

  // 用 const_iterator 遍历容器
  #define UTIL_CONST_FOREACH(i, container, type) \
    for( type::const_iterator i = (container).begin(); i != (container).end(); ++i )

  // 遍历容器各个元素，对各个元素调用 Functor::operator()
  template <class Container, class Functor>
  inline void Vist(Container& container, Functor& functor);

  // 判断容器是否存在某个 Key
  template <class Container, class Key>
  inline bool Contain(Container& container, Key& key);

  // 删除容器的某个键为 Key 的元素
  template <class Container, class Key>
  inline bool Remove(Container& container, Key& key);

  // 向容器插入一个新元素
  template <class Container, class ValueType>
  inline bool Insert(Container& container, ValueType& value);

  // TODO: 如何把两个 Get 合并？

  template <class Key, class Value>
  inline Value& Get(std::map<Key, Value>& container, const Key& key);

  template <class Key, class Value>
  inline Value& Get(std::multimap<Key, Value>& container, const Key& key);

  #include "container.inl"
}