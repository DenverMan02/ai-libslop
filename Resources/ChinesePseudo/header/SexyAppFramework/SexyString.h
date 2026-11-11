#ifndef SEXY_STRING_H_INCLUDED
#define SEXY_STRING_H_INCLUDED

#include <string>
#include <algorithm>
#include <cctype>
#include <cwctype>
#include <sstream>


/*!
	SexyString type definition and string utilities.  Many more functions in common.h could come over here, but that's a bigger project.

	Platforms must define the following functions for both ascii or wide characters depending on _USE_WIDE_STRING.

	#define sexystrncmp
	#define sexystrnicmp
	#define sexystrcmp
	#define sexystricmp
	#define sexysscanf
	#define sexyatoi
	#define sexyatof
	#define sexystrcpy
	#define sexyasctime

	Note that SexyString is *not* in the Sexy namespace for historical reasons.
*/

// The android sdk defines _S for its own internal use.
// They should be undef'ing it after they are done but they don't.
// We we undef it here.
#if defined(HOST_ANDROID) && defined(_S)
	#undef _S
#endif

#ifdef _USE_WIDE_STRING

typedef std::wstring		SexyString;
typedef wchar_t				SexyChar;
typedef std::wstringstream	SexyStringStream;

#define _S(x)				L ##x
#ifdef SUPPORT_XPRINTF
#define PRIxSEXY			"s"
#else
#define PRIxSEXY			"ls"
#endif
#define TO_SEXYSTRING(x) std::to_wstring(x)

#define SexyStringToStringFast(x)	WStringToString(x)
#define SexyStringToWStringFast(x)	(x)
#define StringToSexyStringFast(x)	UTF8StringToWString(x)
#define WStringToSexyStringFast(x)	(x)

#else

typedef std::string			SexyString;
typedef char				SexyChar;
typedef std::stringstream	SexyStringStream;
#define _S(x)				x
#define PRIxSEXY			"s"
#define TO_SEXYSTRING(x) std::to_string(x)

#define SexyStringToStringFast(x)	(x)
#define SexyStringToWStringFast(x)	StringToWString(x)
#define StringToSexyStringFast(x)	(x)
#define WStringToSexyStringFast(x)	WStringToString(x)

#endif

#endif //SEXY_STRING_H_INCLUDED
