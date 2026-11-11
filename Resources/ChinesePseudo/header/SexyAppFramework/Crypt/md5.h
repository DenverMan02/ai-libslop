#ifndef MD5_H
#define MD5_H

#include "Common.h"

struct MD5Context {
        uint32 buf[4];
        uint32 bits[2];
        unsigned char in[64];
};

extern void MD5Init(MD5Context *ctx);
extern void MD5Update(MD5Context *ctx, unsigned char *buf, unsigned len);
extern void MD5Final(unsigned char digest[16], MD5Context *ctx);
extern void MD5Transform(uint32 buf[4], uint32 in[16]);
extern std::string GetMD5(const std::string& data);
extern std::string MD5DigestToHexDigest(const char *bytes, int numBytes);

/*
 * This is needed to make RSAREF happy on some MS-DOS compilers.
 */
typedef struct MD5Context MD5_CTX;

#endif /* !MD5_H */
