//
//  PrimeTypeface.h
//  SexyAppFramework Prime
//
//  Represents an instance of a font, such as Helvetica 32 Bold.
//
//  Some background on this metaphor:
//  http://fontfeed.com/archives/font-or-typeface/
//
//  Created by Jason Emery on 3/27/13.
//
//

#ifndef __SexyAppFramework_Prime__PrimeTypeface__
#define __SexyAppFramework_Prime__PrimeTypeface__

#include "Prime_EATech_Bridge.h"
#include "PrimeGlyphMesh.h"
#include "Graphics.h"

namespace Sexy
{

//
// -------------
// Example Usage
// -------------
//
// Directly creating and drawing text.
//
// Complex typeface with shadow effect.
//
// EA::Text::TextStyle style2 = gSexyAppBase->mPrimeText->TextStyle_Create(fontToTest, 20);
// style2.mEffectColor = EA::Text::Color(0x00002000);
// style2.mEffect = EA::Text::kEffectShadow;
// PrimeTypeface* typeface2 = gSexyAppBase->mPrimeText->Typeface(style2);
// delete typeface2;
//

class PrimeTypeface
{
public:
    static int ParagraphHeightUnlimited;
    static int ParagraphFitSlack;
    
public:
    PrimeTypeface(EA::Text::Font* font, EA::Text::TextStyle& defaultStyle);
    ~PrimeTypeface();

    EA::Text::Font* GetEAFont() { return mFont; };
    EA::Text::TextStyle& GetDefaultStyle() { return mDefaultStyle; }

    /// ------- Direct Draw Strings -------
    // Directly draws strings to the screen
    // Use sparingly for testing as this is speed-inefficient.
    // It is faster to prepare a string and render out its reusable glyph mesh.
    void DrawString_Simple(Sexy::Graphics* g, float x, float y, SexyString text, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Line(Sexy::Graphics* g, float x, float y, float width, SexyString text, EA::Text::HAlignment alignment = EA::Text::kHADefault, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Paragraph(Sexy::Graphics* g, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Paragraph(Sexy::Graphics* g, Rect extents, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid, PrimeTextExtraParameters* optionalParameters = NULL);
    void DrawString_Typesetter(Sexy::Graphics* g, EA::Text::Typesetter& typesetter, float fRectHeight, bool useTypesetterColorChanges = false);

    /// ------- Prepare Strings -------
    /// Prepares a reusable GlyphMesh for later rendering
    ///
    /// These functions are intended to simplify end-developer access to EA Text for
    /// more common text drawing situations.
    
    // Non justified or bounded line that grows to the right.
    Sexy::PrimeGlyphMesh* PrepareString_Simple(float x, float y, SexyString text, const Sexy::Color& color = Color::Invalid);
    
    // Bounded and justified single line
    Sexy::PrimeGlyphMesh* PrepareString_Line(float x, float y, float width, SexyString text, EA::Text::HAlignment alignment = EA::Text::kHADefault, const Sexy::Color& color = Color::Invalid);

    // Bounded and justified multiple lines
    Sexy::PrimeGlyphMesh* PrepareString_Paragraph(float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, const Sexy::Color& color = Color::Invalid);

    Sexy::PrimeGlyphMesh* PrepareString_Typesetter(EA::Text::Typesetter& typesetter, float height, bool useTypesetterColorChanges = false);

    // Advanced Typesetter prepared with common settings
    EA::Text::Typesetter PrepareTypesetter(EA::Text::TextStyle& startingTextStyle, float x, float y, float width, float height, EA::Text::HAlignment horiz, EA::Text::VAlignment, const Sexy::Color& color = Color::Invalid);
    
    Sexy::PrimeGlyphMesh* PrepareGlyphMesh(EA::Text::LineLayout& lineLayout, const Sexy::Color& color, bool useTypesetterColorChanges = false);
    
    
    /// ------- Fit Strings -------
    /// Attempts to fit into the space allocated, testing smaller sizes until it really fits.
    /// Returns true if it had to resize the font.
    PrimeTypeface* FitString_Paragraph(SexyString text, int maxWidth, int maxHeight, int& resultHeight);
    PrimeTypeface* FitString_Line(SexyString text, int maxWidth, int& resultWidth);
    void SetTypefaceIfShrunk(PrimeTypeface* typeface);

    void ApplyOptionalParameters(PrimeGlyphMesh* glyphMesh, PrimeTextExtraParameters* optionalParameters, float originX, float originY, float width, float height);
    
    // Get size text will render at
    void SizeString_Paragraph(SexyString text, int& x, int& y, float layoutWidth = 0);
    int SizeString_Line(SexyString text);
    
    // Font Metrics
    float GetAscent();
    float GetAscentPadding();
    float GetDescent();
    float GetHeight();
    float GetLineHeight();
    float GetCharWidth(SexyChar thisChar);
    float GetCharWidthKern(SexyChar curChar, SexyChar prevChar);
    
    // Compatibility with old text system
    // TODO: Deprecate
    int StringWidth(SexyString text);
    float GetLineSpacing();
    float CharWidth(SexyChar thisChar) { return GetCharWidth(thisChar); }

    PrimeTypeface* ShrunkTypeface();
    
private:
    EA::Text::Font* mFont;
    EA::Text::TextStyle mDefaultStyle;

    PrimeTypeface* mTypefaceIfShrunk;
};

}

#endif /* defined(__SexyAppFramework_Prime__PrimeTypeface__) */
