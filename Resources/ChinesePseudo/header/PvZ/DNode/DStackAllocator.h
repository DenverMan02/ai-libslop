//
//  DStackAllocator.h
//  DCore
//
//  Created by lzjseed on 16/2/19.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DStack_Allocator_h
#define DStack_Allocator_h

#define DStackAllocatorDefaultSize			(50*1024)
#define DStackAllocatorDefaultEntriesNum	(32)

#include <vector>

const size_t d_stackSize = DStackAllocatorDefaultSize;
const size_t d_maxStackEntries = DStackAllocatorDefaultEntriesNum;

struct DStackEntry
{
	char* data;
	size_t size;
	bool usedMalloc;
};

class  DStackAllocator
{
public:
	void*  push(size_t size);
	void   pop();
	void   pop(size_t num);
	void   popAll();

	size_t getMaxAllocation() const;
	
	static DStackAllocator* getInstance();
	static void purge();
    
private:
    DStackAllocator();
    virtual ~DStackAllocator();

	char m_data[d_stackSize];
	size_t m_index;

	size_t m_allocation;
	size_t m_maxAllocation;
    
	DStackEntry m_entries[d_maxStackEntries];
	size_t m_entryCount;

	static DStackAllocator* sp_stackAllocator;
};

#define DStackPush(size)					DStackAllocator::getInstance()->push(size)

#define DStackPushUseType(type)             (type*)DStackAllocator::getInstance()->push(sizeof(type))

#define DStackPushArrayUseType(type,num)	(type*)DStackAllocator::getInstance()->push(sizeof(type)*num)

#define DStackPop()                         DStackAllocator::getInstance()->pop()

#define DStackPopLoop(count)				DStackAllocator::getInstance()->pop(count)

#define DStackPopAll()						DStackAllocator::getInstance()->popAll()

#define DGetStackAllocMaxCount()			DStackAllocator::getInstance()->GetMaxAllocation()

#define DInitStackAllocator()				DStackAllocator::getInstance()

#define DDestroyStackAllocator()			DStackAllocator::purge()

#endif
