/////////////////////////////////////////////////////////////////////////////
// eathread_atomic_android.h
//
// Copyright (c) 2010, Electronic Arts Inc. All rights reserved.
//
// Defines functionality for threadsafe primitive operations.
// Created by Scott Graham
/////////////////////////////////////////////////////////////////////////////


#ifndef EATHREAD_GCC_EATHREAD_ATOMIC_ANDROID_H
#define EATHREAD_GCC_EATHREAD_ATOMIC_ANDROID_H


#include <EABase/eabase.h>
#include <stddef.h>


#define EA_THREAD_ATOMIC_IMPLEMENTED

#if !defined(__aarch64__)
#include <sys/atomics.h>
#endif


namespace EA
{
    namespace Thread
    {
        int64_t android_fake_atomic_swap_64(int64_t value, volatile int64_t* addr);
        int android_fake_atomic_cmpxchg_64(int64_t oldvalue, int64_t newvalue, volatile int64_t* addr);
        int64_t android_fake_atomic_read_64(volatile int64_t* addr);

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
            inline            operator const ValueType() const { return GetValue(); }
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


        /* sys/atomics.h 
                extern int __atomic_cmpxchg(int old, int _new, volatile int *ptr);
                extern int __atomic_swap(int _new, volatile int *ptr);
                extern int __atomic_dec(volatile int *ptr);
                extern int __atomic_inc(volatile int *ptr);

                int __futex_wait(volatile void *ftx, int val, const struct timespec *timeout);
                int __futex_wake(volatile void *ftx, int count);
        */

        // TODO Gets are non-atomic. OK?
#if defined(__aarch64__)

        inline int __atomic_cmpxchg_ex2(int old, int _new, volatile int *ptr)
        {
            /* We must return 0 on success */
            return __sync_val_compare_and_swap(ptr, old, _new) != old;
        }

        inline int __atomic_swap_ex2(int _new, volatile int *ptr)
        {
            int prev;
            do {
                prev = *ptr;
            } while (__sync_val_compare_and_swap(ptr, prev, _new) != prev);
            return prev;
        }

        inline int __atomic_inc_ex2(volatile int *ptr)
        {
          return __sync_fetch_and_add (ptr, 1);
        }

        inline int __atomic_dec_ex2(volatile int *ptr)
		{
		  return __sync_fetch_and_sub (ptr, 1);
		}

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::SetValue(ValueType n)
        	//{ return __sync_lock_test_and_set(&mValue, n); }
            { return __atomic_swap_ex2(n, &mValue); }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::SetValue(ValueType n)
            { return __atomic_swap_ex2(n, (volatile int*)&mValue); }
        //{ //return __sync_lock_test_and_set(&mValue, n); }

        template <> inline
        bool AtomicInt<int32_t>::SetValueConditional(ValueType n, ValueType condition)
            { return (__atomic_cmpxchg_ex2(condition, n, &mValue) == 0); }
        //{ //return __sync_bool_compare_and_swap(&mValue, condition, n); }

        template <> inline
        bool AtomicInt<uint32_t>::SetValueConditional(ValueType n, ValueType condition)
            { return (__atomic_cmpxchg_ex2(condition, n, (volatile int*)&mValue) == 0); }
        //{ return __sync_bool_compare_and_swap(&mValue, condition, n); }

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Increment()
            { return __atomic_inc_ex2(&mValue) + 1; }
        //{ return __sync_fetch_and_add(&mValue, int(1)); }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Increment()
            { return __atomic_inc_ex2((volatile int*)&mValue) + 1; }
        //{ return __sync_fetch_and_add(&mValue, int(1)); }

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Decrement()
            { return __atomic_dec_ex2(&mValue) - 1; }
        //{ return __sync_fetch_and_add(&mValue, int(-1)); }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Decrement()
            { return __atomic_dec_ex2((volatile int*)&mValue) - 1; }
        //{ return __sync_fetch_and_add(&mValue, int(-1)); }
#else
        template <> inline
		AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::SetValue(ValueType n)
			{ return __atomic_swap(n, &mValue); }

		template <> inline
		AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::SetValue(ValueType n)
			{ return __atomic_swap(n, (volatile int*)&mValue); }

		template <> inline
		bool AtomicInt<int32_t>::SetValueConditional(ValueType n, ValueType condition)
			{ return (__atomic_cmpxchg(condition, n, &mValue) == 0); }

		template <> inline
		bool AtomicInt<uint32_t>::SetValueConditional(ValueType n, ValueType condition)
			{ return (__atomic_cmpxchg(condition, n, (volatile int*)&mValue) == 0); }

		template <> inline
		AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Increment()
			{ return __atomic_inc(&mValue) + 1; }

		template <> inline
		AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Increment()
			{ return __atomic_inc((volatile int*)&mValue) + 1; }

		template <> inline
		AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Decrement()
			{ return __atomic_dec(&mValue) - 1; }

		template <> inline
		AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Decrement()
			{ return __atomic_dec((volatile int*)&mValue) - 1; }
#endif

        template <> inline
        AtomicInt<int32_t>::ValueType AtomicInt<int32_t>::Add(ValueType n)
            {
                // http://gcc.gnu.org/onlinedocs/gcc-4.4.2/gcc/Atomic-Builtins.html
                return __sync_add_and_fetch(&mValue, n); 
            }

        template <> inline
        AtomicInt<uint32_t>::ValueType AtomicInt<uint32_t>::Add(ValueType n)
            { 
                // http://gcc.gnu.org/onlinedocs/gcc-4.4.2/gcc/Atomic-Builtins.html
                return __sync_add_and_fetch(&mValue, n); 
            }


