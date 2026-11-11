#ifndef ANDROID_PLATFORM_H_INCLUDED
#define ANDROID_PLATFORM_H_INCLUDED

#include <strings.h>
#include <cwchar>
#include <sys/cdefs.h>
#include <cwctype>
#include <cmath>
#include <cctype>
#include <cwctype>
#include <algorithm>	// min/max
#include <vector>

#if !defined(__aarch64__)
#include <sys/atomics.h>
#endif

#include <cstdint>

#ifndef __has_feature
#define __has_feature(feature) 0
#endif

#define SUPPORT_SYSFONT
#define SUPPORT_BITMAP_SYSFONT
#define SUPPORT_XPRINTF
#if __has_feature(cxx_exceptions)
//	#define SUPPORT_EXCEPTIONS
#endif
//#define SUPPORT_FACEBOOK
#ifndef SUPPORT_REFLECTION
#define SUPPORT_REFLECTION
#endif
#define SUPPORT_LIVELINK
#define SUPPORT_FRAMEWORKCONFIG
#define SUPPORT_WWISE
//#define SUPPORT_GOOGLEPLAY_EXPANSION
//#define SUPPORT_DRAPER_LOCAL_NOTES
//#define SUPPORT_HASOFFERS

//PVZ2_CHINESE_BEGIN
#define SUPPORT_WECHAT
//#define SUPPORT_SCREEN_STRETCH
#define SUPPORT_SCREEN_SCALE
//PVZ2_CHINESE_END

//standard type definitions

using int64 = int64_t;
using int32 = int32_t;
using int16 = int16_t;
using int8 = int8_t;

using uint64 = uint64_t;
using uint32 = uint32_t;
using uint16 = uint16_t;
using uint8 = uint8_t;

// why do we have byte and uint8?
using byte = unsigned char;
// gotta save them characters
using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;

using float32 = float;
using float64 = double;

#define _INT32

// include MinMax *after* we have defined int64 and uint64.
#include "MinMax.h"

#define _strcmp strcmp
#define _strncmp strncmp
#define _stricmp strcasecmp
#define _wcsicmp wcscasecmp
#define wcsicmp wcscasecmp
#define _wcsnicmp wcscasencmp
#define wcsnicmp wcscasencmp
#define _stricmp strcasecmp
#define stricmp strcasecmp
#define _strnicmp strncasecmp
#define strnicmp strncasecmp
#define _finite finite

//todo fix the mappings here...
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

#else

#define sexystrncmp			_strncmp
#define sexystrnicmp		_strnicmp
#define sexystrcmp			_strcmp
#define sexystricmp			_stricmp
#define sexysscanf			sscanf
#define sexyatoi			atoi
#define sexyatof			atof
#define sexystrcpy			strcpy
#define sexyasctime			asctime


#endif

#define sexytoupper ((int(*)(int))std::toupper)
#define sexytolower ((int(*)(int))std::tolower)
#define sexytowupper std::towupper
#define sexytowlower std::towlower


//JVW - todo unify message boxes across platforms...
//message box values,
#define MB_OK	1

#define LONG_BIGE_TO_NATIVE(l) (((l >> 24) & 0xFF) | ((l >> 8) & 0xFF00) | ((l << 8) & 0xFF0000) | ((l << 24) & 0xFF000000))
#define WORD_BIGE_TO_NATIVE(w) (((w >> 8) & 0xFF) | ((w << 8) & 0xFF00))
#define LONG_LITTLEE_TO_NATIVE(l) (l)
#define WORD_LITTLEE_TO_NATIVE(w) (w)


//__cdecl not supported in gcc
#define __cdecl
#define _CRTIMP

#define strncpy_s(str1,len1,str2,len2) strncpy(str1,str2,len1)


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
	return 0;
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


inline int _wtoi(const wchar_t* str)
{
	if (!str) {
		return 0;
	}
	int length = wcslen(str);
	if (!length)
		return 0;
	std::vector<char>buffer(str, str+length+1);
	return strtol(&buffer[0], 0, 10);
}

