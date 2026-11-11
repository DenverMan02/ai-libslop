// TodDebug.h

#ifndef __TODDEBUG_H__
#define __TODDEBUG_H__

#include "SexyAppFramework/Debug.h"

#if defined(RELEASEFINAL)
	#undef ASSERTIONS_ENABLED
#elif defined(NDEBUG)
	//#undef ASSERTIONS_ENABLED
	#define ASSERTIONS_ENABLED
#else
	#define ASSERTIONS_ENABLED
//	#define TOD_TRACK_MEMORY
#endif

#ifndef ASSERTIONS_ENABLED

#pragma warning(disable: 4701) // warning C4701: potentially uninitialized local variable '???' used
#pragma warning(disable: 4715) // warning C4715: '???' : not all control paths return a value
#pragma warning(disable: 4189) // warning C4189: '???' : local variable is initialized but not referenced

#define DBG_ASSERT_MSG(condition, msg, ...) do { (void)sizeof(condition); (void)sizeof(msg); } while(0)
// [PVZ2 CHANGE BEGIN] mmcdonald
#define DBG_WARN_MSG(condition, msg, ...) do { (void)sizeof(condition); (void)sizeof(msg); } while(0)
// [PVZ2 CHANGE END]
#define DBG_HALT() do {} while(0)
#define DBG_HALT_MSG(msg, ...) ((void)0)

#define TodTraceAndLog(flags, ...) do { (void)sizeof(flags); } while(0)
#define TodTrace(format, ...) do { (void)sizeof(format); } while(0)
#define TodTraceWithoutSpamming(format, ...) do { (void)sizeof(format); } while(0)
#define TodLog(format, ...) do { (void)sizeof(format); } while(0)
#define TodTraceAndLogErr(format, ...) do { (void)sizeof(format); } while(0)
#define TodLogString(msg) do { (void)sizeof(msg); } while(0)
#define TodTraceMemory(format, ...) do { (void)sizeof(format); } while(0)

#else // ASSERTIONS_ENABLED

// new trace log functions
void TodTraceAndLog( int i_consFlags, const char *i_format, ... );
void TodTrace(const char *format, ...);
void TodTraceWithoutSpamming(const char *format, ...);
void TodLog(const char *i_format, ...);
void TodTraceAndLog(const char *i_format, ...);
void TodTraceAndLogErr(const char *i_format, ...);
void TodLogString(const char *i_msg);
void TodTraceMemory(const char *i_format, ...);

#undef DBG_ASSERT

#ifdef HOST_WINDOWS
#define TodDebugBreak() if (::IsDebuggerPresent()) { __asm int 3 }
void __declspec(noreturn) DoesntReturnStub();
#else 
#define TodDebugBreak() ((void)0)
#endif


void TodAssertFailed(const char *i_condition, const char *i_file, int i_line, const char *i_msg, ...);

#ifdef HOST_WINDOWS
#define DBG_ASSERT(condition) do { \
	if (!(condition)) \
{ \
	TodAssertFailed(#condition, __FILE__, __LINE__, ""); \
	TodDebugBreak(); \
	DoesntReturnStub(); \
} } while(0)

#define DBG_ASSERT_MSG(condition, msg, ...) do { \
	if (!(condition)) \
{ \
	TodAssertFailed(#condition, __FILE__, __LINE__, msg, __VA_ARGS__); \
	TodDebugBreak(); \
	DoesntReturnStub(); \
} } while(0)

// [PVZ2 CHANGE BEGIN] mmcdonald
#define DBG_WARN_MSG(condition, msg, ...) do { \
if (!(condition)) \
{ \
    TodAssertFailed(#condition, __FILE__, __LINE__, msg, ## __VA_ARGS__); \
} } while(0)
// [PVZ2 CHANGE END]

#define DBG_HALT() do { \
{ \
	TodAssertFailed("", __FILE__, __LINE__, ""); \
	TodDebugBreak(); \
	DoesntReturnStub(); \
} } while(0)

#define DBG_HALT_MSG(msg, ...) do { \
{ \
	TodAssertFailed("", __FILE__, __LINE__, msg, __VA_ARGS__); \
	TodDebugBreak(); \
	DoesntReturnStub(); \
} } while(0)
#else // ios & macosx
#define DBG_ASSERT(condition) do { \
if (!(condition)) \
{ \
    TodAssertFailed(#condition, __FILE__, __LINE__, ""); \
	DBG_ASSERTE(condition); \
    __builtin_unreachable(); \
} } while(0)

