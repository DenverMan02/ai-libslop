#ifndef SEXYAPPFRAMEWORK_VITA_PLATFORM_H__
#define SEXYAPPFRAMEWORK_VITA_PLATFORM_H__

//check off the features the platforms supports
#define SEXY_DISABLE_MODVAL_LEGACY
#define SUPPORT_SYSFONT
#define SUPPORT_BITMAP_SYSFONT

//#define PLATFORM_BIG_ENDIAN


#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cwctype>

#include <yvals.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include <alloca.h>

#include <stdio.h>
#include <kernel.h>



#ifdef _PROFILE
#include <libsn.h>
#include <libsntuner.h>
#endif

#define __cdecl 
#include "ReflectionTags.h"

#ifdef _USE_WIDE_STRING

typedef std::wstring		SexyString;
typedef wchar_t				SexyChar;
#define _S(x)				L ##x


#define sexystrncmp			wcsncmp
#define sexystrnicmp		wcsnicmp
#define sexystrcmp			wcscmp
#define sexystricmp			_wcsicmp
#define sexysscanf			swscanf
#define sexyatoi			_wtoi
#define sexyatof			_wtof
#define sexystrcpy			wcscpy
#define sexyasctime			_wasctime

#define SexyStringToStringFast(x)	WStringToString(x)
#define SexyStringToWStringFast(x)	(x)
#define StringToSexyStringFast(x)	StringToWString(x)
#define WStringToSexyStringFast(x)	(x)


#else

typedef std::string			SexyString;
typedef char				SexyChar;
#define _S(x)				x


#define sexystrncmp			strncmp
#define sexystrnicmp		strnicmp
#define sexystrcmp			strcmp
#define sexystricmp			stricmp
#define sexysscanf			sscanf
#define sexyatoi			atoi
#define sexyatof			atof
#define sexystrcpy			strcpy
#define sexyasctime			asctime

#define SexyStringToStringFast(x)	(x)
#define SexyStringToWStringFast(x)	StringToWString(x)
#define StringToSexyStringFast(x)	(x)
#define WStringToSexyStringFast(x)	WStringToString(x)

#endif

#define sexytoupper std::toupper
#define sexytolower std::tolower
#define sexytowupper std::towupper
#define sexytowlower std::towlower

inline float max(float a, float b) { return ((a>b)?a:b); }
inline double max(float a, double b) { return ((a>b)?a:b); }
inline float min(float a, float b) { return ((a<b)?a:b); }
inline double min(float a, double b) { return ((a<b)?a:b); }

inline double max(double a, float b) { return ((a>b)?a:b); }
inline double max(double a, double b) { return ((a>b)?a:b); }
inline double min(double a, float b) { return ((a<b)?a:b); }
inline double min(double a, double b) { return ((a<b)?a:b); }

template<class T> float max(T a, float b) { return ((a>b)?a:b); }
template<class T> double max(T a, double b) { return ((a>b)?a:b); }
template<class T> float min(T a, float b) { return ((a<b)?a:b); }
template<class T> double min(T a, double b) { return ((a<b)?a:b); }


template<class T> T max(T a, T b) { return ((a>b)?a:b); }
template<class T> T min(T a, T b) { return ((a<b)?a:b); }


template<class T,class T2> T max(T a, T2 b) { return ((a>b)?a:b); }
template<class T,class T2> T min(T a, T2 b) { return ((a<b)?a:b); }

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

//JVW - todo unify message boxes across platforms...
//message box values, 
#define MB_OK	1

typedef std::map<std::string, std::string>		DefinesMap;
typedef std::map<std::wstring, std::wstring>	WStringWStringMap;

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

inline float _wtof(const wchar_t* str)
{
	return wcstof(str,0);
}

//max path for the filesystem
//I haven't found the define for this yet...
#define _MAX_PATH 1024

#define OutputDebugString(x) printf(x)

typedef void* HWND;
#define _alloca alloca

#endif
