#ifndef __SEXYAPPFRAMEWORK_COMMON_H__
#define __SEXYAPPFRAMEWORK_COMMON_H__

#include <string>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>

//--------------------------------------------------------------------------
// Build/configuration macros
//--------------------------------------------------------------------------

//	Build kinds

// These assume that several #defines are set by the build script/vcproj on
// the compiler command line, depending on target configuration.

#if defined(NDEBUG)
#	define SEXY_IS_BUILD_RELEASE (1)
#	define SEXY_IS_BUILD_DEBUG (0)
#	define SEXY_BUILD_MODE_NAME "Release"
#elif defined(_DEBUG)
#	define SEXY_IS_BUILD_RELEASE (0)
#	define SEXY_IS_BUILD_DEBUG (1)
#	define SEXY_BUILD_MODE_NAME "Debug"
#elif defined(_DEBUG_OPT)
#	define SEXY_IS_BUILD_RELEASE (0)
#	define SEXY_IS_BUILD_DEBUG (1)
#	define SEXY_BUILD_MODE_NAME "Debug - Optimized"
#else
#	error Unexpected build type
#endif

#define PRIME_SAFE_MACRO_BEGIN() do {
#define PRIME_SAFE_MACRO_END() } while (0);
#define PRIME_SAFE_MACRO_UNIMPLEMENTED() PRIME_SAFE_MACRO_BEGIN() PRIME_SAFE_MACRO_END()

#define PRIME_UNUSED_PARAM(...) ((void)(__VA_ARGS__))

#include "PlatformAutodetect.h"

#ifdef SUPPORT_FRAMEWORKCONFIG
#include "../SexyAppFrameworkConfig/FrameworkConfig.h"
#endif // SUPPORT_FRAMEWORKCONFIG

#include "PlatformExceptions.h"
#include "CommonDefines.h"

#include "SexyString.h"

#include "EnumUtils.h"
#include "Reporting.h"
#include "ReflectionTags.h"
#include <random>

typedef std::map<std::string, std::string>		DefinesMap;
typedef std::map<std::wstring, std::wstring>	WStringWStringMap;

#define LENGTH(anyarray) (sizeof(anyarray) / sizeof(anyarray[0]))

#include "SexyLocale.h"


#if defined HOST_MACOSX || defined HOST_IPHONEOS || defined HOST_ANDROID
#include <unistd.h> // for usleep
#endif



namespace Sexy
{

const ulong SEXY_RAND_MAX = 0x7FFFFFFF;

extern bool			gDebug;

	//creating a Sexy::FileTime for prime,
	// it is unix time basically
	typedef uint64 FileTime;

