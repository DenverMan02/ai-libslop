#ifndef PS3_MEMORY_H_INCLUDED
#define PS3_MEMORY_H_INCLUDED

#include "Debug.h"

#include <cell/gcm.h>

namespace Sexy
{
/*
	PS3 Memory management functions for RSX accesible memory (Main and Local).
	Eventually we will want probably to wrap these around something like dlmalloc.
*/

extern uint32_t gMainMemSize;
extern uint32_t gMainMemBase;
extern uint32_t gMainMemHeap;
extern bool gIsMainMemHeapInitialized;

extern uint32_t gLocalMemSize;
extern uint32_t gLocalMemBase;
extern uint32_t gLocalMemHeap;
extern bool gIsLocalMemHeapInitialized;

#define _DEBUG_MEM

// Allocates from main memory accesible by RSX 
//	Currently used for batched/temporary vertex buffers as well as RSB decompression buffers
inline void mainMemInit()
{
	assert(!gIsMainMemHeapInitialized);

	gMainMemSize = 1024 * 1024 * 8;//8Mb
	gMainMemBase = gMainMemHeap = (uint32_t)memalign(0x100000, gMainMemSize );
	assert( gMainMemBase != NULL );

	uint32_t mainOffset;
	int32_t err = cellGcmMapMainMemory((void*)gMainMemBase, gMainMemSize, &mainOffset);
	assert(err==CELL_OK);

	gIsMainMemHeapInitialized = true;
}

inline void *mainMemAlloc(const uint32_t size)
{
	if(!gIsMainMemHeapInitialized)
		mainMemInit();

	uint32_t allocated_size = (size + 1023) & (~1023);//not sure why this is here.
	void *mem = (void*)gMainMemHeap;
	gMainMemHeap += allocated_size;

#ifdef _DEBUG_MEM
	uint32_t mainMemUsed = gMainMemHeap - gMainMemBase;
	float percentUsed = 100.f * (((float)mainMemUsed)/gMainMemSize);
	OutputDebug("RSX Mapped MainMem Usage %02.2f%%\n", percentUsed);
#endif

	assert( gMainMemHeap <= gMainMemBase + gMainMemSize );
	return mem;
}

inline void *mainMemAllocAlign(const uint32_t size, const uint32_t align )
{
	if(!gIsMainMemHeapInitialized)
		mainMemInit();

	gMainMemHeap = (gMainMemHeap + align-1) & (~(align-1));
	return (void*)mainMemAlloc(size);
}

inline void mainMemFree( void *mem )
{
	OutputDebug("mainMemFree\n");
}

//allocates from local (video) memory.  
//Memory allocated by these functions shouldn't be read/written to by the PPU
inline void localMemInit()
{
	assert(!gIsLocalMemHeapInitialized);

	CellGcmConfig gcmConfig;
	cellGcmGetConfiguration(&gcmConfig);

	gLocalMemSize = gcmConfig.localSize;
	gLocalMemBase = gLocalMemHeap = (uint32_t)gcmConfig.localAddress;

	gIsLocalMemHeapInitialized = true;
}

inline void *localMemAlloc(const uint32_t size)
{
	if(!gIsLocalMemHeapInitialized)
		localMemInit();

	uint32_t allocated_size = (size + 1023) & (~1023);//not sure why this is here.
	void *mem = (void*)gLocalMemHeap;
	gLocalMemHeap += allocated_size;

#ifdef _DEBUG_MEM
	uint32_t localMemUsed = gLocalMemHeap - gLocalMemBase;
	float percentUsed = 100.f * (((float)localMemUsed)/gLocalMemSize);
	OutputDebug("LocalMem Usage %02.2f%%\n", percentUsed);
#endif

	assert( gLocalMemHeap <= gLocalMemBase + gLocalMemSize );
	return mem;
}

inline void *localMemAllocAlign(const uint32_t align, const uint32_t size )
{
	if(!gIsLocalMemHeapInitialized)
		localMemInit();

	gLocalMemHeap = (gLocalMemHeap + align-1) & (~(align-1));
	return (void*)localMemAlloc(size);
}

inline void localMemFree( void *mem )
{
	OutputDebug("localMemFree\n");
}

};

#endif