        ///////////////////////////////////////////////////////////
        /// 64 bit, simulated
        ///
        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::GetValue() const
            { return android_fake_atomic_read_64((volatile int64_t*)&mValue); }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::GetValue() const
            { return android_fake_atomic_read_64((volatile int64_t*)&mValue); }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::SetValue(ValueType n)
        {
            const ValueType nOldValue(mValue);
            android_fake_atomic_swap_64((int64_t)n, (volatile int64_t*)&mValue);
            return nOldValue;
        }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::SetValue(ValueType n)
        {
            const ValueType nOldValue(mValue);
            android_fake_atomic_swap_64((int64_t)n, (volatile int64_t*)&mValue);
            return nOldValue;
        }

        template <> inline
        bool AtomicInt<int64_t>::SetValueConditional(ValueType n, ValueType condition)
        {
            return android_fake_atomic_cmpxchg_64(condition, n, (volatile int64_t*)&mValue) == 0;
        }

        template <> inline
        bool AtomicInt<uint64_t>::SetValueConditional(ValueType n, ValueType condition)
        {
            return android_fake_atomic_cmpxchg_64(condition, n, (volatile int64_t*)&mValue) == 0;
        }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::Add(ValueType n)
        {
            int64_t old;

            do {
                old = mValue;
            }
            while (android_fake_atomic_cmpxchg_64((int64_t)old, (int64_t)old+n, (volatile int64_t*)&mValue) != 0);

            return mValue;
        }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::Add(ValueType n)
        {
            uint64_t old;

            do {
                old = mValue;
            }
            while (android_fake_atomic_cmpxchg_64((int64_t)old, (int64_t)old+n, (volatile int64_t*)&mValue) != 0);

            return mValue;
        }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::Increment()
            { return Add(1); }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::Increment()
            { return Add(1); }

        template <> inline
        AtomicInt<int64_t>::ValueType AtomicInt<int64_t>::Decrement()
            { return Add(-1); }

        template <> inline
        AtomicInt<uint64_t>::ValueType AtomicInt<uint64_t>::Decrement()
            { return Add(-1); }



        /* To do

        inline int32_t AtomicGetValue(volatile int32_t*)
            { }
        inline void AtomicSetValue(volatile int32_t*, int32_t value)
            { }
        inline int32_t AtomicIncrement(volatile int32_t*)
            { }
        inline int32_t AtomicDecrement(volatile int32_t*)
            { }
        inline int32_t AtomicAdd(volatile int32_t*, int32_t value)
            { }
        inline int32_t AtomicOr(volatile int32_t*, int32_t value)
            { }
        inline int32_t AtomicAnd(volatile int32_t*, int32_t value)
            { }
        inline int32_t AtomicXor(volatile int32_t*, int32_t value)
            { }
        inline int32_t AtomicSwap(volatile int32_t*, int32_t value)
            { }
        inline bool AtomicSetValueConditional(volatile int32_t*, int32_t value, int32_t condition)
            { }

        inline uint32_t AtomicGetValue(volatile uint32_t*)
            { }
        inline void AtomicSetValue(volatile uint32_t*, uint32_t value)
            { }
        inline uint32_t AtomicIncrement(volatile uint32_t*)
            { }
        inline uint32_t AtomicDecrement(volatile uint32_t*)
            { }
        inline uint32_t AtomicAdd(volatile uint32_t*, uint32_t value)
            { }
        inline uint32_t AtomicOr(volatile uint32_t*, uint32_t value)
            { }
        inline uint32_t AtomicAnd(volatile uint32_t*, uint32_t value)
            { }
        inline uint32_t AtomicXor(volatile uint32_t*, uint32_t value)
            { }
        inline uint32_t AtomicSwap(volatile uint32_t*, uint32_t value)
            { }
        inline bool AtomicSetValueConditional(volatile uint32_t*, uint32_t value, uint32_t condition)
            { }

        inline int64_t AtomicGetValue(volatile int64_t*)
            { }
        inline void AtomicSetValue(volatile int64_t*, int64_t value)
            { }
        inline int64_t AtomicIncrement(volatile int64_t*)
            { }
        inline int64_t AtomicDecrement(volatile int64_t*)
            { }
        inline int64_t AtomicAdd(volatile int64_t*, int64_t value)
            { }
        inline int64_t AtomicOr(volatile int64_t*, int64_t value)
            { }
        inline int64_t AtomicAnd(volatile int64_t*, int64_t value)
            { }
        inline int64_t AtomicXor(volatile int64_t*, int64_t value)
            { }
        inline int64_t AtomicSwap(volatile int64_t*, int64_t value)
            { }
        inline bool AtomicSetValueConditional(volatile int64_t*, int64_t value, int64_t condition)
            { }

        inline uint64_t AtomicGetValue(volatile uint64_t*)
            { }
        inline void AtomicSetValue(volatile uint64_t*, uint64_t value)
            { }
        inline uint64_t AtomicIncrement(volatile uint64_t*)
            { }
        inline uint64_t AtomicDecrement(volatile uint64_t*)
            { }
        inline uint64_t AtomicAdd(volatile uint64_t*, uint64_t value)
            { }
        inline uint64_t AtomicOr(volatile uint64_t*, uint64_t value)
            { }
        inline uint64_t AtomicAnd(volatile uint64_t*, uint64_t value)
            { }
        inline uint64_t AtomicXor(volatile uint64_t*, uint64_t value)
            { }
        inline uint64_t AtomicSwap(volatile uint64_t*, uint64_t value)
            { }
        inline bool AtomicSetValueConditional(volatile uint64_t*, uint64_t value, uint64_t condition)
            { }
        */

    } // namespace Thread

} // namespace EA



#endif // EATHREAD_GCC_EATHREAD_ATOMIC_GCC_H









