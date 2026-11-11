//
//  PrimeTextWidget.h
//  SexyAppFramework Prime
//
//  Lightweight text drawing object.
//  The intention is to start this with a minimal implementation and grow it with TextWidget functionality -or-
//  try to find common base functionality and create a root to TextWidget.
//
//  Created by Jason Emery on 4/8/13.
//
//

#ifndef __SexyAppFramework_Prime__PrimeTextWidget__
#define __SexyAppFramework_Prime__PrimeTextWidget__

#include "PrimeText/PrimeText.h"
#include "PrimeText/PrimeTextPotentialText.h"
#include "Widget.h"

namespace Sexy
{
    
    //PVZ2_CHINESE_BEGIN
    class FontText_PotentialText
    {
    public:
        enum TextRegion
        {
            TextRegionInvalid,
            TextRegionSimple,
            TextRegionLine,
            TextRegionParagraph
        };
        
        FontText_PotentialText();

    public:
        Font* mFont;
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
    //PVZ2_CHINESE_END
    
    
    class PrimeTextWidget : public Widget
    {
    public:
        PrimeTextWidget();
        //PVZ2_CHINESE_BEGIN
        PrimeTextWidget(FontText_PotentialText* pntentialText);
        
        //PVZ2_CHINESE_END
        PrimeTextWidget(PrimeText_PotentialText* potentialText);
        virtual ~PrimeTextWidget();
        
        // ----- PrimeText Implementation
        
        // Simple: Prepare strings for rendering
        void SetPotentialText(PrimeText_PotentialText* potentialText);
        //PVZ2_CHINESE_BEGIN
        void SetPotentialText(FontText_PotentialText* potentialText);
        //PVZ2_CHINESE_END
        
        // Advanced: Set this Widget with a pre-generated text glyphMesh for rendering.
        // Note: Cannot auto-size this, you must Resize the widget manually or you will not see anything!
        // Note: Cannot rebuild this automatically when glyph cache has been invalidated.
        void SetGlyphMesh(PrimeGlyphMesh* glyphMesh);
        void UpdateGlyphMeshCacheVersion();
        
        void Clear();
        
        void UpdateGlyphMesh();
        void CreateGlyphMesh();
        
        virtual void Draw(Graphics* g);
        virtual void DrawWithFont(Graphics* g);
        virtual void DrawWithPrimeFont(Graphics* g);
        virtual void SetColor(int theIdx, const Color& theColor);
        void SetText(const SexyString& text);
        bool IsEmpty() { return mPrimeTextPotentialText->mText.empty(); }
        SexyString GetText();
        void SetPosition(int x, int y);
        Point GetPosition();
        void SetRect(Rect region);
        
        void SetDontDrawWhenOffscreen(bool i_dontDraw);
        void SetScale(float x, float y);
        
    private:
        
        // ----- Previous Adapted Implementation
        
        void ClearGlyphMesh();
        
        // ----- PrimeText Implementation
        
        PrimeGlyphMesh* mGlyphMesh;
        
        //PVZ2_CHINESE_BEGIN
        PrimeText_PotentialText*    mPrimeTextPotentialText;
        FontText_PotentialText*     mFontTextPotentialText;
        //PVZ2_CHINESE_END
        
        int mGlyphCacheVersionUsed;
        
        bool mDontDrawOffscreen;
    };
    
    //PVZ2_CHINESE_BEGIN
    // Non justified or bounded line that grows to the right.
    extern FontText_PotentialText* BuildPotentialText_Simple(Font* font, int x, int y, SexyString text, Sexy::Color color = Color::Invalid);
    
    // Bounded and justified single line
    extern FontText_PotentialText* BuildPotentialText_Line(Font* font, float x, float y, float width, SexyString text, EA::Text::HAlignment alignment = EA::Text::kHADefault, Sexy::Color color = Color::Invalid);
    
    // Bounded and justified multiple lines
    extern FontText_PotentialText* BuildPotentialText_Paragraph(Font* font, float x, float y, float width, float height, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid);
    
    extern FontText_PotentialText* BuildPotentialText_Paragraph(Font* font, Rect location, SexyString text, EA::Text::HAlignment alignmentHorizontal = EA::Text::kHADefault, EA::Text::VAlignment alignmentVertical = EA::Text::kVADefault, Sexy::Color color = Color::Invalid);
    //PVZ2_CHINESE_END
    
}

#endif /* defined(__SexyAppFramework_Prime__PrimeTextWidget__) */
