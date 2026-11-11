#pragma once

//#include "Platform.h"
#include <map>
#include "Common.h"


namespace Sexy {



struct FontCharListInfo
{
	SexyString fontType;			//like:FONT_TINYBOLD, FONT_CONTINUUMBOLD14(the id) 
	SexyString fontCharList;		//like"0123456abcAbC+", we get it from analysing lawnstring.txt and lawnstringwithfont.txt
};

class FontFilterInfo
{
public:
	FontFilterInfo();
	~FontFilterInfo();

	bool LoadFontFilterInfos(const char *i_LawnStringfileName, const char *i_LawnStringFontfileName, const char* i_LocSet);
	bool GetFontCharList(const SexyString& theFontName, SexyString& theFontCharList);	

	//if theString has its font define ,return true, and the font type, else return false
	bool FindFontTypeByStringID(const SexyString& theStringID, SexyString& theFontType);
 
private:
	bool AnalyseFilterInfos();
	void RefreshFontCharList(const SexyString& str, SexyString &fontCharList);
	bool TodStringListReadLawnStringFile(const char *i_fileName);
	bool TodStringListReadLawnStringFontFile(const char *i_fileName);

	bool TodStringListReadLawnStringItems(const SexyChar *i_fileText);
	bool TodStringListReadLawnStringWithFontItems(const SexyChar *i_fileText);

	bool TodStringListReadName(const SexyChar *&i_ptr, SexyString &i_name);
	bool TodStringListReadValue(const SexyChar *&i_ptr, SexyString &i_value);
	void TodStringRemoveReturnChars(SexyString &i_value);

	void DumpCharListInfo();//for debug

public:
	//typedef std::map<SexyString, SexyString> LawnStringIDToFontIDMap;
	//typedef std::map<SexyString, FontCharListInfo> FontCharListMap;			//the key is font type name
	SexyString	mLocSet;								 
	std::map<SexyString, SexyString>							mLawnStringIDToLawnStringMap;	//first:LawnStringID, second: LawnString
	std::map<SexyString, SexyString>							mLawnStringToStringIDMap;		//opposite of above
	std::map<SexyString, SexyString>							mLawnStringIDToFontTypeMap;		//first:LawnStringID, second: FontType
	std::map<SexyString, SexyString>							mFontToStringIDMap;				//opposite of above

	std::map<SexyString, FontCharListInfo>						mFontCharListMap;				//first:FontType,second: FontCharListInfo, for resgen get font charlist.
};

}