	#ifdef HOST_WINDOWS
		typedef std::mt19937 RandEngineType;
	#else
		using RandEngineType = std::mt19937;
	#endif
    
#ifdef HOST_WINDOWS
//JVW - move this into the windows drivers
extern HINSTANCE	gHInstance;
#endif
int					Rand();
RandEngineType&		GetRandEngine();    
int					Rand(int range);
float				Rand(float range);
void				SRand(ulong theSeed);
extern std::string	vformat(const char* fmt, va_list argPtr);
extern std::wstring	vformat(const wchar_t* fmt, va_list argPtr);
extern std::string	StrFormat(const char* fmt ...);
extern std::wstring	StrFormat(const wchar_t* fmt ...);
void				OutputDebugStrF(const char* fmt ...);
void				OutputDebugStrF(const wchar_t* fmt ...);
	
#ifdef HOST_WINDOWS
//JVW - move these into windows drivers
bool				CheckFor98Mill();
bool				CheckForVista();
bool				CheckForWin7();
#endif
	
void				GetProcessorInfoStrings(std::vector<std::string>& outStrings);
	

// This is used in functions that take a length param. Use this in those to
// auto-detect the length using strlen/wcslen. Use a magic number other than -1
// to catch errors where people have off-by-one errors so we won't have it get
// interpreted as a detect-length.
//
const int32 SEXY_STR_DETECT_LEN = -1111;


//JVW - prime needs a framework for loading and saving 
// save game data.  AppDataFolder doesn't cut it for consoles
std::string			GetAppDataFolder();
void				SetAppDataFolder(const std::string& thePath);
std::string			URLEncode(const std::string& theString);
std::string			StringToUpper(const std::string& theString);
std::wstring		StringToUpper(const std::wstring& theString);
std::string			StringToLower(const std::string& theString);
std::wstring		StringToLower(const std::wstring& theString);
std::wstring		StringToWString(const std::string &theString);
std::string			WStringToString(const std::wstring &theString, bool* isValid = NULL);

inline char 		WCharToChar(wchar_t inWChar)
{
#if SEXY_IS_BUILD_DEBUG
	if (inWChar < 256)
	{
		PRIME_WARN("WCharToChar() was passed a wchar_t that was larger than 256.");
	}
#endif // SEXY_IS_BUILD_DEBUG

	return (char)(inWChar & 0xFF);
}

int					GetNextUTF8CharFromStream(const char** theBuffer, int theLen, wchar_t* theChar);
std::string			WStringToUTF8String(const std::wstring &theString);
std::wstring		UTF8StringToWString(const std::string &theString);
SexyString			StringToSexyString(const std::string& theString);
SexyString			WStringToSexyString(const std::wstring& theString);
SexyString          UTF8StringToSexyString(const std::string& theString);
std::string			SexyStringToString(const SexyString& theString);
std::wstring		SexyStringToWString(const SexyString& theString);
std::string			SexyStringToUTF8String(const SexyString& theString);
std::string			ToString(const std::string& theString);
std::string			ToString(const std::wstring& theString);
std::wstring		ToWString(const std::string& theString);
std::wstring		ToWString(const std::wstring& theString);
SexyString			ToSexyString(const std::string& theString);
SexyString			ToSexyString(const std::wstring& theString);
std::string			Upper(const std::string& theData);
std::wstring		Upper(const std::wstring& theData);
std::string			Lower(const std::string& theData);
std::wstring		Lower(const std::wstring& theData);
std::string			Trim(const std::string& theString);
std::wstring		Trim(const std::wstring& theString);

//
// String parsing for primative types (bool, int, int64, double)
//

bool				StringToBool(const char* inStrToParse, bool* outBoolVal);
bool				StringToInt(const char* inStrToParse, int32* outIntVal);
bool				StringToInt64(const char* inStrToParse, int64* outInt64Val);
bool				StringToDouble(const char* inStrToParse, double* outDoubleVal);

bool				StringToBool(const wchar_t* inStrToParse, bool* outBoolVal);
bool				StringToInt(const wchar_t* inStrToParse, int32* outIntVal);
bool				StringToInt64(const wchar_t* inStrToParse, int64* outInt64Val);
bool				StringToDouble(const wchar_t* inStrToParse, double* outDoubleVal);

inline bool			StringToBool(const std::string& inStrToParse, bool* outBoolVal) { return StringToBool(inStrToParse.c_str(), outBoolVal); }
inline bool			StringToInt(const std::string& inStrToParse, int32* outIntVal) { return StringToInt(inStrToParse.c_str(), outIntVal); }
inline bool			StringToInt64(const std::string& inStrToParse, int64* outInt64Val) { return StringToInt64(inStrToParse.c_str(), outInt64Val); }
inline bool			StringToDouble(const std::string& inStrToParse, double* outDoubleVal) { return StringToDouble(inStrToParse.c_str(), outDoubleVal); }

inline bool			StringToBool(const std::wstring& inStrToParse, bool* outBoolVal) { return StringToBool(inStrToParse.c_str(), outBoolVal); }
inline bool			StringToInt(const std::wstring& inStrToParse, int32* outIntVal) { return StringToInt(inStrToParse.c_str(), outIntVal); }
inline bool			StringToInt64(const std::wstring& inStrToParse, int64* outInt64Val) { return StringToInt64(inStrToParse.c_str(), outInt64Val); }
inline bool			StringToDouble(const std::wstring& inStrToParse, double* outDoubleVal) { return StringToDouble(inStrToParse.c_str(), outDoubleVal); }


int					StrFindNoCase(const char *theStr, const char *theFind);
bool				StrPrefixNoCase(const char *theStr, const char *thePrefix, int maxLength = 10000000);
SexyString			CommaSeparate(int theValue);
SexyString			UCommaSeparate(unsigned int theValue);
SexyString			CommaSeparate64(int64 theValue);
SexyString			UCommaSeparate64(uint64 theValue);
std::string			Evaluate(const std::string& theString, const DefinesMap& theDefinesMap);
std::string			XMLDecodeString(const std::string& theString);
std::string			XMLEncodeString(const std::string& theString);
std::wstring		XMLDecodeString(const std::wstring& theString);
std::wstring		XMLEncodeString(const std::wstring& theString);
bool				WriteUTF8XMLFile(FILE* fp, const std::wstring& theData, bool includePreamble = true);

bool				Deltree(const std::string& thePath);
bool				FileExists(const std::string& theFileName, bool *isFolder = NULL);
bool				FileExists(const std::wstring& theFileName, bool *isFolder = NULL);
std::string			GetAppFullPath(const std::string& theAppRelPath);
void				MkDir(const std::string& theDir);
void				MkDir(const std::wstring& theDir);

std::string			GetFileName(const std::string& thePath, bool noExtension = false);
std::wstring		GetFileName(const std::wstring& thePath, bool noExtension = false);

// Returns NULL if there is no filename in the path.
const char*			GetFileName(const char* inPath);
const wchar_t*		GetFileName(const wchar_t* inPath);

// Same as GetFileName() but never returns NULL. Will return "" in those cases instead.
const char*			GetFileNameSafe(const char* inPath); 
const wchar_t*		GetFileNameSafe(const wchar_t* inPath);

std::string         GetFileExt(std::string& inPath, bool withPeriod = true);
std::wstring        GetFileExt(std::wstring& inPath, bool withPeriod = true);
const SexyString    GetFileExt(const SexyString& theFileName, bool withPeriod = true);
std::string			GetFileDir(const std::string& thePath, bool withSlash = false);
std::wstring		GetFileDir(const std::wstring& thePath, bool withSlash = false);
std::string			RemoveTrailingSlash(const std::string& theDirectory);
std::wstring		RemoveTrailingSlash(const std::wstring& theDirectory);
std::string			AddTrailingSlash(const std::string& theDirectory, bool backSlash = false);
std::wstring		AddTrailingSlash(const std::wstring& theDirectory, bool backSlash = false);
FileTime			GetFileDate(const std::string& theFileName);
FileTime			GetFileDate(const std::wstring& theFileName);
std::string			GetCurDir();
std::string			GetFullPath(const std::string& theRelPath);
std::wstring		GetFullPath(const std::wstring& theRelPath);
std::string			GetPathFrom(const std::string& theRelPath, const std::string& theDir);
std::wstring		GetPathFrom(const std::wstring& theRelPath, const std::wstring& theDir);
bool				AllowAllAccess(const std::string& theFileName);

#if defined(HOST_WINDOWS) || defined(HOST_MACOSX)
void				InitXprintf();
#endif

time_t 				GetTimegm(struct tm *tm);
time_t 				GetBJTimeOffset();

inline void			inlineUpper(std::string &theData)
{
    std::transform(theData.begin(), theData.end(), theData.begin(), sexytoupper);
}

inline void			inlineUpper(std::wstring &theData)
{
    std::transform(theData.begin(), theData.end(), theData.begin(), sexytowupper);
}

inline void			inlineLower(std::string &theData)
{
    std::transform(theData.begin(), theData.end(), theData.begin(), sexytolower);
}

inline void			inlineLower(std::wstring &theData)
{
    std::transform(theData.begin(), theData.end(), theData.begin(), sexytowlower);
}

inline void			inlineLTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
    theData.erase(0, theData.find_first_not_of(theChars));
}

