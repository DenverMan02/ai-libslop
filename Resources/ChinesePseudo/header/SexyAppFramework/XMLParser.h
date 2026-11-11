#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include "Common.h"
#include "EncodingParser.h"

struct PFILE;

namespace Sexy
{

class XMLParam
{
public:
	std::string				mKey;
	std::string				mValue;
};

typedef std::map<SexyString, SexyString>	XMLParamMap;
typedef std::list<XMLParamMap::iterator>	XMLParamMapIteratorList;

typedef std::vector<wchar_t> XMLParserBuffer;

class XMLElement
{
public:
	enum
	{
		TYPE_NONE,
		TYPE_START,
		TYPE_END,
		TYPE_ELEMENT,
		TYPE_INSTRUCTION,
		TYPE_COMMENT
	};
public:
	
	int						mType;
	SexyString				mSection;
	SexyString				mValue;
	SexyString				mValueEncoded;
	SexyString				mInstruction;
	XMLParamMap				mAttributes;
	XMLParamMap				mAttributesEncoded;
	XMLParamMapIteratorList	mAttributeIteratorList; // stores attribute iterators in their original order
	XMLParamMapIteratorList	mAttributeEncodedIteratorList; // stores attribute iterators in their original order

	bool					GetAttributeBool(const SexyString& theKey, bool theDefaultValue=false);
};

class XMLParser : public EncodingParser
{
protected:
	std::string				mFileName;
	SexyString				mErrorText;
	int						mLineNum;
	bool					mHasFailed;
	bool					mAllowComments;
	SexyString				mSection;

protected:
	void					Fail(const SexyString& theErrorText);
	void					Init();

	bool					AddAttribute(XMLElement* theElement, const SexyString& theAttributeKey, const SexyString& theAttributeValue);
	bool					AddAttributeEncoded(XMLElement* theElement, const SexyString& theAttributeKey, const SexyString& theAttributeValue);

public:
	XMLParser();
	virtual ~XMLParser();

	virtual bool			OpenFile(const std::string& theFilename);
	virtual bool			NextElement(XMLElement* theElement);
	SexyString				GetErrorText();
	int						GetCurrentLineNum();
	std::string				GetFileName();

	virtual void			SetStringSource(const std::wstring& theString);

	inline void				AllowComments(bool doAllow) { mAllowComments = doAllow; }

	bool					HasFailed();
};

};

#endif //__XMLPARSER_H__