inline float _wtof(const wchar_t* str)
{
    //	return wcstof(str,0);
    // wcstof seems to be missing in SDK 4.2 so swscanf is used instead
    float fValue = 0;
    swscanf(str, L"%f", &fValue);
    return fValue;
}

inline size_t _mbstowcs ( wchar_t * dest, const char * src, size_t max )
{
	if (NULL == src)
		return 0;
	size_t count = 0;
	while (count < max)
	{
		if (dest)
			*(dest + count) = *(src + count);
		if( '\0' == *(src + count))
			return count + 1;
		++count;
	}
	return count;
}

inline size_t _wcstombs ( char * dest, const wchar_t * src, size_t max )
{
	if (NULL == src)
		return 0;
	size_t count = 0;
	while (count < max)
	{
		if (dest)
			*(dest + count) = *(src + count);
		if( '\0' == *(src + count))
			return count + 1;
		++count;
	}
	return count;
}

//max path for the filesystem
#define _MAX_PATH PATH_MAX

#define OutputDebugString(x)	fputs(x,stderr)
typedef void* HWND;
#define _alloca alloca

static inline unsigned short bswap_16(unsigned short x)
{
	return (x>>8) | (x<<8);
}

static inline unsigned int bswap_32(unsigned int x)
{
	return (bswap_16(x&0xffff)<<16) | (bswap_16(x>>16));
}

static inline unsigned long long bswap_64(unsigned long long x)
{
	return (((unsigned long long)bswap_32(x&0xffffffffull))<<32) |
	(bswap_32(x>>32));
}

#define _abs64(x) llabs(x)

#define _byteswap_uint64(x) bswap_64(x)
#define _byteswap_ulong(x) bswap_32(x)



//#define _fcvt(x,y,z,w) fcvt(x,y,z,w)
//#define _ecvt(x,y,z,w) ecvt(x,y,z,w)


namespace Sexy
{
#if defined(__aarch64__)

inline int __atomic_inc_ex(volatile int *ptr)
{
  return __sync_fetch_and_add (ptr, 1);
}

inline int __atomic_dec_ex(volatile int *ptr)
{
  return __sync_fetch_and_sub (ptr, 1);
}

inline signed int AtomicIncrement(int32* ioValue)
{
	return __atomic_inc_ex((volatile int32_t*)ioValue);
}

inline signed int AtomicDecrement(int32* ioValue)
{
	return __atomic_dec_ex((volatile int32_t*)ioValue);
}

inline int __atomic_cmpxchg_ex(int old, int _new, volatile int *ptr)
{
    /* We must return 0 on success */
    return __sync_val_compare_and_swap(ptr, old, _new) != old;
}

inline bool AtomicCompareAndSet( volatile int32* pDestination, int32 newValue, int32 oldValue )
{
	//return __sync_bool_compare_and_swap((volatile int32_t*)pDestination, oldValue, newValue);
	return !__atomic_cmpxchg_ex( oldValue, newValue, (volatile int32_t*)pDestination );
}

inline int __atomic_swap_ex(int _new, volatile int *ptr)
{
    int prev;
    do {
        prev = *ptr;
    } while (__sync_val_compare_and_swap(ptr, prev, _new) != prev);
    return prev;
}

inline int AtomicSet(volatile int32 * pDestination, int32 newValue )
{
	//return __sync_lock_test_and_set((volatile int32_t*)pDestination, newValue);
	return __atomic_swap_ex( newValue, (volatile int32_t*)pDestination );
}

#else

inline signed int AtomicIncrement(int32* ioValue)
{
	return __atomic_inc((volatile int32_t*)ioValue);
}

inline signed int AtomicDecrement(int32* ioValue)
{
	return __atomic_dec((volatile int32_t*)ioValue);
}

// returns true if and only if the set action was successful
inline bool AtomicCompareAndSet( volatile int32* pDestination, int32 newValue, int32 oldValue )
{
	return !__atomic_cmpxchg( oldValue, newValue, (volatile int32_t*)pDestination );
}

// Atomically sets a 32-bit value and returns the old value
inline int32 AtomicSet(volatile int32 * pDestination, int32 newValue )
{
	return __atomic_swap( newValue, (volatile int32_t*)pDestination );
}

#endif
} // namespace Sexy



#endif
