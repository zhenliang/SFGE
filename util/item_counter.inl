
template <class Key>
int ItemCounter<Key>::GetCount( const Key& key )
{
  return items_[key];
}

template <class Key>
void ItemCounter<Key>::SetCount( const Key& key, int count )
{
  items_[key] = count;
}

template <class Key>
void ItemCounter<Key>::ChangeCount( const Key& key, int change )
{
  items_[key] += change;
}

template <class Key>
void ItemCounter<Key>::Reset()
{
  items_.clear();
}