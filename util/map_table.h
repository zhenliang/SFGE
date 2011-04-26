#pragma once

#include <util\container.h>
#include <util\i_get_instance.h>

namespace util
{
  template <class Key, class Value>
  class MapTable : public IGetInstance< MapTable<Key, Value> >
  {
  public:
    MapTable() {}
    virtual ~MapTable() {}

    bool AddItem(Key key, Value& value);
    Value& GetItem(Key key);

  protected:
    typedef std::map<Key, Value> Items;
    Items items_;
  };

  #include "map_table.inl"
}
