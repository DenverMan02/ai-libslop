//
//  PrimeFont.h
//  SexyAppFramework Prime
//
//  PrimeFont is merely a resource holder which interfaces with a text server.
//
//  This is because the concept of Font is no longer a static single instance such
//  as a bitmap but can be a TrueType font that has multiple simultaneous sizes,
//  styles, etc.
//
//  See the implementation of PrimeText.
//
//  Created by Jason Emery on 3/20/13.
//
//

#ifndef SexyAppFramework_Prime_PrimeFont_h
#define SexyAppFramework_Prime_PrimeFont_h

#include "Buffer.h"
#include "Common.h"
#include "ResourceTypes.h"
#include "PrimeText.h"

namespace Sexy
{
    namespace ResourceInfoTypes { class PrimeFontRes; }
    
    class PrimeFont
    : public BaseResource
    {
    public:
        RT_CLASS_DEFINE_ABSTRACT(PrimeFont, BaseResource, ResourceClass);
        typedef ResourceInfoTypes::PrimeFontRes InfoClass;
        
    public:
        PrimeFont();
        PrimeFont(const PrimeFont& otherPrimeFont);
        virtual ~PrimeFont();
        
        bool LoadResourceFile(const char* inFileName);
        
    private:
        bool LoadFromMem(ulong inDataLen, const void* inData, const char* inSrcFileName);
        
#ifdef WANTS_PRIMETEXT
        EA::Text::FontDescription   mFontDescription;
#endif
    };
    
}

#endif
