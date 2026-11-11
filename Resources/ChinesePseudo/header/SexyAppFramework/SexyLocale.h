#ifndef __SEXYAPPFRAMEWORK_SEXYLOCALE_H__
#define __SEXYAPPFRAMEWORK_SEXYLOCALE_H__

// NOTE: This file is included by Common.h and should not be included directly.
#ifndef __SEXYAPPFRAMEWORK_COMMON_H__
#include "Common.h"
#endif

namespace Sexy
{
	namespace Locale
	{
		void				SetSeperators( const SexyString& theGrouping, const SexyString& theSeperator );
		void				SetLocale(const SexyString& theLocale);
		std::string			StringToUpper(const std::string& theString);
		std::wstring		StringToUpper(const std::wstring& theString);
		std::string			StringToLower(const std::string& theString);
		std::wstring		StringToLower(const std::wstring& theString);
		bool				isalnum(const char theChar);
		bool				isalnum(const wchar_t theChar);
		SexyString			CommaSeparate(int theValue);
		SexyString			UCommaSeparate(unsigned int theValue);
		SexyString			CommaSeparate64(int64 theValue);
		SexyString			UCommaSeparate64(uint64 theValue);
	}
}

#endif // #ifndef __SEXYAPPFRAMEWORK_SEXYLOCALE_H__
