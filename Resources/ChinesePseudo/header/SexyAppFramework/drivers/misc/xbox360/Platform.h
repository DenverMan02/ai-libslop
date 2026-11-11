#ifndef __SEXYAPPFRAMEWORK_XBOX360_PLATFORM_H__
#define __SEXYAPPFRAMEWORK_XBOX360_PLATFORM_H__

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
#define SEXY_DISABLE_MODVAL_LEGACY
#define SUPPORT_SYSFONT
#define SUPPORT_BITMAP_SYSFONT
#define SUPPORT_EXCEPTIONS
#define SUPPORT_XPRINTF
//#define SUPPORT_LIVELINK

//Xbox file opens are so slow that most games will want this
//#define PAK_ONLY

//#define SUPPORT_SEXY_CACHE

//STL is unplayably slow on the Xbox in Debug
//Going to have to turn off any debugging features it has
#ifdef _HAS_ITERATOR_DEBUGGING
#undef _HAS_ITERATOR_DEBUGGING
#endif
#define _HAS_ITERATOR_DEBUGGING	0

#ifdef _SECURE_SCL
#undef _SECURE_SCL
#endif
#define _SECURE_SCL 0


#include <string>
#include <locale>
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cwctype>

#include <stdarg.h>
#include <assert.h>
#include <xtl.h>

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

#define sexyisspace			isspace

#endif


#define sexytoupper std::toupper
#define sexytolower std::tolower
#define sexytowupper std::towupper
#define sexytowlower std::towlower

#define LONG_BIGE_TO_NATIVE(l) (l)
#define WORD_BIGE_TO_NATIVE(w) (w)
#define LONG_LITTLEE_TO_NATIVE(l) (((l >> 24) & 0xFF) | ((l >> 8) & 0xFF00) | ((l << 8) & 0xFF0000) | ((l << 24) & 0xFF000000))
#define WORD_LITTLEE_TO_NATIVE(w) (((w >> 8) & 0xFF) | ((w << 8) & 0xFF00))

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
typedef __int64 int64;
typedef unsigned __int64 uint64;

typedef float float32;
typedef double float64;


//JVW - todo unify message boxes across platforms...
//message box values, 
#define MB_OK	1

typedef std::map<std::string, std::string>		DefinesMap;
typedef std::map<std::wstring, std::wstring>	WStringWStringMap;

#define PLATFORM_BIG_ENDIAN

inline int32 AtomicIncrement(int32* ioValue) {
	return ::InterlockedIncrement((long *) ioValue); }

inline int32 AtomicDecrement(int32* ioValue) {
	return ::InterlockedDecrement((long *) ioValue); }


#endif //__SEXYAPPFRAMEWORK_XBOX360_PLATFORM_H__
