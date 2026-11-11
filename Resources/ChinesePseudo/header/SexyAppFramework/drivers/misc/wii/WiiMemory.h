#ifndef WII_MEMORY_H_INCLUDED
#define WII_MEMORY_H_INCLUDED

#include <new>

#include <revolution/types.h>
#include <revolution/os.h>
#include <revolution/mem.h>

//	I copied the following from the Wii docs -- We can define our own 'new' and 'delete' so CodeWarrior/MSL 
//	doesn't use all of MEM1 as the heap.  Currently, using all of MEM1 as the heap is pretty much what we 
//	want though so I do that anyway...
//
//	The following functions allocate memory from MEM1 by default:
//	new, delete, OSAlloc
//
//	To access MEM2, use the convinence functions (MEM2Alloc/MEM2Free)
//
// For something even better, look at "global new/delete overloading and link order" in the newsgroups.
//  There you can see how to use a hook for pre-static initalization that would allow us to completely 
//  override new/delete if the need arises.

static MEMHeapHandle gMEM2HeapHandle = NULL;
static BOOL gIsMEM2HeapInitialized = FALSE;
static u32 gMEM2Available = 0;
static u32 gMEM2Allocated = 0;

static void MEM2Init()
{
	void* arenaLo;
	void* arenaHi;
	if (gIsMEM2HeapInitialized)
		return;
	
	ASSERT(gMEM2HeapHandle==NULL);

	arenaLo = OSGetMEM2ArenaLo();
	arenaHi = OSGetMEM2ArenaHi();

	unsigned long gMEM2Available = ((unsigned long)arenaHi-(unsigned long)arenaLo);
	gMEM2HeapHandle = MEMCreateExpHeap(arenaLo, gMEM2Available );

	gIsMEM2HeapInitialized = TRUE;
}

inline void *MEM2Alloc( u32 size )
{
	if( !gIsMEM2HeapInitialized )
		MEM2Init();
	
	ASSERT(gIsMEM2HeapInitialized);
	ASSERT(gMEM2HeapHandle!=NULL);
	void *mem = MEMAllocFromExpHeap( gMEM2HeapHandle, size );
	if( mem != NULL )
		gMEM2Allocated += size;
	return mem;
		
}

inline void *MEM2AllocAlign( u32 size, int align )
{
	if( !gIsMEM2HeapInitialized )
		MEM2Init();
	
	ASSERT(gIsMEM2HeapInitialized);
	ASSERT(gMEM2HeapHandle!=NULL);
	void *mem = MEMAllocFromExpHeapEx( gMEM2HeapHandle, size, align );
	if( mem != NULL )
		gMEM2Allocated += size;
	return mem;
}

inline void MEM2Free( void *mem )
{
	if( mem == NULL )
		return;
	
	ASSERT(gIsMEM2HeapInitialized);
	ASSERT(gMEM2HeapHandle!=NULL);
	
	u32 size = MEMGetSizeForMBlockExpHeap( mem );
	gMEM2Allocated -= size;
	
	MEMFreeToExpHeap( gMEM2HeapHandle, mem );
}


//MEM1 handling is currently disabled since the default behaviour of MSL is pretty much what we want.
/*
#define MEM1_HEAP_ID 0

static BOOL IsMEM1HeapInitialized = FALSE;

static void MEM1Init()
{
	void* arenaLo;
	void* arenaHi;
	if (IsMEM1HeapInitialized)
	{
		return;
	}

	arenaLo = OSGetMEM1ArenaLo();
	arenaHi = OSGetMEM1ArenaHi();

	// Create a heap
	// OSInitAlloc should only ever be invoked once.
	arenaLo = OSInitAlloc(arenaLo, arenaHi, 1); // 1 heap
	OSSetMEM1ArenaLo(arenaLo);

	// Ensure boundaries are 32B aligned
	arenaLo = (void*)OSRoundUp32B(arenaLo);
	arenaHi = (void*)OSRoundDown32B(arenaHi);

	// The boundaries given to OSCreateHeap should be 32B aligned
	OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));

	// From here on out, OSAlloc and OSFree behave like malloc and free
	// respectively

	OSSetMEM1ArenaLo(arenaLo=arenaHi);
	IsMEM1HeapInitialized = TRUE;
}

void* operator new ( u32 size ,std::nothrow_t const&) throw()
{
	if (!IsMEM1HeapInitialized)
	{
		MEM1Init();
	}
	return OSAllocFromHeap(MEM1_HEAP_ID, size);
}

void* operator new[] ( u32 size, std::nothrow_t const&) throw()
{
	if (!IsMEM1HeapInitialized)
	{
		MEM1Init();
	}

	return OSAllocFromHeap(MEM1_HEAP_ID, size);
}

void operator delete ( void* block ) throw()
{
	OSFreeToHeap(MEM1_HEAP_ID, block);
}

void operator delete[] ( void* block ) throw()
{
	OSFreeToHeap(MEM1_HEAP_ID, block);
}

*/
#endif
