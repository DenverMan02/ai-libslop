
#ifndef __SEXYAPPFRAMEWORK_MEMTRACK_H__
#define __SEXYAPPFRAMEWORK_MEMTRACK_H__


#ifdef MEMTRACK_ENABLE
#define MEMTRACK_LENGTH 1024
#include "common.h"
#include <map>
#include <string>
extern void RecordMemAlloc( void* theP, unsigned long theSize, const char* file, int line, bool bAdd );
extern void RemoveMemAlloc( void* theP );

namespace Sexy
{
    class Graphics;
    
    class MemTracker
    {
    public:
        MemTracker();
        ~MemTracker();
        
        void Reset();
        void Draw( Graphics* g );
        void RecordSample();
        
        void RecordMemAlloc( unsigned long theSize );
        void RecordMemDealloc( unsigned long theSize );
        
        bool GetDrawEnabled() const 		        { return mMemHistDraw; }
        void SetDrawEnabled( bool i_val ) 		    { mMemHistDraw = i_val; }
        
        bool GetTrackingEnabled() const 		    { return mMemTrackingEnabled; }
        void SetTrackingEnabled( bool i_val ) 		{ mMemTrackingEnabled = i_val; }
        
        unsigned int GetMaxMemoryAvailable() const  { return mMaxMemoryAvailable; }
        void SetMaxMemoryAvailable( unsigned int i_val ) { mMaxMemoryAvailable = i_val; }
        
    private:
        unsigned int mByteCntHeapMaxSizeInUse;
        unsigned int mByteCntHeapMaxSize;
        unsigned int mMemHistCurIdx;
        unsigned int mItemCnt;
        
        unsigned int mMaxMemoryAvailable;
        bool mMemHistDraw;
        bool mMemTrackingEnabled;
        
        struct MemHistItem
        {
            unsigned int mByteInUse;
            unsigned int mByteSize;
            unsigned int mByteDealloc;
            unsigned int mByteAlloc;
        } mMemHist[ MEMTRACK_LENGTH ];
    };
    
    struct MemData
    {
        MemData() : mCritSect(false), mEnabled(true), mMemAllocTrigger(100000) {}
        ~MemData() {
            OutputReport(true);
        }
        void OutputReport( bool theDeltaOnly );
        void Clear();
        
        std::map<void*, unsigned long> mSize;
        std::map<void*, std::string> mLocId;
        std::map<std::string, int> mLocSize;
        std::map<std::string, int> mLastLocSize;
        bool mCritSect;
        bool mEnabled;
        
        int mTotalSize;
        int mMemAllocTrigger;
    };
    
    extern MemData gMemData;
    extern MemTracker* gMemTracker;
}

// overrides to new & delete
// $$ jbilas -- move to prime driver
#ifdef HOST_PS3
void* operator new(size_t size) throw();
void* operator new[](size_t size) throw();
#endif

#if defined HOST_ANDROID
void* operator new(unsigned int size, const char* file, int line);
void* operator new[](unsigned int size, const char* file, int line);
#elif defined HOST_IPHONEOS
void* operator new(size_t size, const char* file, int line) throw();
void* operator new[](size_t size, const char* file, int line) throw();
#endif

// $$ jbilas -- there are more ps3 defs @ C:/usr/local/cell/target/ppu/include/new. Technically we should have a driver for this.
#ifdef HOST_PS3
// void *operator new(_CSTD size_t, _CSTD size_t, const _STD nothrow_t&);	// allocate or return null pointer
// void *operator new(_CSTD size_t, _CSTD size_t, void *_Where);
// void *operator new[](_CSTD size_t, _CSTD size_t) _THROW1(_XSTD bad_alloc);
// void *operator new[](_CSTD size_t, _CSTD size_t, const _STD nothrow_t&) _THROW0();
// void *operator new[](_CSTD size_t, _CSTD size_t, void *_Where) _THROW0();

// void *__wrap_malloc(size_t);
#endif

/*
 void operator delete  (void *, _CSTD size_t) _THROW0();	// delete allocated storage
 void operator delete[](void *, _CSTD size_t) _THROW0();	// delete allocated array
 void operator delete  (void *, _CSTD size_t, const _STD nothrow_t&) _THROW0();
 void operator delete[](void *, _CSTD size_t, const _STD nothrow_t&) _THROW0();
 void operator delete  (void *, _CSTD size_t, void *) _THROW0();
 void operator delete[](void *, _CSTD size_t, void *) _THROW0();
 */

//#ifdef HOST_PS3

//#endif

#if defined HOST_ANDROID
void operator delete(void* p);
void operator delete[](void* p);
#elif defined HOST_IPHONEOS
void operator delete(void* p) throw();
void operator delete[](void* p) throw();
#endif

//#if defined HOST_ANDROID
//void operator delete(void* pMem, const char *file, int line);
//void operator delete[](void* pMem, const char *file, int line);
//#elif defined HOST_IPHONEOS
//void operator delete(void* pMem, const char *file, int line) throw();
//void operator delete[](void* pMem, const char *file, int line) throw();
//#endif



void* malloc_custom(unsigned long _Size, const char* file, int line);
void* realloc_custom(void *ptr, unsigned long _Size, const char* file, int line);
void free_custom(void *ptr);
#endif // MEMTRACK_ENABLE

#endif // __SEXYAPPFRAMEWORK_MEMTRACK_H__
