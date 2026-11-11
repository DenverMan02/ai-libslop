#ifndef ENDIAN_H_INCLUDED
#define ENDIAN_H_INCLUDED

//
// These functions will swap bytes if the current platform is big endian.
//

unsigned int EndianDWORD(unsigned int src);
unsigned short EndianWORD(unsigned short src);

uint32 EndianUINT32(uint32 src);
uint16 EndianUINT16(uint16 src);

int64 EndianInt64(int64 src);
int EndianInt(int src);
short EndianShort(short src);
float EndianFloat(float src);
double EndianDouble(double src);

Sexy::FileTime EndianFileTime( Sexy::FileTime ft );

//
// These functions unconditionally swap bytes
//

uint64  ByteSwapUINT64(uint64 l);
uint32  ByteSwapUINT32(uint32 l);
uint16  ByteSwapUINT16(uint16 l);
int64   ByteSwapINT64(int64 src);
int     ByteSwapInt(int src);
short   ByteSwapShort(short l);
float   ByteSwapFloat(float l);
double  ByteSwapDouble(double src);
Sexy::FileTime ByteSwapFileTime(Sexy::FileTime ft);

//
// These functions swap bytes only if the secondary argument is true
//

inline uint64 ByteSwapUINT64(uint64 l, bool inDoSwap)
{
    return inDoSwap ? ByteSwapUINT64(l) : l;
}

inline uint32 ByteSwapUINT32(uint32 l, bool inDoSwap)
{
    return inDoSwap ? ByteSwapUINT32(l) : l;
}

inline uint16 ByteSwapUINT16(uint16 l, bool inDoSwap)
{
    return inDoSwap ? ByteSwapUINT16(l) : l;
}

inline int64 ByteSwapINT64(int64 l, bool inDoSwap)
{
    return inDoSwap ? ByteSwapINT64(l) : l;
}

inline int ByteSwapInt(int l, bool inDoSwap)
{
    return inDoSwap ? ByteSwapInt(l) : l;
}

inline short ByteSwapShort(short l, bool inDoSwap)
{
    return inDoSwap ? ByteSwapShort(l) : l;
}

inline float ByteSwapFloat(float l, bool inDoSwap)
{
    return inDoSwap ? ByteSwapFloat(l) : l;
}

inline double ByteSwapDouble(double src, bool inDoSwap)
{
    return inDoSwap ? ByteSwapDouble(src) : src;
}

inline Sexy::FileTime ByteSwapFileTime(Sexy::FileTime ft, bool inDoSwap)
{
    return inDoSwap ? ByteSwapFileTime(ft) : ft;
}



#endif
