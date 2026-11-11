#ifndef __SEXYAES_H__

#define __SEXYAES_H__



#include "SexyMD5.h"

#include "Rijndael.h"

#include "Base64.h"

#include "SexyZlib.h"



#define KEY_SIZE 32

#define BLOCK_SIZE 24

#define BUFFER_SIZE BLOCK_SIZE*1024



#define ENCYPT_VERSION_CODE 0x01



void GenerateKeyIV(const char* pKey, std::string &strKey, std::string &strIV);

void PrintBuf(const char* i_buf, size_t i_len);

void EncodeFile(const char* inFile, const char* outFile);

void DecryptString(const char* i_in, std::string &i_out, size_t i_inLen);

void DecryptString2(const char* i_in, std::string &i_out, size_t i_inLen);

void DecodeFile(const char* inFile, const char* outFile);



#endif