#ifndef AIRPLAY_PLATFORM_H_INCLUDED
#define AIRPLAY_PLATFORM_H_INCLUDED

#include <strings.h>
#include <wchar.h>
#include <wctype.h>
#include <math.h>
#include <cstdio>
#include <wctype.h>

#include "s3e.h"
#include "s3eTimer.h"

#define SEXY_DISABLE_MODVAL_LEGACY
#define SUPPORT_SYSFONT
#define SUPPORT_BITMAP_SYSFONT
//standard type definitions

typedef signed long long		int64;
//typedef signed long				int32;
typedef signed short			int16;
typedef signed char				int8;
typedef unsigned long long		uint64;
//typedef unsigned long			uint32;
typedef unsigned short			uint16;
typedef unsigned char			uint8;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#define _strcmp strcmp
#define _strncmp strncmp
#define _stricmp strcasecmp
#define _wcsicmp wcscasecmp
#define _wcsnicmp wcscasencmp
#define wcsnicmp wcscasencmp
#define _stricmp strcasecmp
#define stricmp strcasecmp
#define _strnicmp strncasecmp
#define strnicmp strncasecmp
#define _finite finite


#ifndef _USE_WIDE_STRING
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


inline int wcscasecmp(const wchar_t *s1, const wchar_t *s2)
{
	int lc1  = 0;
	int lc2  = 0;
	int diff = 0;
	
	for (;;) {
    // albertb: temporarily mask out hi-word due to bug in Airplay SDK 4.2
		lc1 = towlower(*s1) & 0x0000ff;
		lc2 = towlower(*s2) & 0x0000ff;
		
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

    // albertb: temporarily mask out hi-word due to bug in Airplay SDK 4.2
		lc1 = towlower(*s1) & 0x0000ff;
		lc2 = towlower(*s2) & 0x0000ff;
		
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

inline float _wtof(const wchar_t* str)
{
  // wcstof seems to be missing in SDK 4.2 so swscanf is used instead
  float fValue = 0;
  swscanf(str, L"%f", &fValue);
	return fValue;
}



//max path for the filesystem
#define _MAX_PATH PATH_MAX

#define OutputDebugString(x)	fputs(x,stderr)



#endif