inline void			inlineLTrim(std::wstring &theData, const std::wstring& theChars = L" \t\r\n")
{
    theData.erase(0, theData.find_first_not_of(theChars));
}


inline void			inlineRTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
    theData.resize(theData.find_last_not_of(theChars) + 1);
}

inline void			inlineRTrim(std::wstring &theData, const std::wstring& theChars = L" \t\r\n")
{
	theData.resize(theData.find_last_not_of(theChars) + 1);
}

inline void			inlineTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
	inlineRTrim(theData, theChars);
	inlineLTrim(theData, theChars);
}

inline void			inlineTrim(std::wstring &theData, const std::wstring& theChars = L" \t\r\n")
{
	inlineRTrim(theData, theChars);
	inlineLTrim(theData, theChars);
}

//
// String comparision functions
//

inline bool StringLess(const char* inStrA, const char* inStrB) { return strcmp(inStrA, inStrB) < 0; }
inline bool StringLess(const wchar_t* inStrA, const wchar_t* inStrB) { return wcscmp(inStrA, inStrB) < 0; }
inline bool StringLess(const std::string& inStrA, const std::string& inStrB) { return StringLess(inStrA.c_str(), inStrB.c_str()); }
inline bool StringLess(const std::wstring& inStrA, const std::wstring& inStrB) { return StringLess(inStrA.c_str(), inStrB.c_str()); }

