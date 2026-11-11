#ifndef __SEXYAPPFRAMEWORK_WINDOWS_PLATFORM_H__
#define __SEXYAPPFRAMEWORK_WINDOWS_PLATFORM_H__

#pragma warning(disable:4786)
#pragma warning(disable:4503)

#undef _WIN32_WINNT
#undef WIN32_LEAN_AND_MEAN

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#undef _UNICODE
#undef UNICODE

// override keyword only supported in VS 2005 and up
#if (!defined(_MSC_VER) || (_MSC_VER < 1400))
	#define override
#endif

//check off the features the platforms supports
#define SUPPORT_SYSFONT
#define SUPPORT_BITMAP_SYSFONT
#define SUPPORT_SEXY_CACHE
#define SUPPORT_SEH_CATCHER
#define SUPPORT_HTTP
#define SUPPORT_REF_PEFILES
#define SUPPORT_XPRINTF
#define SUPPORT_BASS
#define SUPPORT_WININET
#define SUPPORT_EXCEPTIONS
#define SUPPORT_DIRTY_RECTS
#define SUPPORT_REFLECTION
#define SUPPORT_LIVELINK
#define SUPPORT_FRAMEWORKCONFIG
#define SUPPORT_WWISE

#define NOMINMAX
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <assert.h>
#include <windows.h>
#include <shellapi.h> 
#include <mmsystem.h>
#include "ReflectionTags.h"
#include <unknwn.h>
#include <cctype>
#include <cwctype>

#ifdef _USE_WIDE_STRING

#define sexystrncmp			wcsncmp
#define sexystrnicmp		wcsnicmp
#define sexystrcmp			wcscmp
#define sexystricmp			_wcsicmp
#define sexysscanf			swscanf
#define sexyatoi			_wtoi
#define sexyatof			_wtof
#define sexystrcpy			wcscpy
#define sexyasctime			_wasctime
#define sexyisspace			iswspace

#ifndef SEXYFRAMEWORK_NO_REDEFINE_WIN_API
// Redefine the functions and structs we need to be wide-string
#undef CreateWindowEx
#undef RegisterClass
#undef MessageBox
#undef ShellExecute
#undef GetTextExtentPoint32
#undef RegisterWindowMessage
#undef CreateMutex
#undef DrawTextEx
#undef TextOut

#define CreateWindowEx				CreateWindowExW
#define RegisterClass				RegisterClassW
#define WNDCLASS					WNDCLASSW
#define MessageBox					MessageBoxW
#define ShellExecute				ShellExecuteW
#define GetTextExtentPoint32		GetTextExtentPoint32W
#define RegisterWindowMessage		RegisterWindowMessageW
#define CreateMutex					CreateMutexW
#define DrawTextEx					DrawTextExW
#define TextOut						TextOutW
#endif

#else

typedef std::string			SexyString;
typedef char				SexyChar;
#define _S(x)				x

#define _strcmp				strcmp
#define _strncmp			strncmp

#define sexystrncmp			strncmp
#define sexystrnicmp		strnicmp
#define sexystrcmp			strcmp
#define sexystricmp			stricmp
#define sexysscanf			sscanf
#define sexyatoi			atoi
#define sexyatof			atof
#define sexystrcpy			strcpy
#define sexyasctime			asctime

#endif

#define sexytoupper std::toupper
#define sexytolower std::tolower
#define sexytowupper std::towupper
#define sexytowlower std::towlower

#define LONG_BIGE_TO_NATIVE(l) (((l >> 24) & 0xFF) | ((l >> 8) & 0xFF00) | ((l << 8) & 0xFF0000) | ((l << 24) & 0xFF000000))
#define WORD_BIGE_TO_NATIVE(w) (((w >> 8) & 0xFF) | ((w << 8) & 0xFF00))
#define LONG_LITTLEE_TO_NATIVE(l) (l)
#define WORD_LITTLEE_TO_NATIVE(w) (w)

