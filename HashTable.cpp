#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>
#include "HashTable.h"


HashTable::HashTable(size_t size) noexcept
    : _capacity(size)
    , _filled(0)
{
    table.resize(_capacity);
}

//! Хеш-функция, используемая для расчета индекса в хеш-таблице
//! Она просто берет хеш-код строки key (который рассчитан с помощью
//! std::hash<std::string>) и делит его на _capacity
//! чтобы получить индекс в хеш-таблице
size_t HashTable::hash_function(const KeyType &key) const {
    std::hash<std::string> hash_fn;
    return hash_fn(key) % _capacity;
}
HashTable::~HashTable() = default;

void HashTable::insert(const KeyType &key, const ValueType &value)
{
    if (_filled > _capacity * 0.75) {
        std::cout << "Resizing..." << std::endl;
        resize();
    }

    const size_t index = hash_function(key);
    auto& bucket = table[index];
    auto it = std::find_if(bucket.begin(), bucket.end(),
        [&](const auto& pair) { return pair.first == key; });
    if (it != bucket.end()) {
        it->second = value;
    }
    else {
        bucket.emplace_back(key, value);
        ++_filled;
    }
}



bool HashTable::find(const KeyType &key, ValueType &value) const
{
    const size_t index = hash_function(key);
    auto& bucket = table[index];
    auto it = std::find_if(bucket.begin(), bucket.end(),
        [&](const auto& pair) { return pair.first == key; });

    if (it != bucket.end()) {
        value = it->second;
        return true;
    }

    return false;
}

void HashTable::remove(const KeyType &key)
{
    const size_t index = hash_function(key);
    auto& bucket = table[index];

    auto it = std::find_if(bucket.begin(), bucket.end(),
        [&](const auto& pair) { return pair.first == key; });

    if (it != bucket.end()) {
        bucket.erase(it);
        _filled -= 1;
    }

    if (_filled <= _capacity * 0.25) {
        resize();
    }
}
ValueType& HashTable::operator[](const KeyType &key)
{
    const size_t index = hash_function(key);
    auto& bucket = table[index];

    // std::cout << "-------------------------------------" << std::endl;

    // std::cout << "Index: " << index << std::endl;
    // std::cout << "Key: " << key << std::endl;
    // for (const auto& bucket : table) {
    //         for (const auto& pair : bucket) {
    //             std::cout << pair.first << ": " << pair.second << std::endl;
    //         }
    // }
    for (auto& pair : bucket) {
        // std::cout << "Key: " << pair.first << " Value: " << pair.second << std::endl;
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    
    throw std::out_of_range("Key not found");
    

    
}

double HashTable::getLoadFactor()
{
    return static_cast<double>(_filled) / _capacity;
}

void HashTable::resize()
{
    _capacity = _capacity * 2;
    std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(_capacity);

    for (auto& bucket : table) {
        for (auto& pair : bucket) {
            const size_t newIndex = hash_function(pair.first);
            newTable[newIndex].emplace_back(pair.first, pair.second);
        }
    }

    table.swap(newTable);
}