inline bool StringLessNoCase(const char* inStrA, const char* inStrB) { return _stricmp(inStrA, inStrB) < 0; }
inline bool StringLessNoCase(const wchar_t* inStrA, const wchar_t* inStrB) { return _wcsicmp(inStrA, inStrB) < 0; }
inline bool StringLessNoCase(const std::string& inStrA, const std::string& inStrB) { return StringLessNoCase(inStrA.c_str(), inStrB.c_str()); }
inline bool StringLessNoCase(const std::wstring& inStrA, const std::wstring& inStrB) { return StringLessNoCase(inStrA.c_str(), inStrB.c_str()); }

inline bool StringEqual(const char* inStrA, const char* inStrB) { return strcmp(inStrA, inStrB) == 0; }
inline bool StringEqual(const wchar_t* inStrA, const wchar_t* inStrB) { return wcscmp(inStrA, inStrB) == 0; }
inline bool StringEqual(const std::string& inStrA, const std::string& inStrB) { return StringEqual(inStrA.c_str(), inStrB.c_str()); }
inline bool StringEqual(const std::wstring& inStrA, const std::wstring& inStrB) { return StringEqual(inStrA.c_str(), inStrB.c_str()); }

inline bool StringEqualNoCase(const char* inStrA, const char* inStrB) {	return _stricmp(inStrA, inStrB) == 0; }
inline bool StringEqualNoCase(const wchar_t* inStrA, const wchar_t* inStrB) { return _wcsicmp(inStrA, inStrB) == 0; }
inline bool StringEqualNoCase(const std::string& inStrA, const std::string& inStrB) { return StringEqualNoCase(inStrA.c_str(), inStrB.c_str()); }
inline bool StringEqualNoCase(const std::wstring& inStrA, const std::wstring& inStrB) { return StringEqualNoCase(inStrA.c_str(), inStrB.c_str()); }

inline bool StringGreater(const char* inStrA, const char* inStrB) { return strcmp(inStrA, inStrB) > 0; }
inline bool StringGreater(const wchar_t* inStrA, const wchar_t* inStrB) { return wcscmp(inStrA, inStrB) > 0; }
inline bool StringGreater(const std::string& inStrA, const std::string& inStrB) { return StringGreater(inStrA.c_str(), inStrB.c_str()); }
inline bool StringGreater(const std::wstring& inStrA, const std::wstring& inStrB) { return StringGreater(inStrA.c_str(), inStrB.c_str()); }

inline bool StringGreaterNoCase(const char* inStrA, const char* inStrB) { return _stricmp(inStrA, inStrB) > 0; }
inline bool StringGreaterNoCase(const wchar_t* inStrA, const wchar_t* inStrB) { return _wcsicmp(inStrA, inStrB) > 0; }
inline bool StringGreaterNoCase(const std::string& inStrA, const std::string& inStrB) { return StringGreaterNoCase(inStrA.c_str(), inStrB.c_str()); }
inline bool StringGreaterNoCase(const std::wstring& inStrA, const std::wstring& inStrB) { return StringGreaterNoCase(inStrA.c_str(), inStrB.c_str()); }


//
// String comparision functors
//

