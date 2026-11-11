#ifndef __REGKEY_H__
#define __REGKEY_H__

#include "CryptCommon.h"
#include "BigInt.h"

BigInt HashData(const char* theData, int theDataLen, int theNumBits);
BigInt HashString(const std::string& theString, int theNumBits);
std::string IntToKey(const BigInt& theBigInt, int aNumBits);
BigInt KeyToInt(const std::string& theString);

extern const char gRegKeyTranslationTable[][2];

#endif //__REGKEY_H__
