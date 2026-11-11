#pragma once

#define OFFSET_RTWEAKPTR_GETREGISTRY 0x14EAD90
#define OFFSET_RTWEAKPTR_COPYWEAKPTR 0x14F39CC
#define OFFSET_RTWEAKPTR_GETTABLEOFTYPE 0x14F31A4
#define OFFSET_RTWEAKPTR_RESOLVE 0x14EDE00
#define OFFSET_RTWEAKPTR_EQUALS 0x5AB660
#define OFFSET_RTWEAKPTR_ISVALIDPTR 0x5D8ABC
#define OFFSET_RTWEAKPTR_FROMOTHER 0x14D920C
#define OFFSET_RTWEAKPTR_SETWEAKPTR 0x14D8B08
#define OFFSET_RTWEAKPTR_MOVE 0x14D91C8

#define NULL_RTID 0LL

namespace Sexy
{
    template<typename T>
    class RtWeakPtr
    {
    public:

        int64_t mRtId;

        RtWeakPtr()
        {
            mRtId = NULL;
        }

        ~RtWeakPtr()
        {
			SetWeakPtr(NULL_RTID);
        }

        RtWeakPtr(RtWeakPtr* other) {
            mRtId = NULL;

            this->FromOther(other);
        }

        RtWeakPtr(RtWeakPtr&& other)
		{
            mRtId = NULL;

			Move(&other);
        }

        RtWeakPtr(const RtWeakPtr& other)
		{
            mRtId = NULL;

			FromOther(other);
        }

        bool operator==(const RtWeakPtr<T>& other) const
        {
            typedef bool(*equalsOther)(RtWeakPtr<T>*, RtWeakPtr<T>*);
            equalsOther equalsOtherFunc = (equalsOther)GetActualOffset(OFFSET_RTWEAKPTR_EQUALS);
            return equalsOtherFunc(this, &other);
        }

        bool operator==(RtWeakPtr<T>& other)
        {
            typedef bool(*equalsOther)(RtWeakPtr<T>*, RtWeakPtr<T>*);
            equalsOther equalsOtherFunc = (equalsOther)GetActualOffset(OFFSET_RTWEAKPTR_EQUALS);
            return equalsOtherFunc(this, &other);
        }

        RtWeakPtr<T>& operator=(const RtWeakPtr<T>& other)
        {
			FromOther(other);

            // This is how I've been using the assignment operator so far
            mRtId = other.mRtId;

            return *this;
        }

        RtWeakPtr<T>& operator=(RtWeakPtr<T>* other)
        {
			FromOther(other);
        }
		
        void SetWeakPtr(RtWeakPtr* other)
        {
            CallFunc<void, RtWeakPtr*, RtWeakPtr*>(OFFSET_RTWEAKPTR_SETWEAKPTR, this, other);
        }

        void Move(RtWeakPtr* other)
        {
            CallFunc<void, RtWeakPtr*, RtWeakPtr*>(OFFSET_RTWEAKPTR_MOVE, this, other);
        }

        void FromOther(RtWeakPtr* other)
        {
            CallFunc<void, RtWeakPtr*, RtWeakPtr*>(OFFSET_RTWEAKPTR_FROMOTHER, this, other);
        }

        bool Equals(RtWeakPtr<T>* other)
		{
            typedef bool(*equalsOther)(RtWeakPtr<T>*, RtWeakPtr<T>*);
            equalsOther equalsOtherFunc = (equalsOther)GetActualOffset(OFFSET_RTWEAKPTR_EQUALS);
            return equalsOtherFunc(this, other);
        }

        bool IsInvalid()
        {
            return mRtId == NULL;
        }

        bool IsValid()
        {
            return mRtId != NULL;
        }

        bool IsFromSheets()
        {
            return this->mRtId >> 0x1F;
        }
		
        int GetTypeId()
        {
            return (this->mRtId >> 0x11) & 0x3FFF;
        }

        void FromOther(RtWeakPtr* other)
        {
			FromOther(other);
        }

        // Get the object this points to, if valid.
        inline T* Get()
        {
            typedef void* (*getRegistry)();
            getRegistry getRegistryFunc = (getRegistry)GetActualOffset(OFFSET_RTWEAKPTR_GETREGISTRY);

            void* registry = getRegistryFunc();

            typedef void (*func14F39CC)(RtWeakPtr*, void*, RtWeakPtr*);
            func14F39CC func_0x14F39CC = (func14F39CC)GetActualOffset(OFFSET_RTWEAKPTR_COPYWEAKPTR);

            RtWeakPtr<T> temp;
            func_0x14F39CC(&temp, registry, this);

            T* retVal = NULL;
            if (!temp.IsInvalid())
            {
                int typeId = temp.GetTypeId();

                typedef void* (*func14F31A4)(void*, int);
                func14F31A4 func_0x14F31A4 = (func14F31A4)GetActualOffset(OFFSET_RTWEAKPTR_GETTABLEOFTYPE);

                void* v11 = func_0x14F31A4(registry, typeId);
                if (v11)
                {
                    typedef T* (*resolveWeakPtr)(void*, RtWeakPtr*);
                    resolveWeakPtr resolveWeakPtrFunc = (resolveWeakPtr)GetActualOffset(OFFSET_RTWEAKPTR_RESOLVE);
                    retVal = resolveWeakPtrFunc(v11, &temp);
                }
            }

            return retVal;
        }
		
		T* operator->()
		{
			return Get();
		}
    };
}