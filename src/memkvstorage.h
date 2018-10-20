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

	typename ContainerType::iterator findByKey(const KeyType key) const;
	std::vector<typename ContainerType::iterator> findByValue(const ValueType value) const;

	iterator end() const;

private:
	ContainerType _storage;
};

template<typename KeyType, typename ValueType>
typename MemKvStorage<KeyType, ValueType>::iterator MemKvStorage<KeyType, ValueType>::findByKey(const KeyType key) const
{
	return _storage.find(key);
}

template<typename KeyType, typename ValueType>
std::vector<typename MemKvStorage<KeyType, ValueType>::iterator> MemKvStorage<KeyType, ValueType>::findByValue(const ValueType value) const
{
	std::vector<iterator> iteratorsToMatches;
	for (const auto it = _storage.begin(); it != _storage.end(); ++it)
	{
		if (it->second == value)
			iteratorsToMatches.emplace_back(it);
	}

	return iteratorsToMatches;
}

template<typename KeyType, typename ValueType>
typename MemKvStorage<KeyType, ValueType>::iterator MemKvStorage<KeyType, ValueType>::end() const
{
	return _storage.end();
}