struct StringLessFunctor { bool operator()(const std::string& inStrA, const std::string& inStrB) const { return StringLess(inStrA, inStrB); } };
struct StringEqualFunctor { bool operator()(const std::string& inStrA, const std::string& inStrB) const { return StringEqual(inStrA, inStrB); } };
struct StringGreaterFunctor { bool operator()(const std::string& inStrA, const std::string& inStrB) const { return StringGreater(inStrA, inStrB); } };
struct StringLessNoCaseFunctor { bool operator()(const std::string& inStrA, const std::string& inStrB) const { return StringLessNoCase(inStrA, inStrB); } };
struct StringEqualNoCaseFunctor { bool operator()(const std::string& inStrA, const std::string& inStrB) const { return StringEqualNoCase(inStrA, inStrB); } };
struct StringGreaterNoCaseFunctor { bool operator()(const std::string& inStrA, const std::string& inStrB) const { return StringGreaterNoCase(inStrA, inStrB); } };

struct WStringLessFunctor { bool operator()(const std::wstring& inStrA, const std::wstring& inStrB) const { return StringLess(inStrA, inStrB); } };
struct WStringEqualFunctor { bool operator()(const std::wstring& inStrA, const std::wstring& inStrB) const { return StringEqual(inStrA, inStrB); } };
struct WStringGreaterFunctor { bool operator()(const std::wstring& inStrA, const std::wstring& inStrB) const { return StringGreater(inStrA, inStrB); } };
struct WStringLessNoCaseFunctor { bool operator()(const std::wstring& inStrA, const std::wstring& inStrB) const { return StringLessNoCase(inStrA, inStrB); } };
struct WStringEqualNoCaseFunctor { bool operator()(const std::wstring& inStrA, const std::wstring& inStrB) const { return StringEqualNoCase(inStrA, inStrB); } };
struct WStringGreaterNoCaseFunctor { bool operator()(const std::wstring& inStrA, const std::wstring& inStrB) const { return StringGreaterNoCase(inStrA, inStrB); } };

#ifdef _USE_WIDE_STRING
typedef WStringLessFunctor SexyStringLessFunctor;
typedef WStringEqualFunctor SexyStringEqualFunctor;
typedef WStringGreaterFunctor SexyStringGreaterFunctor;
typedef WStringLessNoCaseFunctor SexyStringLessNoCaseFunctor;
typedef WStringEqualNoCaseFunctor SexyStringEqualNoCaseFunctor;
typedef WStringGreaterNoCaseFunctor SexyStringGreaterNoCaseFunctor;
#else
typedef StringLessFunctor SexyStringLessFunctor;
typedef StringEqualFunctor SexyStringEqualFunctor;
typedef StringGreaterFunctor SexyStringGreaterFunctor;
typedef StringLessNoCaseFunctor SexyStringLessNoCaseFunctor;
typedef StringEqualNoCaseFunctor SexyStringEqualNoCaseFunctor;
typedef StringGreaterNoCaseFunctor SexyStringGreaterNoCaseFunctor;
#endif


template<typename CHAR_TYPE> CHAR_TYPE GetStringTerminator();
template<> inline char		GetStringTerminator<char>() { return '\0'; }
template<> inline wchar_t	GetStringTerminator<wchar_t>() { return L'\0'; }

template<typename CHAR_TYPE> const CHAR_TYPE* GetEmptyString();
template<> inline const char*		GetEmptyString<char>() { return ""; }
template<> inline const wchar_t*	GetEmptyString<wchar_t>() { return L""; }

// Returns length of string (number of characters not bytes)
inline int StringLength(const std::string& inStr) {	return (int)inStr.length(); }
inline int StringLength(const std::wstring& inStr) { return (int)inStr.length(); }
inline int StringLength(const wchar_t* inStr) {	return (int)::wcslen(inStr); }
inline int StringLength(const char* inStr) { return (int)::strlen(inStr); }

inline bool StringNullOrEmpty(const std::string& inStr) { return inStr.empty(); }
inline bool StringNullOrEmpty(const std::wstring& inStr) { return inStr.empty(); }
inline bool StringNullOrEmpty(const wchar_t* inStr) { return (inStr == NULL) || (*inStr == L'\0'); }
inline bool StringNullOrEmpty(const char* inStr) { return (inStr == NULL) || (*inStr == '\0'); }

// $ These are "safe" versions of the equivalent C lib functions which we're
//   disabling to guarantee no buffer overruns.

