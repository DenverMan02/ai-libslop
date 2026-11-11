//
//  PrimeText.h
//  SexyAppFramework Prime
//
//  Created by Jason Emery on 3/21/13.
//
//

#ifndef __SexyAppFramework_Prime__PrimeText__
#define __SexyAppFramework_Prime__PrimeText__

// Not possible to do this as EAText has too many dependencies on 16-bit chars
//#define EATEXT_CHAR_TYPE SexyChar
//#define EATEXT_CHAR_TYPE_SIZE 4

#include "SexyAppBase.h"

#ifdef WANTS_PRIMETEXT

#include "Prime_EATech_Bridge.h"
#include "PrimeTypeface.h"
#include "PrimeGlyphCache.h"
#include "PrimeGlyphMesh.h"

namespace Sexy
{

class PrimeText
{
public:
    static PrimeText* Instance();
    static void InstanceCreate(Sexy::SexyAppBase* appPointer);
    
private:
    PrimeText(Sexy::SexyAppBase* appPointer);
    ~PrimeText();
    
// Game-developer Functions
public:

    // Directly create simple typeface
    PrimeTypeface* TypefaceSimple(SexyString familyName, int size, Sexy::Color defaultColor = Sexy::Color::White);

    // Create advanced typefaces by modifying style
    PrimeTypeface* Typeface(EA::Text::TextStyle& textStyle);
    EA::Text::TextStyle TextStyle_Create(EA::Text::Char* familyName, int size, Sexy::Color defaultColor = Sexy::Color::White);
    EA::Text::TextStyle TextStyle_Create(SexyString familyName, int size, Sexy::Color defaultColor = Sexy::Color::White);

    // Used to store a default typeface for rendering
    // Note that PrimeText comes with a simple embedded font for guaranteed basic rendering
    PrimeTypeface* TypefaceDefault();

    // Framework call for drawing basic text using the embedded font
    // Note this is relatively slow
    static void DrawDebugText(Sexy::Graphics *g, SexyString text, int x, int y, const Sexy::Color& color = Sexy::Color::White);
    
    void ClearGlyphCache();
    int GlyphCacheVersion() { return mGlyphCacheVersion; }
    
// Debugging & Helpers
public:
    // Output list of all loaded fonts to the console
    void Font_DebugOutputAllFontNames();
    
    void DebugDrawCache(Graphics* g, int x, int y);
    
    bool DebugDrawRects() { return mShowDebugRects; }
    void SetDebugDrawRects(bool show) { mShowDebugRects = show; }
    
// System functions
public:
    // Return a GlyphMesh for rendering text onto
    PrimeGlyphMesh* GlyphMesh();
    
    static const char16_t* String32to16(SexyString text);
    
    void Font_AddTrueType(const void* inData, ulong inDataLen, EA::Text::FontDescription* mFontDescription);
    void Font_Remove(EA::Text::FontDescription& mFontDescription);
    void Font_AddUserEffect(uint32_t effectId, const EA::Text::EIWord* pInstructionList, uint32_t instructionCount);
    
private:
    void Init(Sexy::SexyAppBase* appPointer);
    int CalculateGlyphCacheResolution(int screenHeight, int& glyphPadding);
    void GlyphCacheVersionIncrement();
    
    wchar_t* String16ToWString(EA::Text::Char* string, int length);
  
private:
    EA::Text::FontServer* mFontServer;
    PrimeGlyphCache* mGlyphCache;
    
    PrimeTypeface* mEmbeddedTypeface;
    PrimeTypeface* mDefaultTypeface;
    
    // Add a cheat to your game to toggle this boolean to show placement rectangles for text in-game in debug builds
    bool mShowDebugRects;
    
    // ID Used to detect which version of the glyph cache meshes are built off of for automatic invalidation
    int mGlyphCacheVersion;
};
    
}

#else

namespace Sexy
{
    
    class PrimeText
    {
    public:
        PrimeText(void* appPointer) {};
        ~PrimeText() {};
        
        static void InstanceCreate(Sexy::SexyAppBase* appPointer) {}

    };
    
}

#endif

#endif /* defined(__SexyAppFramework_Prime__PrimeText__) */
