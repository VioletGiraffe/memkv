#pragma once

#include <map>
#include <vector>

template <typename KeyType, typename ValueType>
class MemKvStorage
{
public:
	using ContainerType = std::map<KeyType, ValueType>;

	using value_type = typename ContainerType::value_type;
	using key_type = KeyType;
	using iterator = typename ContainerType::iterator;
	using const_iterator = typename ContainerType::const_iterator;

	iterator insert(const KeyType key, const ValueType value);

	typename ContainerType::iterator findByKey(const KeyType key);

	template <typename Comparator>
	std::vector<typename ContainerType::iterator> find_if(Comparator comp);

	const_iterator begin() const;
	iterator begin();

	const_iterator end() const;
	iterator end();

	bool empty() const;
	size_t size() const;

private:
	ContainerType _storage;
};

template <typename KeyType, typename ValueType>
typename MemKvStorage<KeyType, ValueType>::iterator MemKvStorage<KeyType, ValueType>::begin()
{
	return _storage.begin();
}

template <typename KeyType, typename ValueType>
typename MemKvStorage<KeyType, ValueType>::const_iterator MemKvStorage<KeyType, ValueType>::begin() const
{
	return _storage.begin();
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
typename MemKvStorage<KeyType, ValueType>::iterator MemKvStorage<KeyType, ValueType>::insert(const KeyType key, const ValueType value)
{
	return _storage.insert(std::make_pair(key, value)).first;
}

template<typename KeyType, typename ValueType>
typename MemKvStorage<KeyType, ValueType>::iterator MemKvStorage<KeyType, ValueType>::findByKey(const KeyType key)
{
	return _storage.find(key);
}

template <typename KeyType, typename ValueType>
template <typename Comparator>
std::vector<typename MemKvStorage<KeyType, ValueType>::ContainerType::iterator>
MemKvStorage<KeyType, ValueType>::find_if(Comparator comp)
{
	std::vector<iterator> iteratorsToMatches;
	for (auto it = _storage.begin(); it != _storage.end(); ++it)
	{
		if (comp(*it))
			iteratorsToMatches.emplace_back(it);
	}

	return iteratorsToMatches;
}

template<typename KeyType, typename ValueType>
typename MemKvStorage<KeyType, ValueType>::const_iterator MemKvStorage<KeyType, ValueType>::end() const
{
	return _storage.cend();
}

template<typename KeyType, typename ValueType>
typename MemKvStorage<KeyType, ValueType>::iterator MemKvStorage<KeyType, ValueType>::end()
{
	return _storage.end();
}