// use in place of strcpy, strncpy
//
char* StringCopy(char* outDest, size_t inDestSizeChars, const char* inSrc, int32 inNumCharsToCopy = SEXY_STR_DETECT_LEN);
wchar_t* StringCopy(wchar_t* outDest, size_t inDestSizeChars, const wchar_t* inSrc, int32 inNumCharsToCopy = SEXY_STR_DETECT_LEN);

// $ These special versions auto-detect the size of the buffer you're writing
//   to, if they're statically sized (which is 99% of the time).

template <size_t SIZE>
inline char* StringCopy(char (&outDest)[SIZE], const char* inSrc, int32 inNumCharsToCopy = SEXY_STR_DETECT_LEN) 
{
	return StringCopy(outDest, SIZE, inSrc, inNumCharsToCopy); 
}

template <size_t SIZE>
inline wchar_t* StringCopy(wchar_t (&outDest)[SIZE], const wchar_t* inSrc, int32 inNumCharsToCopy = SEXY_STR_DETECT_LEN) 
{
	return StringCopy(outDest, SIZE, inSrc, inNumCharsToCopy); 
}

// This returns a pointer to the first char in the string that is within the
// subset passed in as the second arg. This is better than strcspn for small
// strings (strcspn builds a LUT). Returns NULL if no match.
//
const char* StringFindAnyOfWithCase(const char* inStrToTest, const char* inCharsToLookFor);
const char* StringFindAnyOfWithCase(const char* inStrToTest, const std::string& inCharsToLookFor);
const std::string StringFindAnyOfWithCase(const std::string& inStrToTest, const std::string& inCharsToLookFor);
const wchar_t* StringFindAnyOfWithCase(const wchar_t* inStrToTest, const wchar_t* inCharsToLookFor);
const wchar_t* StringFindAnyOfWithCase(const wchar_t* inStrToTest, const std::wstring& inCharsToLookFor);
const std::wstring StringFindAnyOfWithCase(const std::wstring& inStrToTest, const std::wstring& inCharsToLookFor);

// Same except searches in reverse.
//
const char* StringReverseFindAnyOfWithCase(const char* inStrToTest, const char* inCharsToLookFor);
const wchar_t* StringReverseFindAnyOfWithCase(const wchar_t* inStrToTest, const wchar_t* inCharsToLookFor);

// Checking if a string matches a wildcard mask
bool StringWildcardMatches(const std::string& inWildcard, const std::string& inCheckStr, bool inCheckStrHasImplicitStarSuffix = false);
bool StringWildcardMatches(const std::wstring& inWildcard, const std::wstring& inCheckStr, bool inCheckStrHasImplicitStarSuffix = false);

//
// String conversion structs for use in templates
//


struct CharToCharFunc
{
	static const char* Str(const char* inStr) {	return inStr; }
	static char Char(char inChar) { return inChar; }
};

struct WCharToWCharFunc
{
	static const wchar_t* Str(const wchar_t* inStr)	{ return inStr;	}
	static wchar_t Char(wchar_t inChar)	{ return inChar; }
};

struct CharToWCharFunc
{
	static const std::wstring Str(const char* inStr) { return StringToWString(inStr); }
	static wchar_t Char(char inChar) { return (wchar_t)inChar; }
};


struct WCharToCharFunc
{
	static const std::string Str(const wchar_t* inStr) { return WStringToString(inStr);	}
	static char Char(wchar_t inChar) { return WCharToChar(inChar); }
};

// 
// Templatized string/wstring conversion structs
//

template<typename TO_CHAR_TYPE> struct CharConv;

template<>
struct CharConv<char>
{
	typedef std::string StringType;
	
	static char Char(char inChar) { return CharToCharFunc::Char(inChar); }
	static std::string Str(const char* inStr) { return CharToCharFunc::Str(inStr); }
	static std::string Str(const std::string& inStr) { return CharToCharFunc::Str(inStr.c_str()); }

	static char Char(wchar_t inChar) { return WCharToCharFunc::Char(inChar); }
	static std::string Str(const wchar_t* inStr) { return WCharToCharFunc::Str(inStr); }
	static std::string Str(const std::wstring& inStr) { return WCharToCharFunc::Str(inStr.c_str()); }
};

template<>
struct CharConv<wchar_t>
{
	typedef std::wstring StringType;
	
