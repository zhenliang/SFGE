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

  // 容器约定：
  // 元素的类型为 Container::value_type
  // 元素键值的类型为 Container::key_type ，即 Container::value_type::first_type
  // 元素映射值的类型为 Container::mapped_type ，即 Container::value_type::second_type

  // 遍历容器各个元素，对各个元素调用 Functor::operator()
  template <class Container, class Functor>
  inline void Vist(Container& container, Functor& functor);

  // 判断容器是否存在一个以 key 为键值的元素
  template <class Container>
  inline bool Contain(Container& container, const typename Container::key_type& key);

  // 删除容器的键值为 key 的元素
  template <class Container>
  inline bool Remove(Container& container, const typename Container::key_type& key);

  // 向容器插入一个新元素
  template <class Container>
  inline bool Insert(Container& container, const typename Container::value_type& value);

  // 获取第一个以 key 为键值的元素的映射值
  template <class Container>
  inline typename Container::mapped_type& Get(
    Container& container, const typename Container::key_type& key);

  #include "container.inl"
}