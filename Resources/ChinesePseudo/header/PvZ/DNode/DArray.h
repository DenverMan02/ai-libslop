//
//  DArray.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DArray_h
#define DArray_h

#include "DRef.h"
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <initializer_list>

template <typename T>
class DArray
{
public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    typedef typename std::vector<T>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
    
    iterator begin() { return m_data.begin(); }
    
    const_iterator begin() const { return m_data.begin(); }

    iterator end() { return m_data.end(); }

    const_iterator end() const { return m_data.end(); }
    
    const_iterator cbegin() const { return m_data.cbegin(); }
    
    const_iterator cend() const { return m_data.cend(); }
    
    reverse_iterator rbegin() { return m_data.rbegin(); }
    
    const_reverse_iterator rbegin() const { return m_data.rbegin(); }
    
    reverse_iterator rend() { return m_data.rend(); }

    const_reverse_iterator rend() const { return m_data.rend(); }
    
    const_reverse_iterator crbegin() const { return m_data.crbegin(); }

    const_reverse_iterator crend() const { return m_data.crend(); }
    
    DArray<T>()
    : m_data()
    {
        static_assert(std::is_convertible<T, DRef*>::value, "Invalid Type for DArray<T>!");
    }
    
    explicit DArray<T>(std::initializer_list<T> _l)
    : m_data(_l)
    {
    
    }
    
    explicit DArray<T>(ssize_t capacity)
    : m_data()
    {
        static_assert(std::is_convertible<T, DRef*>::value, "Invalid Type for DArray<T>!");
        reserve(capacity);
    }
    
    ~DArray<T>()
    {
        clear();
    }
    
    DArray<T>(const DArray<T>& other)
    {
        static_assert(std::is_convertible<T, DRef*>::value, "Invalid Type for DArray<T>!");
        m_data = other.m_data;
        addRefForAllObjects();
    }
    
    DArray<T>(DArray<T>&& other)
    {
        static_assert(std::is_convertible<T, DRef*>::value, "Invalid Type for DArray<T>!");
        m_data = std::move(other.m_data);
    }
    
    DArray<T>& operator=(const DArray<T>& other)
    {
        if (this != &other)
        {
            clear();
            m_data = other.m_data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    DArray<T>& operator=(DArray<T>&& other)
    {
        if (this != &other)
        {
            clear();
            m_data = std::move(other.m_data);
        }
        return *this;
    }
    
    void reserve(ssize_t n)
    {
        m_data.reserve(n);
    }
    
    ssize_t capacity() const
    {
        return m_data.capacity();
    }
    
    ssize_t size() const
    {
        return  m_data.size();
    }
    
    bool empty() const
    {
        return m_data.empty();
    }
    
    ssize_t max_size() const
    {
        return m_data.max_size();
    }
    
    ssize_t getIndex(T object) const
    {
        auto iter = std::find(m_data.begin(), m_data.end(), object);
        if (iter != m_data.end())
            return iter - m_data.begin();
        
        return -1;
    }
    
    const_iterator find(T object) const
    {
        return std::find(m_data.begin(), m_data.end(), object);
    }
    
    iterator find(T object)
    {
        return std::find(m_data.begin(), m_data.end(), object);
    }
    
    T at(ssize_t index) const
    {
        return m_data[index];
    }
    
    T front() const
    {
        return m_data.front();
    }
    
    T back() const
    {
        return m_data.back();
    }
    
    T getRandomObject() const
    {
        if (!m_data.empty())
        {
            ssize_t randIdx = rand() % m_data.size();
            return *(m_data.begin() + randIdx);
        }
        return nullptr;
    }
    
    bool contains(T object) const
    {
        return( std::find(m_data.begin(), m_data.end(), object) != m_data.end() );
    }
    
    bool equals(const DArray<T> &other)
    {
        ssize_t s = this->size();
        if (s != other.size())
            return false;
        
        for (ssize_t i = 0; i < s; i++)
        {
            if (this->at(i) != other.at(i))
            {
                return false;
            }
        }
        return true;
    }
    
    void pushBack(T object)
    {
        m_data.push_back( object );
        object->ref();
    }
    

    void pushBack(const DArray<T>& other)
    {
        for(const auto &obj : other) {
            m_data.push_back(obj);
            obj->ref();
        }
    }
    
    
    void insert(ssize_t index, T object)
    {
        m_data.insert((std::begin(m_data) + index), object);
        object->ref();
    }
    
    
    void popBack()
    {
        auto last = m_data.back();
        m_data.pop_back();
        last->unref();
    }
    
   
    void eraseObject(T object, bool removeAll = false)
    {
        if (removeAll)
        {
            for (auto iter = m_data.begin(); iter != m_data.end();)
            {
                if ((*iter) == object)
                {
                    iter = m_data.erase(iter);
                    object->unref();
                }
                else
                {
                    ++iter;
                }
            }
        }
        else
        {
            auto iter = std::find(m_data.begin(), m_data.end(), object);
            if (iter != m_data.end())
            {
                m_data.erase(iter);
                object->unref();
            }
        }
    }
    
    
    iterator erase(iterator position)
    {
        (*position)->unref();
        return m_data.erase(position);
    }
    
    iterator erase(iterator first, iterator last)
    {
        for (auto iter = first; iter != last; ++iter)
        {
            (*iter)->unref();
        }
        
        return m_data.erase(first, last);
    }
    

    iterator erase(ssize_t index)
    {
        auto it = std::next( begin(), index );
        (*it)->unref();
        return m_data.erase(it);
    }
    
    
    void clear()
    {
        for( auto it = std::begin(m_data); it != std::end(m_data); ++it ) {
            (*it)->unref();
        }
        m_data.clear();
    }
    
    void swap(T object1, T object2)
    {
        ssize_t idx1 = getIndex(object1);
        ssize_t idx2 = getIndex(object2);
        
        
        std::swap( m_data[idx1], m_data[idx2] );
    }
    
    void swap(ssize_t index1, ssize_t index2)
    {
        std::swap( m_data[index1], m_data[index2] );
    }
    
    
    void replace(ssize_t index, T object)
    {
        m_data[index]->unref();
        m_data[index] = object;
        object->ref();
    }
    
    void reverse()
    {
        std::reverse( std::begin(m_data), std::end(m_data) );
    }
    
    void shuffle()
    {
    	std::random_shuffle(m_data.begin(), m_data.end());
    }

    void shrinkToFit()
    {
        m_data.shrink_to_fit();
    }
    
protected:
    void addRefForAllObjects()
    {
        for(const auto &obj : m_data) {
            obj->ref();
        }
    }
    std::vector<T> m_data;
};

#endif