	static wchar_t Char(char inChar) { return CharToWCharFunc::Char(inChar);	}
	static std::wstring Str(const char* inStr) { return CharToWCharFunc::Str(inStr); }
	static std::wstring Str(const std::string& inStr) { return CharToWCharFunc::Str(inStr.c_str()); }

	static wchar_t Char(wchar_t inChar) { return WCharToWCharFunc::Char(inChar);	}
	static std::wstring Str(const wchar_t* inStr) { return WCharToWCharFunc::Str(inStr); }
	static std::wstring Str(const std::wstring& inStr) { return WCharToWCharFunc::Str(inStr.c_str()); }
};


std::vector<std::string> SplitStringToVector(const std::string& inStr, const char inDelim);
std::string JoinStringVector(const std::vector<std::string>& inStrVec, const std::string& inSep);
void TrimStringVector(std::vector<std::string>& ioStrVec);
std::vector<std::string> StringArrayToStringVector(const char* inNullTerminatedStrArray[]);
std::vector<std::string> StringVectorIntersection(const std::vector<std::string>& inVecA, const std::vector<std::string>& inVecB);



// Null out entire structures

template <typename T>
void ClearStruct(T* inStructPtr) 
{ 
	::memset(inStructPtr, 0, sizeof(T)); 
}

template <typename T>
void ClearArray(T* inBasePtr, int32 inElementCount) 
{ 
	::memset(inBasePtr, 0, inElementCount * sizeof(T)); 
}

// Easy comparison of memory (for filling out operator =='s)

template <typename T>
int32 CompareStructs(const T* inA, const T* inB) 
{ 
	return ::memcmp(inA, inB, sizeof(T)); 
}

template <typename T>
bool CompareStructsEqual(const T* inA, const T* inB) 
{ 
	return ::memcmp(inA, inB, sizeof(T)) == 0; 
}
	
inline void SexySleep(uint32 milliseconds)
{
#if defined HOST_WINDOWS || defined HOST_XBOX360
	::Sleep(milliseconds);
#elif defined HOST_PS3
	sys_timer_usleep(milliseconds*1000);
#elif defined RVL_OS
	milliseconds > 0 ? OSSleepMilliseconds(milliseconds) : OSYieldThread();
#elif defined HOST_MACOSX || defined HOST_IPHONEOS || defined HOST_ANDROID
	usleep(milliseconds*1000);
#elif defined WINRT_CLUSTER
	WaitForSingleObjectEx(GetCurrentThread(), milliseconds, FALSE);
#endif
}

#define NOP() (void)0
    

    
    //--------------------------------------------------------------------------
    // Class NonCopyable definition
    
    // Private copy constructor and copy assignment ensure classes derived from
    // class NonCopyable cannot be copied.
    //
    // (Copied from http://www.boost.org/doc/libs/1_40_0/boost/noncopyable.hpp)
    
    namespace NonCopyableNamespace // protection from unintended ADL (argument dependent lookup)
    {
        class NonCopyableClass // the "class" postfix also necessary to avoid problems
        {
        protected:
            NonCopyableClass()
            {
            }
            
            ~NonCopyableClass()
            {
            }
        private:  // emphasize the following members are private
            NonCopyableClass(const NonCopyableClass&);
            const NonCopyableClass& operator=(const NonCopyableClass&);
        };
    }
    
    typedef NonCopyableNamespace::NonCopyableClass NonCopyable;

    
    // $ Note: The delete macros can't be converted to templates because the dtors
    //   can't be called if private yet friended to the class method doing the
    //   deleting. So they have to stay macros.
    
    // Delete and null a pointer.
    //
