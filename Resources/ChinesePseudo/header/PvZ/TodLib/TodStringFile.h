// TodStringFile.h

#ifndef __TOD_STRING_FILE_H__
#define __TOD_STRING_FILE_H__

#include "TodCommon.h"

#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Color.h"
#include "core.h"
#include <set>

namespace Sexy
{
	class Font;
	class Graphics;
};

enum TodStringFormatFlag
{
	PVZ_BEGIN_FLAG_ENUM(TOD_FORMAT_),
	PVZ_FLAG(TOD_FORMAT_IGNORE_NEWLINES),
	PVZ_FLAG(TOD_FORMAT_HIDE_UNTIL_MAGNETSHROOM),
	PVZ_END_FLAG_ENUM(TOD_FORMAT_)
};

class TodStringListFormat
{
public:
	const SexyChar *m_formatName;
	Sexy::PrimeTypeface **m_newFont;
	Sexy::Color m_newColor;
	int m_lineSpacingOffset;
	uint m_formatFlags;
};

#ifndef WANTS_CHEATS_DISABLED
static std::set<std::string> gTranslatedStringsSet;
void LogTranslateString(SexyString& i_key, SexyString& i_translatedString);
#endif

void TodStringListSetColors(TodStringListFormat *i_formats, int i_count);
void TodStringListLoad(const char *i_fileName);
SexyString TodStringTranslate(const SexyString& i_string);
SexyString TodStringTranslate(const SexyChar* i_string);
SexyString TodStringTranslateAll(const SexyString& i_string);
bool TodStringListExists(const SexyString& i_string);
int TodDrawStringWrapped(Sexy::Graphics *g, const SexyString& i_text, const Sexy::Rect& i_rect, Sexy::PrimeTypeface *i_font, const Sexy::Color &i_color, DrawStringJustification i_justification, bool i_drawAll = false);
int TodDrawStringWrappedHelper(Sexy::Graphics *g, const SexyString& i_text, const Sexy::Rect& i_rect, Sexy::PrimeTypeface *i_font, Sexy::Color i_color, DrawStringJustification i_justification, bool drawString, bool i_drawAll = false);
int TodDrawStringWrapped(Sexy::Graphics *g, const SexyString& i_text, const Sexy::Rect& i_rect, Sexy::Font *i_font, const Sexy::Color &i_color, DrawStringJustification i_justification, bool i_drawAll = false);
int TodDrawStringWrappedHelper(Sexy::Graphics *g, const SexyString& i_text, const Sexy::Rect& i_rect, Sexy::Font *i_font, Sexy::Color i_color, DrawStringJustification i_justification, bool drawString, bool i_drawAll = false);

#endif //__TOD_STRING_FILE_H__
