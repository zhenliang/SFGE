#pragma once

#include <map>

#include "i_get_instance.h"

namespace util
{
	template <class Key>
	class ItemCounter : public IGetInstance< ItemCounter<Key> >
	{
	public:
		typedef std::map<Key, int> Items;

		ItemCounter() {}
		virtual ~ItemCounter() {}

		int GetCount(const Key& key);
		void SetCount(const Key& key, int count);
		void ChangeCount(const Key& key, int change);

        const Items& GetItems() const { return items_; }

		void Reset();

	protected:
		Items items_;
	};

#include "item_counter.inl"
}