#define PRIME_DELETE(inObjectPtr) { delete inObjectPtr; inObjectPtr = 0; }
    
    //-----------------------------------------------------------------------
    // Class AutoDeleteArray
    //
    // Used to ensure an array is deleted when this AutoDeleteArray goes
    // out of scope.
    
    template <typename ArrayElementType>
    class AutoDeleteArray : public NonCopyable
    {
    public:
        AutoDeleteArray(ArrayElementType* inArrayToDelete)
        {
            mArrayToDelete = inArrayToDelete;
        }
        virtual ~AutoDeleteArray()
        {
            DeleteArrayNow();
        }
        
        // Will cause the currently register array to be deleted now, instad of waiting for
        // the destructor to be called.
        void DeleteArrayNow()
        {
            delete [] mArrayToDelete;
            mArrayToDelete = NULL;
        }
        
        // This will register a new array to be auto deleted.
        // Any existing array that is registered with this object
        // will no longer be referenced by this object and will not
        // be deleted.
        void RegisterNewArray(ArrayElementType* inNewArrayToDelete)
        {
            mArrayToDelete = inNewArrayToDelete;
        }
        
    private:
        ArrayElementType* mArrayToDelete;
    };

    //--------------------------------------------------------------------------
    // Class TOptAutoPtr <T> declaration
    
    template <typename T>
    class TOptAutoPtr : NonCopyable
    {
    public:
        TOptAutoPtr(T* i_object = NULL, bool i_shouldOwn = false)
        {
            m_object = i_object;
            m_owned = i_shouldOwn;
        }
        
        ~TOptAutoPtr()
        {
            if (m_owned)
            {
                PRIME_DELETE(m_object);
            }
        }
        
        // API.
        
        void Set(T* i_object, bool i_shouldOwn = false)
        {
            if ((m_object != NULL) && m_owned)
            {
                delete m_object;
            }
            
            m_object = i_object;
            m_owned = i_shouldOwn;
        }
        
        void Take(T* i_object)
        {
            Set(i_object, true);
        }
        
        void SetUnused(T* i_object, bool i_shouldOwn = false)
        {
            PRIME_ASSERT(m_object == NULL);
            m_object = i_object;
            m_owned = i_shouldOwn;
        }
        
        void TakeUnused(T* i_object)
        {
            SetUnused(i_object, true);
        }
        
        void Clear()
        {
            Set(NULL);
        }
        
        // Access.
        
        T* GetObjectPtr()
        {
            return m_object;
        }
        const T* GetObjectPtr() const
        {
            return m_object;
        }
        
        T& GetObject()
        {
            PRIME_ASSERT(m_object != NULL);
            return *m_object;
        }
        const T& GetObject() const
        {
            PRIME_ASSERT(m_object != NULL);
            return *m_object;
        }
        
        T* operator -> ()
        {
            PRIME_ASSERT(m_object != NULL);
            return m_object;
        }
        const T* operator -> () const
        {
            PRIME_ASSERT(m_object != NULL);
            return m_object;
        }
        
        // Other query.
        
        bool IsValid()
        {
            return m_object != NULL;
        }
        bool IsNull()
        {
            return m_object == NULL;
        }
        
    private:
        T*   m_object;	// object we're pointing at (ok to be null)
        bool m_owned;	// true if we're responsible for deleting it when replaced or container is destroyed
    };
    
    //--------------------------------------------------------------------------
    // Class NoRecursion declaration and implementation
    
#if !SEXY_IS_BUILD_RELEASE || PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED
    
    class NoRecursion : NonCopyable
    {
    public:
        NoRecursion(int32& ioRecursionCount)
		: mRecursionCount(ioRecursionCount)
        {
            mMyRecursionCount = AtomicIncrement(&mRecursionCount) - 1;
        }
        
        ~NoRecursion()
        {
            AtomicDecrement(&mRecursionCount);
        }
        
        bool IsRecursing() const
        {
            return mMyRecursionCount != 0;
        }
        
    private:
        int32& mRecursionCount;
        int32  mMyRecursionCount;
    };
    
#endif // !SEXY_IS_BUILD_RELEASE

template<class T,class T2> T max_t(T a, T2 b) { return ((a>b)?a:b); }
template<class T,class T2> T min_t(T a, T2 b) { return ((a<b)?a:b); }

} // namespace Sexy

// Join two symbols together (useful in macros)
//
#define SEXY_STR_JOIN(X, Y) SEXY_STR_DO_JOIN(X, Y)
#define SEXY_STR_DO_JOIN(X, Y) SEXY_STR_DO_JOIN2(X, Y)
#define SEXY_STR_DO_JOIN2(X, Y) X##Y


#ifdef HOST_ANDROID

#include <sstream>

namespace std
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#endif

#endif //__SEXYAPPFRAMEWORK_COMMON_H__
