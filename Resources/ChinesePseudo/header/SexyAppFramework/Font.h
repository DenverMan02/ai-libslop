#ifndef __FONT_H__
#define __FONT_H__

#include "Common.h"
#include "Rect.h"
#include "Color.h"
#include "ResourceTypes.h"

//PVZ2_CHINESE_BEGIN
#ifdef WIDGETS_USE_PRIMETEXT
#include "PrimeText/Prime_EATech_Bridge.h"
#endif
//PVZ2_CHINESE_END

#ifndef REMOVE_SEXYFONT

namespace Sexy
{

class Graphics;
class ImageFont;
namespace ResourceInfoTypes { class FontRes; }

class Font
: public BaseResource
{
public:
	RT_CLASS_DEFINE_ABSTRACT(Font, BaseResource, ResourceClass);
	typedef ResourceInfoTypes::FontRes InfoClass;

public:
	int						mAscent;
	int						mAscentPadding; // How much space is above the avg uppercase char
	int						mHeight;
	int						mLineSpacingOffset; // This plus height should get added between lines
	
public:
	Font();
	Font(const Font& theFont);
	virtual ~Font();

	virtual ImageFont*		AsImageFont() {	return NULL; }

	virtual int				GetAscent();
	virtual int				GetAscentPadding();
	virtual int				GetDescent();
	virtual int				GetHeight();
	virtual int				GetLineSpacingOffset();
	virtual int				GetLineSpacing();
	virtual int				StringWidth(const SexyString& theString);
	virtual int				CharWidth(SexyChar theChar);
	virtual int				CharWidthKern(SexyChar theChar, SexyChar thePrevChar);

	virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect);

	virtual Font*			Duplicate() = 0;
    
//PVZ2_CHINESE_BEGIN
#ifdef WIDGETS_USE_PRIMETEXT
    /// ------- Direct Draw Strings -------
    // Directly draws strings to the screen
    // Use sparingly for testing as this is speed-inefficient.
    // It is faster to prepare a string and render out its reusable glyph mesh.
    void DrawString_Simple(Sexy::Graphics* g, float x, float y, SexyString text, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Line(Sexy::Graphics* g, float x, float y, float width, SexyString text, EA::Text::HAlignment alignment = EA::Text::kHADefault, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Paragraph(Sexy::Graphics* g, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Paragraph(Sexy::Graphics* g, Rect extents, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Typesetter(Sexy::Graphics* g, EA::Text::Typesetter& typesetter, float fRectHeight, bool useTypesetterColorChanges = false);
    
    // Get size text will render at
    void SizeString_Paragraph(SexyString text, int& x, int& y, float layoutWidth = 0);
    int SizeString_Line(SexyString text);
    
    float GetLineHeight();
    float GetCharWidth(SexyChar thisChar);
    float GetCharWidthKern(SexyChar curChar, SexyChar prevChar);
#endif
//PVZ2_CHINESE_END
    
};

}

#endif // REMOVE_SEXYFONT

#endif //__FONT_H__
