#ifndef __SEXYAPPFRAMEWORK_ALIGN_H__
#define __SEXYAPPFRAMEWORK_ALIGN_H__

#include "Common.h"

#ifdef HOST_IPHONEOS

#include <stdint.h>

namespace Sexy
{
    
    //-----------------------------------------------------------------------------
    // Alignment functions.
    
    // note that "alignment" is in bytes, and should be a power of 2 for these to work (we don't check)
    
    // variable-alignment
    template <typename T> inline bool  IsAligned   ( T  inValue, size_t inAlignment )  { return ( !((uintptr_t)inValue & (inAlignment - 1)) ); }
    template <typename T> inline T     GetAlignUp  ( T  inValue, size_t inAlignment )  { return ( (T)(((uintptr_t)inValue + inAlignment - 1) & ~(inAlignment - 1)) ); }
    template <typename T> inline T     GetAlignDown( T  inValue, size_t inAlignment )  { return ( (T)((uintptr_t)inValue & ~(inAlignment - 1)) ); }
    template <typename T> inline void  AlignUp     ( T& ioValue, size_t inAlignment )  { ioValue = (T)(((uintptr_t)ioValue + inAlignment - 1) & ~(inAlignment - 1)); }
    template <typename T> inline void  AlignDown   ( T& ioValue, size_t inAlignment )  { ioValue = (T)((uintptr_t)ioValue & ~(inAlignment - 1)); }
    template <typename T> inline ptrdiff_t GetPadTo    ( T  inValue, size_t inAlignment )  { return GetAlignUp( inValue, inAlignment ) - inValue; }
    
    // the #'s here (64, 32, etc.) are # of bits
    
    // 64bit-alignment functions
    template <typename T> inline bool  IsAligned64   ( T  inValue )  { return ( !((uintptr_t)inValue & 7) ); }
    template <typename T> inline T     GetAlignUp64  ( T  inValue )  { return ( (T)(((uintptr_t)inValue + 7) & ~7) ); }
    template <typename T> inline T     GetAlignDown64( T  inValue )  { return ( (T)((uintptr_t)inValue & ~7) ); }
    template <typename T> inline void  AlignUp64     ( T& ioValue )  { ioValue = (T)(((uintptr_t)ioValue + 7) & ~7); }
    template <typename T> inline void  AlignDown64   ( T& ioValue )  { ioValue = (T)((uintptr_t)ioValue & ~7); }
    
    // 32bit-alignment functions
    template <typename T> inline bool  IsAligned32   ( T  inValue )  { return ( !((uintptr_t)inValue & 3) ); }
    template <typename T> inline T     GetAlignUp32  ( T  inValue )  { return ( (T)(((uintptr_t)inValue + 3) & ~3) ); }
    template <typename T> inline T     GetAlignDown32( T  inValue )  { return ( (T)((uintptr_t)inValue & ~3) ); }
    template <typename T> inline void  AlignUp32     ( T& ioValue )  { ioValue = (T)(((uintptr_t)ioValue + 3) & ~3); }
    template <typename T> inline void  AlignDown32   ( T& ioValue )  { ioValue = (T)((uintptr_t)ioValue & ~3); }
    
    // 16bit-alignment functions
    template <typename T> inline bool  IsAligned16   ( T  inValue )  { return ( !((uintptr_t)inValue & 1) ); }
    template <typename T> inline T     GetAlignUp16  ( T  inValue )  { return ( (T)(((uintptr_t)inValue + 1) & ~1) ); }
    template <typename T> inline T     GetAlignDown16( T  inValue )  { return ( (T)((uintptr_t)inValue & ~1) ); }
    template <typename T> inline void  AlignUp16     ( T& ioValue )  { ioValue = (T)(((uintptr_t)ioValue + 1) & ~1); }
    template <typename T> inline void  AlignDown16   ( T& ioValue )  { ioValue = (T)((uintptr_t)ioValue & ~1); }
    
} // namespace Sexy
#else

namespace Sexy
{
	
//-----------------------------------------------------------------------------
// Alignment functions.

// note that "alignment" is in bytes, and should be a power of 2 for these to work (we don't check)

// variable-alignment
template <typename T> inline bool  IsAligned   ( T  inValue, size_t inAlignment )  { return ( !((uintptr_t)inValue & (inAlignment - 1)) ); }
template <typename T> inline T     GetAlignUp  ( T  inValue, size_t inAlignment )  { return ( (T)(((uintptr_t)inValue + inAlignment - 1) & ~(inAlignment - 1)) ); }
template <typename T> inline T     GetAlignDown( T  inValue, size_t inAlignment )  { return ( (T)((uintptr_t)inValue & ~(inAlignment - 1)) ); }
template <typename T> inline void  AlignUp     ( T& ioValue, size_t inAlignment )  { ioValue = (T)(((uintptr_t)ioValue + inAlignment - 1) & ~(inAlignment - 1)); }
template <typename T> inline void  AlignDown   ( T& ioValue, size_t inAlignment )  { ioValue = (T)((uintptr_t)ioValue & ~(inAlignment - 1)); }
template <typename T> inline ptrdiff_t GetPadTo    ( T  inValue, size_t inAlignment )    { return GetAlignUp(inValue, inAlignment) - inValue; }

// the #'s here (64, 32, etc.) are # of bits

// 64bit-alignment functions
template <typename T> inline bool  IsAligned64   ( T  inValue )  { return ( !((uintptr_t)inValue & 7) ); }
template <typename T> inline T     GetAlignUp64  ( T  inValue )  { return ( (T)(((uintptr_t)inValue + 7) & ~7) ); }
template <typename T> inline T     GetAlignDown64( T  inValue )  { return ( (T)((uintptr_t)inValue & ~7) ); }
template <typename T> inline void  AlignUp64     ( T& ioValue )  { ioValue = (T)(((uintptr_t)ioValue + 7) & ~7); }
template <typename T> inline void  AlignDown64   ( T& ioValue )  { ioValue = (T)((uintptr_t)ioValue & ~7); }

// 32bit-alignment functions
template <typename T> inline bool  IsAligned32   ( T  inValue )  { return ( !((uintptr_t)inValue & 3) ); }
template <typename T> inline T     GetAlignUp32  ( T  inValue )  { return ( (T)(((uintptr_t)inValue + 3) & ~3) ); }
template <typename T> inline T     GetAlignDown32( T  inValue )  { return ( (T)((uintptr_t)inValue & ~3) ); }
template <typename T> inline void  AlignUp32     ( T& ioValue )  { ioValue = (T)(((uintptr_t)ioValue + 3) & ~3); }
template <typename T> inline void  AlignDown32   ( T& ioValue )  { ioValue = (T)((uintptr_t)ioValue & ~3); }

// 16bit-alignment functions
template <typename T> inline bool  IsAligned16   ( T  inValue )  { return ( !((uintptr_t)inValue & 1) ); }
template <typename T> inline T     GetAlignUp16  ( T  inValue )  { return ( (T)(((uintptr_t)inValue + 1) & ~1) ); }
template <typename T> inline T     GetAlignDown16( T  inValue )  { return ( (T)((uintptr_t)inValue & ~1) ); }
template <typename T> inline void  AlignUp16     ( T& ioValue )  { ioValue = (T)(((uintptr_t)ioValue + 1) & ~1); }
template <typename T> inline void  AlignDown16   ( T& ioValue )  { ioValue = (T)((uintptr_t)ioValue & ~1); }

} // namespace Sexy

#endif

#endif // __SEXYAPPFRAMEWORK_ALIGN_H__
