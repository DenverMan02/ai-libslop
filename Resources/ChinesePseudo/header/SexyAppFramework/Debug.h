#ifndef __SEXYAPPFRAMEWORK_DEBUG_H__
#define __SEXYAPPFRAMEWORK_DEBUG_H__

#include "Common.h"

#include <cassert>

extern bool gInAssert;

#ifdef SEXY_TRACING_ENABLED
void SexyTrace(const char *theStr);
#define SEXY_TRACE(theStr) SexyTrace(theStr)
#else
#define SEXY_TRACE(theStr)
#endif

extern void SexyTraceFmt(const SexyChar* fmt ...);

bool _sexy_assert_msg(const char* message, const char* file, unsigned int line);
void _sexy_msg(const char* message, const char* file, unsigned int line);

//------------------------------------------------------------------------
// Better support for char* and wchar_t* exists in Common.cpp/h -dp 07.11.2008
// Moving this call to OutputDebugStrF, but remaining backwards compatible.
//extern void OutputDebug(const SexyChar* fmt ...);
//------------------------------------------------------------------------
#define OutputDebug OutputDebugStrF

// do { } while(0) in macros ensures they expand to a single statement,
// e.g. when used inside if / else statements

#if defined NDEBUG && !defined _DEBUG_OPT

	#if PRIME_IS_REPORTING_ENABLED

		#define DBG_ASSERTE(exp)				do { if (!(exp)) SEXY_WARN("ASSERT: '%s' in %s at line %d", #exp, __FILE__, __LINE__); } while(0)
		#define DBG_ASSERT(exp)					do { if (!(exp)) SEXY_WARN("ASSERT: '%s' in %s at line %d", #exp, __FILE__, __LINE__); } while(0)
		#define DBG_MSG(message, file, line)	do { _sexy_msg(message, file, line); } while(0)

	#else

		#define DBG_ASSERTE(exp)				do { (void)sizeof(exp); } while(0)
		#define DBG_ASSERT(exp)					do { (void)sizeof(exp); } while(0)
		#define DBG_MSG(message, file, line)	do { (void)sizeof(message); (void)sizeof(file); (void)sizeof(line); } while(0)

	#endif

	#define _HALT()				do { (void)sizeof(0); } while(0)

#else

	#ifdef HOST_WINDOWS

		_CRTIMP void __cdecl _wassert(__in_z const wchar_t * _Message, __in_z const wchar_t *_File, __in unsigned _Line);
		#define dbg_assert(_Expression) (void)( (!!(_Expression)) || (_wassert(_CRT_WIDE(#_Expression), _CRT_WIDE(__FILE__), __LINE__), 0) )

	#else

		#define dbg_assert(_Expression) ( (!!(_Expression)) || (_sexy_assert_msg((#_Expression), __FILE__, __LINE__)) )

	#endif

	#define DBG_ASSERTE(exp)				do { gInAssert = true; dbg_assert(exp); gInAssert = false; } while(0)
	#define DBG_ASSERT(exp)					do { gInAssert = true; dbg_assert(exp); gInAssert = false; } while(0)
	#define DBG_MSG( message, file, line ) 	do { _sexy_msg(message, file, line); } while(0)


	#if defined(HOST_WINDOWS) || defined (HOST_XBOX360) || defined (WINRT_CLUSTER)
		#define _HALT()	__debugbreak()    
	#elif defined(HOST_PS3)
		#define _HALT()	__asm__ volatile ( "tw 31,1,1" ) 
	#elif defined(PLATFORM_IPHONE)

		#define  _HALT()  asm("int3") 
	#elif defined(HOST_VITA)
		#define _HALT() __breakpoint(0);
	#else
		#define _HALT()	 ((void)0)
	#endif

#endif // NDEBUG

// This "assert" expression is true at compile-time and will only work on
// things the compiler can verify statically such as sizes, constants and
// static types. For example, this would be a good way to verify builtin
// size assumptions:
//
//     DBG_ASSERTSTATIC(sizeof(int32) == 4).
//
// A static assert will only fire at compile time as an error! It doesn't
// do anything to the compiled image and doesn't exist at runtime.
//
// Based on work from http://www.boost.org/doc/html/boost_staticassert.html.
//

template <bool x> struct __DBG_ASSERTSTATIC_FAILED_for_docs_see_DEBUG_H;
template <> struct __DBG_ASSERTSTATIC_FAILED_for_docs_see_DEBUG_H <true> { enum { value = 1 }; };
template <int x> struct __DBG_ASSERTSTATIC_TEST {};

#define DBG_ASSERTSTATIC(EXPR) \
	typedef __DBG_ASSERTSTATIC_TEST <sizeof(__DBG_ASSERTSTATIC_FAILED_for_docs_see_DEBUG_H <(bool)(EXPR)>)> \
	SEXY_STR_JOIN(__DBG_ASSERTSTATIC_TYPEDEF_, __LINE__)

#endif // __SEXYAPPFRAMEWORK_DEBUG_H__
