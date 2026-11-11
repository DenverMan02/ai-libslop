/////////////////////////////////////////////////////////////////////////////
// eathread_atomic_psp2.h
//
// Copyright (c) Electronic Arts Inc. All rights reserved.
//
// Defines functionality for threadsafe primitive operations.
/////////////////////////////////////////////////////////////////////////////

#ifndef EATHREAD_ATOMIC_PSP2_H
#define EATHREAD_ATOMIC_PSP2_H

#define EA_THREAD_ATOMIC_IMPLEMENTED

#include <EABase/eabase.h>
#include <stddef.h>
#include <sce_atomic.h>

namespace EA
{
    namespace Thread
    {

        /// class AtomicInt
        /// Actual implementation may vary per platform. May require certain alignments, sizes, 
        /// and declaration specifications per platform.

        template <class T>
        class AtomicInt
        {
        public:
            typedef AtomicInt<T> ThisType;
            typedef T            ValueType;

            /// AtomicInt
            /// Empty constructor. Intentionally leaves mValue in an unspecified state.
            /// This is done so that an AtomicInt acts like a standard built-in integer.
            AtomicInt()
                {}

            AtomicInt(ValueType n) 
                { SetValue(n); }

            AtomicInt(const ThisType& x)
                : mValue(x.GetValue()) {}

            AtomicInt& operator=(const ThisType& x)
                { mValue = x.GetValue(); return *this; }

            ValueType GetValue() const
                { return mValue; }

            ValueType GetValueRaw() const
                { return mValue; }

            ValueType SetValue(ValueType n);
            bool      SetValueConditional(ValueType n, ValueType condition);
            ValueType Increment();
            ValueType Decrement();
            ValueType Add(ValueType n);

            // operators
            inline            operator const ValueType() const { return mValue; }
            inline ValueType  operator =(ValueType n)          {        SetValue(n); return n; }
            inline ValueType  operator+=(ValueType n)          { return Add(n);}
            inline ValueType  operator-=(ValueType n)          { return Add(-n);}
            inline ValueType  operator++()                     { return Increment();}
            inline ValueType  operator++(int)                  { return Increment() - 1;}
            inline ValueType  operator--()                     { return Decrement(); }
            inline ValueType  operator--(int)                  { return Decrement() + 1;}

        protected:
            volatile ValueType mValue;
        };

        /// Note: All Vita kernel intrinsics return the *old* value

        /// int32_t Implementation

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::GetValue() const
        {
            return sceAtomicAdd32(const_cast<ValueType*>(&mValue), 0);
        }

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::SetValue(ValueType n)
        {
            return sceAtomicExchange32(&mValue, n);
        }

        template <> inline
        bool AtomicInt<int32_t>::SetValueConditional(ValueType n, ValueType condition)
        {
            return sceAtomicCompareAndSwap32(&mValue, condition, n) == condition;
        }

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Increment()
        {
            return sceAtomicIncrement32(&mValue) + 1;
        }

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Decrement()
        {
            return sceAtomicDecrement32(&mValue) - 1;
        }

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Add(ValueType n)
        {
            return sceAtomicAdd32(&mValue, n) + n;
        }

        /// uint32_t Implementation

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::GetValue() const
        {
            return sceAtomicAdd32(reinterpret_cast<volatile int32_t*>(const_cast<ValueType*>(&mValue)), 0);
        }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::SetValue(ValueType n)
        {
            return sceAtomicExchange32(reinterpret_cast<volatile int32_t*>(&mValue), n);
        }

        template <> inline
        bool AtomicInt<uint32_t>::SetValueConditional(ValueType n, ValueType condition)
        {
            return sceAtomicCompareAndSwap32(reinterpret_cast<volatile int32_t*>(&mValue), condition, n) == condition;
        }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Increment()
        {
            return sceAtomicIncrement32(reinterpret_cast<volatile int32_t*>(&mValue)) + 1;
        }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Decrement()
        {
            return sceAtomicDecrement32(reinterpret_cast<volatile int32_t*>(&mValue)) - 1;
        }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Add(ValueType n)
        {
            return sceAtomicAdd32(reinterpret_cast<volatile int32_t*>(&mValue), n) + n;
        }

        /// int64_t Implementation

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::GetValue() const
        {
            return sceAtomicAdd64(const_cast<ValueType*>(&mValue), 0);
        }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::SetValue(ValueType n)
        {
            return sceAtomicExchange64(&mValue, n);
        }

        template <> inline
        bool AtomicInt<int64_t>::SetValueConditional(ValueType n, ValueType condition)
        {
            return sceAtomicCompareAndSwap64(&mValue, condition, n) == condition;
        }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::Increment()
        {
            return sceAtomicIncrement64(&mValue) + 1;
        }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::Decrement()
        {
            return sceAtomicDecrement64(&mValue) - 1;
        }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::Add(ValueType n)
        {
            return sceAtomicAdd64(&mValue, n) + n;
        }
        
        /// uint64_t Implementation
        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::GetValue() const
        {
            return sceAtomicAdd64(reinterpret_cast<volatile int64_t*>(const_cast<ValueType*>(&mValue)), 0);
        }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::SetValue(ValueType n)
        {
            return sceAtomicExchange64(reinterpret_cast<volatile int64_t*>(&mValue), n);
        }

        template <> inline
        bool AtomicInt<uint64_t>::SetValueConditional(ValueType n, ValueType condition)
        {
            return sceAtomicCompareAndSwap64(reinterpret_cast<volatile int64_t*>(&mValue), condition, n) == condition;
        }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::Increment()
        {
            return sceAtomicIncrement64(reinterpret_cast<volatile int64_t*>(&mValue)) + 1;
        }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::Decrement()
        {
            return sceAtomicDecrement64(reinterpret_cast<volatile int64_t*>(&mValue)) - 1;
        }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::Add(ValueType n)
        {
            return sceAtomicAdd64(reinterpret_cast<volatile int64_t*>(&mValue), n) + n;
        }
    }
}

#endif
