//
//  PrimeTextPotentialText.h
//  SexyAppFramework Prime
//
//  Created by Jason Emery on 5/9/13.
//
//

#ifndef __SexyAppFramework_Prime__PrimeTextPotentialText__
#define __SexyAppFramework_Prime__PrimeTextPotentialText__

#include "PrimeText.h"

namespace Sexy
{

//
// This class contains a way to cache off parameters for text building.
//
// Usage:
// Create this class and call one of the BuildString functions to populate the parameters.
//
// Call Prepare() to construct a new GlyphMesh.
//
// Reuse this GlyphMesh indefinitely (until the GlyphCache is Cleared)
//
// History:
//
// It was necessary to develop because caching off GlyphMeshes, while powerful,
// has the limitation of being invalidated when the GlyphCache is cleared.
//
// PVZ2 wanted to keep their GlyphCache minimal and clear it at various instances
// while the menu was showing.
//
// So, this is used in conjunction with the PrimeTextWidget to allow it to reconstruct
// the text when invalidated.
//
// It may also be desirable to use to simplify future Widgets and other classes needing
// reusable text parameters.
//
class PrimeText_PotentialText
{
public:
    enum TextRegion
    {
        TextRegionInvalid,
        TextRegionSimple,
        TextRegionLine,
        TextRegionParagraph
    };
    
    PrimeText_PotentialText();
    
    PrimeGlyphMesh* Prepare();
    
    void SetOptionalParameters(PrimeTextExtraParameters* optionalParameters);
    
public:
    PrimeTypeface* mTypeface;
    SexyString mText;
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    EA::Text::HAlignment mHorizAlign;
    EA::Text::VAlignment mVertAlign;
    Sexy::Color mColor;
    
    bool mHasOptionalParameters;
    PrimeTextExtraParameters mOptionalParameters;
    TextRegion mRegion;
};

    // Factory-style Builders
    
    // Non justified or bounded line that grows to the right.
    extern PrimeText_PotentialText* BuildPotentialText_Simple(PrimeTypeface* typeface, int x, int y, SexyString text, Sexy::Color color = Color::Invalid);
    
    // Bounded and justified single line
    extern PrimeText_PotentialText* BuildPotentialText_Line(PrimeTypeface* typeface, float x, float y, float width, SexyString text, EA::Text::HAlignment alignment = EA::Text::kHADefault, Sexy::Color color = Color::Invalid);
    
    // Bounded and justified multiple lines
    extern PrimeText_PotentialText* BuildPotentialText_Paragraph(PrimeTypeface* typeface, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid);
    extern PrimeText_PotentialText* BuildPotentialText_Paragraph(PrimeTypeface* typeface, Rect location, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid);


}

#endif /* defined(__SexyAppFramework_Prime__PrimeTextPotentialText__) */
