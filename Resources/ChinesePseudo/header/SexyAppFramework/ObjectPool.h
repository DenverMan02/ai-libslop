#ifndef __OBJECTPOOL_H__
#define __OBJECTPOOL_H__

#include "Common.h"



namespace Sexy
{

#define OBJECT_POOL_SIZE_BYTES 0x8000

template <class _T>
class ObjectPool
{
public:
	int						mNumPools;
	int						mNumAvailObjects;
	uchar**					mDataPools;
	int**					mFreeIndicesPools;	

	int						mChunkSize;	

public:	
	ObjectPool()
	{
		mNumPools = 0;
		mNumAvailObjects = 0;
		mDataPools = NULL;
		mFreeIndicesPools = NULL;
		mChunkSize = sizeof(_T);
	}

	~ObjectPool()
	{
		for (int aPoolNum = 0; aPoolNum < mNumPools; aPoolNum++)
		{
			delete mDataPools[aPoolNum];
			delete mFreeIndicesPools[aPoolNum];
		}

		if (mDataPools != NULL)
			free(mDataPools);
		if (mFreeIndicesPools != NULL)
			free(mFreeIndicesPools);
	}

	void GrowPool()
	{	
		int aCurPoolNum = mNumPools;
		int aNumChunksPerPool = OBJECT_POOL_SIZE_BYTES / mChunkSize;

		mNumPools++;
		mNumAvailObjects += aNumChunksPerPool;

		mDataPools = (uchar**) realloc(mDataPools, sizeof(uchar*)*mNumPools);
		mDataPools[aCurPoolNum] = new uchar[OBJECT_POOL_SIZE_BYTES];

		mFreeIndicesPools = (int**) realloc(mFreeIndicesPools, sizeof(int*)*mNumPools);
		mFreeIndicesPools[aCurPoolNum] = new int[aNumChunksPerPool];

		// Fill in the indices of the new pool starting from the current allocation position

		int aCurIdx = aCurPoolNum*aNumChunksPerPool;		
		int* anIndexPtr = mFreeIndicesPools[0];
		int* anEnd = anIndexPtr + aNumChunksPerPool;
		while (anIndexPtr != anEnd)
			*(anIndexPtr++) = aCurIdx++;
	}

	_T* Alloc()
	{
		if (mNumAvailObjects == 0)
			GrowPool();

		int aNumChunksPerPool = OBJECT_POOL_SIZE_BYTES / mChunkSize;

		mNumAvailObjects--;
		int anIndex = mFreeIndicesPools[mNumAvailObjects/aNumChunksPerPool][mNumAvailObjects%aNumChunksPerPool];

		void* thePtr = &mDataPools[anIndex/aNumChunksPerPool][(anIndex%aNumChunksPerPool)*mChunkSize];
		_T* theObj = new (thePtr) _T();
		return theObj;
	}

	void Free(_T* thePtr)
	{
		int aNumChunksPerPool = OBJECT_POOL_SIZE_BYTES / mChunkSize;

		// Search from the back forward, since that's where most memory action will occur
		for (int aPoolNum = mNumPools-1; aPoolNum >= 0; aPoolNum--)
		{
			int anOffset = (int) ((uchar*) thePtr - mDataPools[aPoolNum]);
			if ((anOffset >= 0) && (anOffset < OBJECT_POOL_SIZE_BYTES))
			{
				// This falls into the pool's domain
				int anIndex = aPoolNum*aNumChunksPerPool + anOffset/mChunkSize;

				mFreeIndicesPools[mNumAvailObjects/aNumChunksPerPool][mNumAvailObjects%aNumChunksPerPool] = anIndex;
				mNumAvailObjects++;
				break;
			}
		}
		thePtr->~_T();
	}
};

};



#endif //__OBJECTPOOL_H__
