#ifndef __SEXYAPPFRAMEWORK_WII_PLATFORM_H_INCLUDED__
#define __SEXYAPPFRAMEWORK_WII_PLATFORM_H_INCLUDED__

#include <revolution.h>
#include "WiiMemory.h"

#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include <wctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>

#define SEXY_DISABLE_MODVAL_LEGACY
#define SUPPORT_SYSFONT
#define SUPPORT_BITMAP_SYSFONT
//standard type definitions

typedef signed long long		int64;
typedef signed long				int32;
typedef signed short			int16;
typedef signed char				int8;
typedef unsigned long long		uint64;
#ifndef _UINT32
typedef unsigned long			uint32;
#endif
typedef unsigned short			uint16;
typedef unsigned char			uint8;


typedef unsigned char			uchar;
typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;

typedef float					float32;
typedef double					float64;

#define _strcmp strcmp
#define _strncmp strncmp
#define _stricmp strcasecmp
#define _wcsicmp wcsicmp
#define _wcsnicmp wcsnicmp
#define wcsnicmp wcscasencmp
#define _stricmp strcasecmp
#define stricmp strcasecmp
#define _strnicmp strncasecmp
#define strnicmp strncasecmp
#define _finite finite

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

//JVW - todo unify message boxes across platforms...
//message box values, 
#define MB_OK	1


template<class T> T max(T a, T b) { return ((a>b)?a:b); }
template<class T> T min(T a, T b) { return ((a<b)?a:b); }

template<class T,class T2> T max(T a, T2 b) { return ((a>b)?a:b); }
template<class T,class T2> T min(T a, T2 b) { return ((a<b)?a:b); }

#define LONG_BIGE_TO_NATIVE(l) (((l >> 24) & 0xFF) | ((l >> 8) & 0xFF00) | ((l << 8) & 0xFF0000) | ((l << 24) & 0xFF000000))
#define WORD_BIGE_TO_NATIVE(w) (((w >> 8) & 0xFF) | ((w << 8) & 0xFF00))
#define LONG_LITTLEE_TO_NATIVE(l) (l)
#define WORD_LITTLEE_TO_NATIVE(w) (w)

#ifndef M_PI
#define M_PI 3.1415926535897932385
#define M_PI_2 M_PI/2
#endif


//__cdecl not supported in cw?
#define __cdecl
//#define _CRTIMP

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
/*

inline int wcscasecmp(const wchar_t *s1, const wchar_t *s2)
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
	return wcstol(str,0,10);
}

inline int _wtof(const wchar_t* str)
{
	return wcstof(str,0);
}

//max path for the filesystem
#define _MAX_PATH PATH_MAX

#define OutputDebugString(x)	fputs(x,stderr)


#include "fmod/macosx/inc/fmod.h"
#include "fmod/macosx/inc/fmod_errors.h"

static inline unsigned short bswap_16(unsigned short x) {
	return (x>>8) | (x<<8);
}

static inline unsigned int bswap_32(unsigned int x) {
	return (bswap_16(x&0xffff)<<16) | (bswap_16(x>>16));
}

static inline unsigned long long bswap_64(unsigned long long x) {
	return (((unsigned long long)bswap_32(x&0xffffffffull))<<32) |
	(bswap_32(x>>32));
}

#define _byteswap_uint64(x) bswap_64(x)
#define _byteswap_ulong(x) bswap_32(x)

#define _itoa(x,y,z) itoa(x,y,z)
*/

#define PLATFORM_BIG_ENDIAN

#define OutputDebugString(x)	OSReport(x)


namespace Sexy
{

inline signed int AtomicIncrement(signed int* ioValue)
{
	signed int tmp;
	asm volatile(
		"1:     lwarx   %0,0,%1\n"
		"	addic   %0,%0,1\n"
		"	stwcx.  %0,0,%1\n"
		"	bne-    1b"
		: "=&r" (tmp)
		: "r" (ioValue)
		: "cc", "memory");
	return tmp;
}

inline signed int AtomicDecrement(signed int* ioValue)
{
	signed int tmp;
	asm volatile(
		"1:     lwarx   %0,0,%1\n"
		"	addic   %0,%0,-1\n"  // addic allows r0, addi doesn't 
		"	stwcx.  %0,0,%1\n"
		"	bne-    1b"
		: "=&r" (tmp)
		: "r" (ioValue)
		: "cc", "memory");
	return tmp;
}

} // namespace Sexy

#endif // __SEXYAPPFRAMEWORK_WII_PLATFORM_H_INCLUDED__
