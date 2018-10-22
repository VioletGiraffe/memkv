#pragma once

#include <map>
#include <optional>
#include <vector>

template <typename KeyType, typename ValueType>
class MemKvStorage
{
public:
	using ContainerType = std::map<KeyType, ValueType>;

	using value_type = typename ContainerType::value_type;
	using key_type = KeyType;

	// Returns true if insertion took place, false if this key already existed and its value was reassigned.
	template <typename KeyCompatibleType, typename ValueCompatibleType>
	bool insert_or_assign(KeyCompatibleType&& key, ValueCompatibleType&& value);
	// Inserts the item if it didn't exist, otherwise does nothing. Returns true if insertion took place.
	template <typename KeyCompatibleType, typename ValueCompatibleType>
	bool try_insert(KeyCompatibleType&& key, ValueCompatibleType&& value);

	bool keyExists(const KeyType key) const;
	std::optional<ValueType> findByKey(const KeyType key);

	template <typename Comparator>
	std::optional<std::vector<std::pair<KeyType, ValueType>>> find_if(Comparator comp);

	void eraseKey(const KeyType key);
	template <typename Comparator>
	void erase_if(Comparator comp);

	bool empty() const;
	size_t size() const;

	// Dereferencing iterators is not thread-safe, handle with care!
	auto begin() const { return _storage.begin(); }
	auto end() const { return _storage.end(); }

private:
	ContainerType _storage;
};

template <typename KeyType, typename ValueType>
template <typename KeyCompatibleType, typename ValueCompatibleType>
bool MemKvStorage<KeyType, ValueType>::insert_or_assign(KeyCompatibleType&& key, ValueCompatibleType&& value)
{
	return _storage.insert_or_assign(std::forward<KeyCompatibleType>(key), std::forward<ValueCompatibleType>(value)).second;
}

template <typename KeyType, typename ValueType>
template <typename KeyCompatibleType, typename ValueCompatibleType>
bool MemKvStorage<KeyType, ValueType>::try_insert(KeyCompatibleType&& key, ValueCompatibleType&& value)
{
	return _storage.try_emplace(std::forward<KeyCompatibleType>(key), std::forward<ValueCompatibleType>(value)).second;
}


template <typename KeyType, typename ValueType>
bool MemKvStorage<KeyType, ValueType>::empty() const
{
	return _storage.empty();
}

template <typename KeyType, typename ValueType>
size_t MemKvStorage<KeyType, ValueType>::size() const
{
	return _storage.size();
}


template <typename KeyType, typename ValueType>
bool MemKvStorage<KeyType, ValueType>::keyExists(const KeyType key) const
{
	return _storage.count(key) > 0;
}


template<typename KeyType, typename ValueType>
std::optional<ValueType> MemKvStorage<KeyType, ValueType>::findByKey(const KeyType key)
{
	const auto item = _storage.find(key);
	if (item != _storage.end())
		return item->second;

	return {};
}

template <typename KeyType, typename ValueType>
template <typename Comparator>
std::optional<std::vector<std::pair<KeyType, ValueType>>>
MemKvStorage<KeyType, ValueType>::find_if(Comparator comp)
{
	std::vector<std::pair<KeyType, ValueType>> matchingItems;
	matchingItems.reserve(500);
	for (auto it = _storage.begin(); it != _storage.end(); ++it)
	{
		if (comp(*it))
			matchingItems.emplace_back(*it);
	}

	return matchingItems;
}

template<typename KeyType, typename ValueType>
void MemKvStorage<KeyType, ValueType>::eraseKey(const KeyType key)
{
	_storage.erase(key);
}

template <typename KeyType, typename ValueType>
template <typename Comparator>
void MemKvStorage<KeyType, ValueType>::erase_if(Comparator comp)
{
	for (auto it = _storage.begin(); it != _storage.end();)
	{
		if (comp(*it))
			it = _storage.erase(it);
		else
			++it;
	}
}