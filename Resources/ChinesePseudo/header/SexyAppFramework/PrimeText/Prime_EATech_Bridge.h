//
//  Prime_EATech_Bridge.h
//  SexyAppFramework Prime
//
//  This class is intended to be both a container for EA technologies and isolate
//  Prime from excessive links with EA Tech.
//
//  My hope is that anyone needing to know how we interface with EA Tech can first
//  look here.  Especially if we need to move/change/update/remove their system in
//  the future.
//
//  Also, this file is needed to ensure compatibility with configuration defines
//  type standards that would otherwise conflict.
//
//  Created by Jason Emery on 3/27/13.
//
//

#ifndef __SexyAppFramework_Prime__Prime_EATech_Bridge__
#define __SexyAppFramework_Prime__Prime_EATech_Bridge__

#include "Common.h"

#ifdef WANTS_PRIMETEXT

// Interpret the EA_FAIL_MESSAGE as otherwise it is compiled out
// TODO: Determine what EA Trace is.
#define EA_FAIL_MESSAGE(message)        OutputDebugString(message)
// TODO: Determine what we need to implement for the missing AsInterface and other linker errors in Profile builds.
// This is here as a reminder of the hack in the EA system.

#ifndef EA_TEXT_CACHE_TEXTURE_SIZE
//PVZ2_CHINESE_START
    #define EA_TEXT_CACHE_TEXTURE_SIZE  2048
//PVZ2_CHINESE_END
#endif

#include "Common.h"
#include <EAStdC/EAString.h>
#include <EAText/internal/EATextStream.h>
#include <EAText/EAText.h>
#include <EAText/EATextCache.h>
#include <EAText/EATextFontServer.h>
#include <EAText/EATextStyle.h>
#include <EAText/EATextOutlineFont.h>
#include <EAText/EATextLayout.h>

#if !defined(NDEBUG) || defined(WANTS_DEBUG_DRAW_ENABLED)
    #define DEBUG_PRIMETEXT
#endif

namespace Sexy
{
    // Extended optional parameters for text drawing
    struct PrimeTextExtraParameters
    {
        PrimeTextExtraParameters() :
        scaleX(1),
        scaleY(1)
        {};
        
        // Post-generate Scaling
        float scaleX;
        float scaleY;
    };
    
    
class PrimeAllocator : public EA::Allocator::ICoreAllocator
{
    void* Alloc(size_t size, const char* /*name*/, unsigned /*flags*/);
    void* Alloc(size_t size, const char* /*name*/, unsigned /*flags*/, unsigned /*align*/, unsigned /*alignOffset*/);
    void Free(void* ptr, size_t /*size*/);
};

extern EA::Allocator::ICoreAllocator*   GetPrimeAllocator();
    
}

extern void* FF_Alloc(size_t size);
extern void FF_Free(void* ptr);
extern void* FF_Realloc(void* ptr, int size);

#endif // WANTS_PRIMETEXT

#endif /* defined(__SexyAppFramework_Prime__Prime_EATech_Bridge__) */
