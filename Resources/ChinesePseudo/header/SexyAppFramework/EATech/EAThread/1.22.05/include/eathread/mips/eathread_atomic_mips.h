/////////////////////////////////////////////////////////////////////////////
// eathread_atomic_mips.h
//
// Copyright (c) 2003, Electronic Arts Inc. All rights reserved.
//
// Defines functionality for threadsafe primitive operations.
//
// Created by Paul Pedriana, Maxis
/////////////////////////////////////////////////////////////////////////////


#ifndef EATHREAD_MIPS_EATHREAD_ATOMIC_MIPS_H
#define EATHREAD_MIPS_EATHREAD_ATOMIC_MIPS_H


#ifndef INCLUDED_eabase_H
    #include <EABase/eabase.h>
#endif
#include <stddef.h>



#if defined(EA_PROCESSOR_MIPS) || defined(EA_PROCESSOR_R5900) || defined(EA_PROCESSOR_R3000) || defined(EA_PROCESSOR_R4000)
    #define EA_THREAD_ATOMIC_IMPLEMENTED

    // For PS2, the kernel has EIntr and DIntr functions which do the same as below, 
    // but don't exist for other platforms and are less efficient than below.
    // When you disable interrupts on a MIPS processor, you are really not disabling
    // them as much as you are delaying them. Any interrupts that were ready to 
    // happen while interrupts were disabled will immediately trigger upon re-enabling
    // the interrupts. So you don't have to worry about 'losing' interrupts while
    // they are disabled.
    // 
    // The MIPS R4000 series and later provide the Load Linked (ll) and Store 
    // Conditional (sc) instructions to implement mutual exclusion primitives. 
    // Paired ll/sc instructions can be used to attempt atomic memory accesses.
    // As soon as we start working with R4000 or later processors that support
    // the ll and sc instructions, we'll want to make a version of this code
    // that takes advantage of this. Talk to Paul Pedriana or look up 
    // "mips atomic ll" on Linux to find many examples of how to do this.

    #define MIPSEnableInterrupts() __asm__ __volatile__("ei")

    #define MIPSDisableInterrupts() \
    { \
            uint32_t status; \
            do{ \
                __asm__ __volatile__(".p2align 3"); \
                __asm__ __volatile__("di"); \
                __asm__ __volatile__("sync.p"); \
                __asm__ __volatile__("mfc0 %0, $12" : "=r"(status) : ); \
            }while(status & 0x00010000); \
    }

    namespace EA
    {
        namespace Thread
        {
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
                    { return mValue; } // For non-SMP MIPS, this really isn't going to matter. If we need to support SMP MIPS, then we might want to put an EAReadBarrier() barrier before the access.

                ValueType GetValueRaw() const
                    { return mValue; }

                ValueType SetValue(ValueType n)
                {
                    MIPSDisableInterrupts();
                    const ValueType nOldValue(mValue);
                    mValue = n;
                    MIPSEnableInterrupts();
                    return nOldValue;
                }

                bool SetValueConditional(ValueType n, ValueType condition)
                {
                    MIPSDisableInterrupts();
                    const bool bResult(mValue == condition);
                    if(bResult)
                        mValue = n;
                    MIPSEnableInterrupts();
                    return bResult;
                }

                ValueType Increment()
                {
                    MIPSDisableInterrupts();
                    const ValueType nNewValue(++mValue);
                    MIPSEnableInterrupts();
                    return nNewValue;
                }

                ValueType Decrement()
                {
                    MIPSDisableInterrupts();
                    const ValueType nNewValue(--mValue);
                    MIPSEnableInterrupts();
                    return nNewValue;
                }

                ValueType Add(ValueType n)
                {
                    MIPSDisableInterrupts();
                    const ValueType nNewValue(mValue += n);
                    MIPSEnableInterrupts();
                    return nNewValue;
                }

                // operators
                inline            operator const ValueType() const { return GetValue(); }  // Should this be provided? Is it safe enough? Return value of 'const' attempts to make this safe from misuse.
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


        } // namespace Thread


    } // namespace EA


#endif // EA_PROCESSOR_XXXX


#endif // EATHREAD_MIPS_EATHREAD_ATOMIC_MIPS_H











