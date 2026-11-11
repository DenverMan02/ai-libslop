//
//  DMap.h
//  DCore
//
//  Created by lzjseed on 16/10/13.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DMap_h
#define DMap_h

#include "DInclude.h"
#include "DRef.h"
#include <vector>

#if USE_STD_UNORDERED_MAP
#include <unordered_map>
#else
#include <map>
#endif

using namespace Sexy;

template <class K, class V>
class DMap
{
public: 
#if USE_STD_UNORDERED_MAP
    typedef std::unordered_map<K, V> DRefMap;
#else
    typedef std::map<K, V> DRefMap;
#endif
    
    
    typedef typename DRefMap::iterator iterator;
    
    typedef typename DRefMap::const_iterator const_iterator;
    
    
    iterator begin() { return _data.begin(); }
    
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    
    const_iterator end() const { return _data.end(); }
    
    
    const_iterator cbegin() const { return _data.cbegin(); }
    
    const_iterator cend() const { return _data.cend(); }
    
    DMap<K, V>()
    : _data()
    {
        static_assert(std::is_convertible<V, DRef*>::value, "Invalid Type for DMap<K, V>!");
        DLOG("In the default constructor of DMap!");
    }
    
    explicit DMap<K, V>(ssize_t capacity)
    : _data()
    {
        static_assert(std::is_convertible<V, DRef*>::value, "Invalid Type for DMap<K, V>!");
        DLOG("In the constructor with capacity of DMap!");
        _data.reserve(capacity);
    }
    
    DMap<K, V>(const DMap<K, V>& other)
    {
        static_assert(std::is_convertible<V, DRef*>::value, "Invalid Type for DMap<K, V>!");
        DLOG("In the copy constructor of DMap!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    DMap<K, V>(DMap<K, V>&& other)
    {
        static_assert(std::is_convertible<V, DRef*>::value, "Invalid Type for DMap<K, V>!");
        DLOG("In the move constructor of DMap!");
        _data = std::move(other._data);
    }

    ~DMap<K, V>()
    {
        DLOG("In the destructor of DMap!");
        clear();
    }
    
    void reserve(ssize_t capacity)
    {
#if USE_STD_UNORDERED_MAP
        _data.reserve(capacity);
#endif
    }
    
    ssize_t bucketCount() const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_count();
#else
        return 0;
#endif
    }
    
    ssize_t bucketSize(ssize_t n) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_size(n);
#else
        return 0;
#endif
    }
    
    ssize_t bucket(const K& k) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket(k);
#else
        return 0;
#endif
    }
    
    ssize_t size() const
    {
        return _data.size();
    }
    
    bool empty() const
    {
        return _data.empty();
    }
    
    std::vector<K> keys() const
    {
        std::vector<K> keys;

        if (!_data.empty())
        {
            keys.reserve(_data.size());
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                keys.push_back(iter->first);
            }
        }
        return keys;
    }
    
    std::vector<K> keys(V object) const
    {
        std::vector<K> keys;
        
        if (!_data.empty())
        {
            keys.reserve(_data.size() / 10);
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                if (iter->second == object)
                {
                    keys.push_back(iter->first);
                }
            }
        }
        
        keys.shrink_to_fit();
        
        return keys;
    }
    
    const V at(const K& key) const
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return nullptr;
    }
    
    V at(const K& key)
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return nullptr;
    }
    
    const_iterator find(const K& key) const
    {
        return _data.find(key);
    }
    
    iterator find(const K& key)
    {
        return _data.find(key);
    }
    
    void insert(const K& key, V object)
    {
        DASSERT(object != nullptr, "Object is nullptr!");
        object->ref();
        erase(key);
        _data.insert(std::make_pair(key, object));
    }
    
    iterator erase(const_iterator position)
    {
        DASSERT(position != _data.cend(), "Invalid iterator!");
        position->second->unref();
        return _data.erase(position);
    }
    
    size_t erase(const K& k)
    {
        auto iter = _data.find(k);
        if (iter != _data.end())
        {
            iter->second->unref();
            _data.erase(iter);
            return 1;
        }
        return 0;
    }
    
    void erase(const std::vector<K>& keys)
    {
        for(const auto &key : keys) {
            this->erase(key);
        }
    }
    
    void clear()
    {
        for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
        {
            iter->second->unref();
        }
        
        _data.clear();
    }
    
    V getRandomObject() const
    {
        if (!_data.empty())
        {
            ssize_t randIdx = rand() % _data.size();
            const_iterator randIter = _data.begin();
            std::advance(randIter , randIdx);
            return randIter->second;
        }
        return nullptr;
    }
    
    V& operator[] ( const K& key )
    {
        DLOG("copy: [] ref");
        return _data[key];
    }
    
    V& operator[] ( K&& key )
    {
        DLOG("move [] ref");
        return _data[key];
    }
    
    const V& operator[] ( const K& key ) const
    {
        DLOG("const copy []");
        return _data.at(key);
    }
    
    const V& operator[] ( K&& key ) const
    {
        DLOG("const move []");
        return _data.at(key);
    }
    
    DMap<K, V>& operator= ( const DMap<K, V>& other )
    {
        if (this != &other) {
            DLOG("In the copy assignment operator of DMap!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    DMap<K, V>& operator= ( DMap<K, V>&& other )
    {
        if (this != &other) {
            DLOG("In the move assignment operator of DMap!");
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
protected:
    
    void addRefForAllObjects()
    {
        for (auto iter = _data.begin(); iter != _data.end(); ++iter)
        {
            iter->second->ref();
        }
    }
    
    DRefMap _data;
};

#endif
