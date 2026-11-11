//
//  PrimeText_SimpleFormatter.h
//  SexyAppFramework Prime
//
//  Created by Jason Emery on 4/16/13.
//
//

#ifndef __SexyAppFramework_Prime__PrimeText_SimpleFormatter__
#define __SexyAppFramework_Prime__PrimeText_SimpleFormatter__

#include "PrimeText.h"
#include "PrimeTypeface.h"

namespace Sexy
{

#define MAX_TYPE_STYLE_CHANGES  48
    
    // ---
    // Multi-line text rendering with embedded color values.
    // ---
    // This class is intended to be roughly analogous to the old WriteWordWrapped in Graphics.
    // For serious long-term use it should be reconsidered to use something like HTML strings.
    //
    // A more efficient implementation of this would have pre-defined styles that get picked
    // by the formatter, but for now it can support up to MAX_TYPE_STYLE_CHANGES by creating
    // them on the fly.
    //
    // Also, if this gets more complex it might be beneficial to consider more of a plug-in
    // architecture for interpreting the format-change sections.
    //
    // Format
    //      Change Color
    //          ...^4B4B4B...     This would be grey (4B, 4B, 4B)
    //
class PrimeText_SimpleFormatter
{
typedef eastl::fixed_vector<const EA::Text::TextStyle*, MAX_TYPE_STYLE_CHANGES> TextStyleArray;
    
public:
    static void DrawFormattedText(Sexy::Graphics* g, PrimeTypeface* font, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, const Sexy::Color& color = Sexy::Color::Invalid);

    static PrimeGlyphMesh* PrepareFormattedText(PrimeTypeface* font, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal, EA::Text::VAlignment alignmentVertical, Sexy::Color color);

private:
    static EA::Text::TextStyle* ProcessFormatter(SexyString text, int formatterOffset, EA::Text::TextStyle* lastTextStyle, const Sexy::Color& originalColor, int& formatterLength);

};
    
}

#endif /* defined(__SexyAppFramework_Prime__PrimeText_SimpleFormatter__) */