#define LENGTH(anyarray) (sizeof(anyarray) / sizeof(anyarray[0]))

typedef signed long long		int64;
typedef signed long				int32;
typedef signed short			int16;
typedef signed char				int8;
typedef unsigned long long		uint64;
typedef unsigned long			uint32;
typedef unsigned short			uint16;
typedef unsigned char			uint8;

typedef unsigned char			uchar;
typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;
typedef __int64					int64;
typedef unsigned __int64		uint64;

typedef float					float32;
typedef double					float64;

typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;

#include "MinMax.h"

#define __INT32_DEFINED__
#define __UINT32_DEFINED__
#define __INT16_DEFINED__
#define __UINT16_DEFINED__
#define __INT8_DEFINED__
#define __UINT8_DEFINED__

typedef std::map<std::string, std::string>		DefinesMap;
typedef std::map<std::wstring, std::wstring>	WStringWStringMap;
#define HAS_SEXYCHAR

#if defined(_WIN32) || defined(_WIN64)
#   include <io.h>
#   define mktemp _mktemp
#endif

//JVW -- will include fmod later
//#include "fmod/windows/inc/fmod.h"
//#include "fmod/windows/inc/fmod_errors.h"

//JVW - implementation of wcscasecmp from BSD (free for use)
/*
 * Copyright (C) 2006 Aleksey Cheusov
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee. Permission to modify the code and to distribute modified
 * code is also granted without any restrictions.
 */


inline int wcscasecmp_prime(const wchar_t *s1, const wchar_t *s2)
{
	int lc1  = 0;
	int lc2  = 0;
	int diff = 0;
	
	for (;;) {
		lc1 = towlower(*s1);
		lc2 = towlower(*s2);
		
		diff = lc1 - lc2;
		if (diff)
			return diff;
		
		if (!lc1)
			return 0;
		
		++s1;
		++s2;
	}
}

#define wcscasecmp(s1,s2) wcscasecmp_prime(s1,s2)


inline int wcscasencmp(const wchar_t *s1, const wchar_t *s2, int len)
{
	int lc1  = 0;
	int lc2  = 0;
	int diff = 0;
	
	int c=0;
	while (c<len) {
		lc1 = towlower(*s1);
		lc2 = towlower(*s2);
		
		diff = lc1 - lc2;
		if (diff)
			return diff;
		
		if (!lc1)
			return 0;
		
		++s1;
		++s2;
		c++;
	}
	return 0;
}

inline size_t _mbstowcs ( wchar_t * dest, const char * src, size_t max )
{
	return mbstowcs(dest, src, max);
}

inline size_t _wcstombs ( char * dest, const wchar_t * src, size_t max )
{
	return wcstombs(dest, src, max);
}
// wcscasecmp END

#define alloca _alloca

namespace Sexy
{

inline int32 AtomicIncrement(int32* ioValue) 
{
	return ::InterlockedIncrement((long *) ioValue); 
}

inline int32 AtomicDecrement(int32* ioValue) 
{
	return ::InterlockedDecrement((long *) ioValue); 
}

//#define MemBarrier() ::MemoryBarrier()

// returns true if and only if the set action was successful
inline bool AtomicCompareAndSet( volatile int32* pDestination, int32 newValue, int32 oldValue )
{
	long prevValue = ::InterlockedCompareExchange( (volatile long*)pDestination, newValue, oldValue );
	return ( prevValue == oldValue );
}

// Atomically sets a 32-bit value and returns the old value
inline int32 AtomicSet(volatile int32 * pDestination, int32 newValue )
{
	volatile int32 oldValue;
	for(;;)
	{
		oldValue = *pDestination;
		if ( ::InterlockedCompareExchange( (volatile long*)pDestination, newValue, oldValue ) == oldValue )
		{
			break;
		}
	}

	return oldValue;
}

} // namespace Sexy

#endif //__SEXYAPPFRAMEWORK_WINDOWS_PLATFORM_H__
