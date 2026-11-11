#ifndef __SEXYZLIB_H__

#define __SEXYZLIB_H__



#include "ImageLib/zlib/zlib.h"



const unsigned int COMPRESS_DEF_COOKIE = 0xDEADFED4;



struct ZLibCompressedHeader

{

public:

	unsigned int m_cookie;

#ifdef HOST_ANDROID
// Need optimize compress buffer for android in resgen !
#if defined(__aarch64__)
	unsigned int m_uncompressedSize;
#else
	unsigned long m_uncompressedSize;
#endif
#else
	unsigned long m_uncompressedSize;
#endif
};

struct ZLibCompressedHeader2

{

public:

    unsigned int m_cookie;

    unsigned int m_uncompressedSize;

};



int SizeForUncompress(unsigned char *i_compressedBuffer);

int SizeForUncompress2(unsigned char *i_compressedBuffer);

void* ZlibCompressBuffer(unsigned char *i_buffer, unsigned int i_bufferSize, unsigned int *i_resultSize);

void* ZlibCompressBuffer2(unsigned char *i_buffer, unsigned int i_bufferSize, unsigned int *i_resultSize, int level );

void ZlibUncompressBuffer(unsigned char *i_compressedBuffer, unsigned char *uncompressedBuffer, unsigned int i_compressedBufferSize);

void ZlibUncompressBuffer3(unsigned char *i_compressedBuffer, unsigned char *uncompressedBuffer, unsigned int i_compressedBufferSize);


#endif
