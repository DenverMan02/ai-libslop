//
//  UIXmlHandler.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __StringHelper_h_
#define __StringHelper_h_

#include <string>
#include "UIRect.h"
#include "SexyAppBase.h"

struct StringFastLessCompare
{
	bool operator() (const std::string& a, const std::string& b) const
	{
		const size_t la = a.length();
		const size_t lb = b.length();
		if (la == lb)
			return (memcmp(a.c_str(), b.c_str(), la * sizeof(std::string::value_type)) < 0);

		return (la < lb);
	}
};

namespace Sexy
{
	class StructuredData;
}

class StringHelper
{
public:
	static bool				ToBool(const std::string& str);
	static float				ToFloat(const std::string& str);
    static float				GetPrecionF(float src, int precion);
	static int					ToInt(const std::string& str);
    static ulong            ToColor(const std::string& str);
	static UI_Area		ToArea(const std::string& str);
	static class Sexy::Image*		ToImage(const std::string& str, bool enableNull = false);
	static class PopAnim*			ToAnimRig(const std::string& str, bool enableNull = false);

    static std::string		ToString(const int& val);
    static std::string		ToString(const float& val);
    static std::string		ToString(const bool& val);
	static std::string		ToString(const UI_Area& val);
	static std::string		ToString(const class Sexy::Image* pImage);
	static std::string		ToString(const class PopAnim* pAnim);
    static std::string  ToString(const Sexy::Color& clr);
    
    static SexyString   ToStringValue(const std::string& str);
    static std::string		ToStringName(const SexyString& str);
    static bool         IsStringValueExist(const std::string& str);
    static SexyString   ReplaceNumberString(const std::string& str, const SexyString& rxStr, int i_number);
    static SexyString   ReplaceNumberString(const std::string& str, const SexyChar *i_stringToFind, int i_number);
    static SexyString   ReplaceNumberString(const SexyString& str, const SexyChar *i_stringToFind, int i_number);
	static SexyString   ReplaceNumberSexyString(const SexyString& str, const SexyString& rxStr, int i_number);
    static SexyString   ReplaceNumberString(const std::string& str, const std::map<SexyString, int>& i_replaceList);
    
    static class Sexy::PrimeTypeface*    ToFont(int fontIndex);
    static int                     ToFontIndex(class Sexy::PrimeTypeface* pFont);
    
    enum TimeFormat
    {
        TimeFormat_Default,
        TimeFormat_CN,
        TimeFormat_MinSec,
        TimeFormat_HourMinSec,
        TimeFormat_Day
    };
    static SexyString      ToTimeString(float seconds, int fmt = TimeFormat_Default);
    static SexyString		ConvertTimeToHMSString(time_t seconds);
    static SexyString		ConvertTimeToHMString(time_t seconds);
    enum DateFormat
    {
        DateFormat_Default,
        DateFormat_CN,
    };
    static SexyString      ToDateString(int i_date, int fmt = DateFormat_Default);
    static SexyString      ToDateString(int i_year, int i_mon, int i_day, int fmt = DateFormat_Default);
    
    static std::string      ToServerString(const std::wstring& i_strCN);
    static std::string      GetJsonFromPackage(const std::string& i_filePath);
	static bool					ReadJson(const std::string& i_json, class Sexy::StructuredData* o_data);
    static bool             GetObjectFromJson(const std::string& i_json, const std::string& i_key, Sexy::RtObject& o_data);
    
    static int              GetDigits(int i_num, std::vector<int>& o_numList);
public:
	static bool SexyStringCacheEnabled;
	static const std::string		Empty;
    static const SexyString     EmptySexyString;
    static const float          MaxArtRes;
private:
	static Sexy::StringSexyStringMap	CachedSexyStrings;
};

#endif
