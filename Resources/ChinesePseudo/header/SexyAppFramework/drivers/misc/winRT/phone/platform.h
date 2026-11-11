/*
*****************************************************************************
*   SCC:Perforce SCM
*
*   $File:$                      
*
*   $Revision:$
*
*   $DateTime:$
*
*   $Author:$
*
*   $Id:$
*
*****************************************************************************
*
* Description: WinRT Phone - Framework Configuration
*
*****************************************************************************
*
* The following text and routines are proprietary and protected by the
* following copyright:
*
* PopCap Games
* 2401 4th Ave, Suite 300
* Seattle, WA 98121
*
*****************************************************************************
*
* History-
*
* 06.23.12 	_SCL_	Initial Version
*
*****************************************************************************
*/

#ifndef __WINRTPHONE_PLATFORM_H__
#define __WINRTPHONE_PLATFORM_H__


//#pragma warning(disable:4786)
//#pragma warning(disable:4503)
//
//#undef _WIN32_WINNT
//#undef WIN32_LEAN_AND_MEAN
//
//#define WIN32_LEAN_AND_MEAN
//#define _WIN32_WINNT 0x0501
//#undef _UNICODE
//#undef UNICODE

// override keyword only supported in VS 2005 and up
#if (!defined(_MSC_VER) || (_MSC_VER < 1400))
	#define override
#endif

#define WINRT_CLUSTER

#define DX_CHECK( expr )	hr = (expr); if( hr != S_OK ) _HALT();

//check off the features the platforms supports
#if	0 	// _SCL_
	#define SUPPORT_SYSFONT
	#define SUPPORT_BITMAP_SYSFONT
	#define SUPPORT_SEXY_CACHE
	#define SUPPORT_SEH_CATCHER
	#define SUPPORT_HTTP
	#define SUPPORT_REF_PEFILES
	#define SUPPORT_XPRINTF
	#define SUPPORT_BASS
	#define SUPPORT_BETA_SUPPORT
	#define SUPPORT_WININET
	#define SUPPORT_EXCEPTIONS
	#define SUPPORT_DIRTY_RECTS
	#define SUPPORT_LIVELINK
	#define SUPPORT_FRAMEWORKCONFIG

	#ifndef RELEASEFINAL
	_#define SUPPORT_AUTOREFLECTION
	#define SUPPORT_PIXELTRACER
	//#define SUPPORT_RADTELEMETRY
	#endif
#else
	#define SUPPORT_REFLECTION
	#define SEXY_DISABLE_MODVAL_LEGACY
	#define SUPPORT_SYSFONT
	#define SUPPORT_BITMAP_SYSFONT
	#define SUPPORT_EXCEPTIONS
	#define SUPPORT_XPRINTF
#endif


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

typedef std::wstring		SexyString;
typedef WCHAR				SexyChar;
#define _S(x)				L ##x


#define sexystrncmp			wcsncmp
#define sexystrnicmp		_wcsnicmp
#define sexystrcmp			wcscmp
#define sexystricmp			_wcsicmp
#define sexysscanf			swscanf
#define sexyatoi			_wtoi
#define sexyatof			_wtof
#define sexystrcpy			wcscpy
#define sexyasctime			_wasctime
#define sexyisspace			iswspace

#define SexyStringToStringFast(x)	WStringToString(x)
#define SexyStringToWStringFast(x)	(x)
#define StringToSexyStringFast(x)	StringToWString(x)
#define WStringToSexyStringFast(x)	(x)

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
#define sexystrnicmp		_strnicmp
#define sexystrcmp			strcmp
#define sexystricmp			_stricmp
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

typedef std::map<std::string, std::string>		DefinesMap;
typedef std::map<std::wstring, std::wstring>	WStringWStringMap;
#define HAS_SEXYCHAR

//JVW -- will include fmod later
//#include "fmod/windows/inc/fmod.h"
//#include "fmod/windows/inc/fmod_errors.h"

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

} // namespace Sexy


//*********************************************************** End of Source *

#endif // __WINRTPHONE_PLATFORM_H__ 

