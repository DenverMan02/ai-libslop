//
//  DRef.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DRef_h
#define DRef_h

#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "DInclude.h"


class DRef
{
public:
    DRef();
    virtual ~DRef();
    void ref();
    void unref();
    
protected:
    unsigned int m_refCount;
};

class DRefAutoLock
{
public:
    DRefAutoLock(DRef *p)
    :_ref(p)
    {
        if(_ref)
        {
            _ref->ref();
        }
    }
    ~DRefAutoLock()
    {
        if(_ref)
        {
            _ref->unref();
        }
    }
private:
    DRef * _ref = nullptr;
};

template<typename T>
class DRefPtr
{
public:
    inline DRefPtr(T** otherPtr)
    {
        static_assert(std::is_convertible<T, DRef>::value, "Invalid Type for DRefPtr<T>!");
        
        _ptr = new T();
        
        if(*otherPtr != nullptr)
        {
            (*otherPtr)->unref();
        }
        *otherPtr = _ptr;
        
        (*otherPtr)->ref();
    }
    
    inline DRefPtr(T * ptr)
    :
    _ptr(const_cast<typename std::remove_const<T>::type*>(ptr))
    {
        if(_ptr)
        {
            _ptr->ref();
        }
    }
    
    inline DRefPtr(DRefPtr<T> && other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }
    
    inline DRefPtr(std::nullptr_t other)
    {
        _ptr = other;
    }
    
    inline DRefPtr()
    {
        static_assert(std::is_convertible<T, DRef>::value, "Invalid Type for DRefPtr<T>!");
        
        _ptr = new T();
    }
    
    inline ~DRefPtr()
    {
        if(_ptr)
        {
            _ptr->unref();
            _ptr = nullptr;
        }
    }
    
    inline DRefPtr(const DRefPtr<T> & other)
    :_ptr(other._ptr)
    {
        if(_ptr)
        {
            _ptr->ref();
        }
    }
    
    inline DRefPtr<T> & operator = (const DRefPtr<T> & other)
    {
        if (other._ptr != _ptr)
        {
            if(other._ptr)
            {
                other._ptr->ref();
            }
            if(_ptr)
            {
                _ptr->unref();
            }
            _ptr = other._ptr;
        }
        
        return *this;
    }
    
    inline DRefPtr<T> & operator = (DRefPtr<T> && other)
    {
        if (&other != this)
        {
            if(_ptr)
            {
                _ptr->unref();
            }
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        
        return *this;
    }
    
    inline DRefPtr<T> & operator = (T * other)
    {
        if (other != _ptr)
        {
            if(other)
            {
                other->ref();
            }
            if(_ptr)
            {
                _ptr->unref();
            }
            _ptr = const_cast<typename std::remove_const<T>::type*>(other);
        }
        
        return *this;
    }
    
    inline DRefPtr<T> & operator = (std::nullptr_t other)
    {
        if(_ptr)
        {
            _ptr->unref();
            _ptr = nullptr;
        }
        return *this;
    }
    
    inline void swap(DRefPtr<T> & other)
    {
        if (&other != this)
        {
            auto tmp = _ptr;
            _ptr = other._ptr;
            other._ptr = tmp;
        }
    }
    
    inline operator T * () const { return reinterpret_cast<T*>(_ptr); }
    
    inline T & operator * () const
    {
        return reinterpret_cast<T&>(*_ptr);
    }
    
    inline T * operator->() const
    {
        return reinterpret_cast<T*>(_ptr);
    }
    
    inline T * get() const { return reinterpret_cast<T*>(_ptr); }
    
    inline operator bool() const { return _ptr != nullptr; }
    
    inline bool operator == (const DRefPtr<T> & other) const { return _ptr == other._ptr; }
    
    inline bool operator == (const T * other) const { return _ptr == other; }
    
    inline bool operator == (typename std::remove_const<T>::type * other) const { return _ptr == other; }
    
    inline bool operator == (const std::nullptr_t other) const { return _ptr == other; }
    
    
    inline bool operator != (const DRefPtr<T> & other) const { return _ptr != other._ptr; }
    
    inline bool operator != (const T * other) const { return _ptr != other; }
    
    inline bool operator != (typename std::remove_const<T>::type * other) const { return _ptr != other; }
    
    inline bool operator != (const std::nullptr_t other) const { return _ptr != other; }
    
    
    inline bool operator > (const DRefPtr<T> & other) const { return _ptr > other._ptr; }
    
    inline bool operator > (const T * other) const { return _ptr > other; }
    
    inline bool operator > (typename std::remove_const<T>::type * other) const { return _ptr > other; }
    
    inline bool operator > (const std::nullptr_t other) const { return _ptr > other; }
    
    
    inline bool operator < (const DRefPtr<T> & other) const { return _ptr < other._ptr; }
    
    inline bool operator < (const T * other) const { return _ptr < other; }
    
    inline bool operator < (typename std::remove_const<T>::type * other) const { return _ptr < other; }
    
    inline bool operator < (const std::nullptr_t other) const { return _ptr < other; }
    
    
    inline bool operator >= (const DRefPtr<T> & other) const { return _ptr >= other._ptr; }
    
    inline bool operator >= (const T * other) const { return _ptr >= other; }
    
    inline bool operator >= (typename std::remove_const<T>::type * other) const { return _ptr >= other; }
    
    inline bool operator >= (const std::nullptr_t other) const { return _ptr >= other; }
    
    
    inline bool operator <= (const DRefPtr<T> & other) const { return _ptr <= other._ptr; }
    
    inline bool operator <= (const T * other) const { return _ptr <= other; }
    
    inline bool operator <= (typename std::remove_const<T>::type * other) const { return _ptr <= other; }
    
    inline bool operator <= (const std::nullptr_t other) const { return _ptr <= other; }
    
    inline void reset()
    {
        if(_ptr)
        {
            _ptr->unref();
            _ptr = nullptr;
        }
    }
    
    inline void weakAssign(const DRefPtr<T> & other)
    {
        if(_ptr)
        {
            _ptr->unref();
        }
        _ptr = other._ptr;
    }
    
private:
    T*   _ptr = nullptr;
};

template<class T, class U> DRefPtr<T> static_pointer_cast(const DRefPtr<U> & r)
{
    return DRefPtr<T>(static_cast<T*>(r.get()));
}

template<class T, class U> DRefPtr<T> dynamic_pointer_cast(const DRefPtr<U> & r)
{
    return DRefPtr<T>(DYNAMIC_CAST<T*>(r.get()));
}

#endif