#define DBG_ASSERT_MSG(condition, msg, ...) do { \
if (!(condition)) \
{ \
    TodAssertFailed(#condition, __FILE__, __LINE__, msg, ## __VA_ARGS__); \
	DBG_ASSERTE(condition); \
    __builtin_unreachable(); \
} } while(0)

// [PVZ2 CHANGE BEGIN] mmcdonald
#define DBG_WARN_MSG(condition, msg, ...) do { \
if (!(condition)) \
{ \
    TodAssertFailed(#condition, __FILE__, __LINE__, msg, ## __VA_ARGS__); \
} } while(0)
// [PVZ2 CHANGE END]

#define DBG_HALT() do { \
{ \
    TodAssertFailed("", __FILE__, __LINE__, ""); \
	DBG_ASSERTE(false); \
} } while(0)

#define DBG_HALT_MSG(msg, ...) do { \
{ \
    TodAssertFailed("", __FILE__, __LINE__, msg, ## __VA_ARGS__); \
	DBG_ASSERTE(false); \
} } while(0)

#endif

#endif // ASSERTIONS_ENABLED

void TodMemoryDetectLeaks();
void TodMemoryTraceAllocations();

#ifdef TOD_TRACK_MEMORY

void *TodMalloc(int i_size);
void *TodCalloc(int i_size);
void TodFree(void *i_block);

// Note that I'm not overriding the placement new or nothrow new operators because we don't use those

inline void* __cdecl operator new(unsigned int i_size)
{
	return TodMalloc(i_size);
}

inline void* __cdecl operator new[](unsigned int size)
{
	return TodMalloc(size);
}

inline void* __cdecl operator new(unsigned int size, const char* file, int line)
{
//	void* ptr = (void*)malloc(size);
//	SexyMemAddTrack(ptr, size, file, line);
//	return(ptr);
	return TodMalloc(size);
}

inline void* __cdecl operator new(unsigned int size, void* ptr, const char* file, int line, bool isFucked)
{
	//	void* ptr = (void*)malloc(size);
	//	SexyMemAddTrack(ptr, size, file, line);
	//	return(ptr);
	return ptr; //TodMalloc(size);
}

//Same as above, but for arrays
inline void* __cdecl operator new[](unsigned int size, const char* file, int line)
{
//	void* ptr = (void*)malloc(size);
//	SexyMemAddTrack(ptr, size, file, line);
//	return(ptr);
	return TodMalloc(size);
}

inline void* __cdecl operator new(unsigned int size, void* ptr, const char* file, int line)
{
	return TodMalloc(size);
}

inline void __cdecl operator delete(void* p)
{
	TodFree(p);
}

inline void __cdecl operator delete[](void* p)
{
	TodFree(p);
}

//needed in case in the constructor of the class we're newing, it throws an exception
inline void __cdecl operator delete(void* pMem, const char *file, int line)
{
	free(pMem);
}

inline void __cdecl operator delete[](void* pMem, const char *file, int line)
{
	free(pMem);
}

inline void __cdecl operator delete(void* pMem, void* pWhere, const char* file, int line, bool isFucked)
{
	free(pMem);
}


//#define DEBUG_NEW new(__FILE__, __LINE__)
//#define new DEBUG_NEW

//#define DEBUG_NEW1 new(ptr, __FILE__, __LINE__, true)

//#define DEBUG_NEW_1 new(ptr, __FILE__, __LINE__, true)
//#define New1(ptr) DEBUG_NEW_1

#endif // TOD_TRACK_MEMORY

typedef void (*BetaSubmitFuncType)();
void TodAssertInitForApp(BetaSubmitFuncType i_func = NULL);
//void TodAssertInitForApp();

void TodErrorMessageBox(const char *i_message, const char *i_title = "Error");
void TodVsnprintfEnsureNewLine(char *buffer, int size, const char *i_format, va_list i_argList);

void TodHesitationStartBuffer();
void TodHesitationTrace(const char *i_format, ...);
void TodHesitationEndBuffer();

const int MAX_HESITATION_MESSAGE_SIZE = 256;

class TodHesitationBracket
{
public:
	TodHesitationBracket(const char *i_format, ...);
	~TodHesitationBracket();
	void EndBracket();
	char m_message[MAX_HESITATION_MESSAGE_SIZE];
	int m_bracketStartTime;
};

extern char gDebugDataFolder[];
typedef void (*BetaSubmitFuncType)();
extern BetaSubmitFuncType gBetaSubmitFunc;

#endif // __TODDEBUG_H__
