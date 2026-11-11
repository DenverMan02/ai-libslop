#ifndef PCPENCRYPT_H_
#define PCPENCRYPT_H_
#include <string>
//Function to convert string of length 2 to unsigned char
void Hex2Char(char const* szHex, unsigned char& rch);

//Function to convert string of unsigned chars to string of chars
void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);

//Function to convert string of chars to string of unsigned chars
void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);
void Char2Hex(unsigned char ch, char* szHex);
//void PCPEncrypt(char const*  inBuf,char* outBuf,int inLen,const char* key,const char* iv);
std::string PCPEncryptStr(char const* inBuf,int inLen,const char* key,const char*iv);

void PCPDecrypt(char const* inHexStr,char* outBuff,int inLen);
int  PCPDecrypt(char const* inHexStr,char*outBuff,int inLen,const char* key,const char* iv);

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
std::string base64_url_safe(unsigned char const* bytes_to_encode, unsigned int in_len);
std::string base64_decode_url_safe(std::string& encoded_string);

//concrete api
//void PCPEncryptSendData(const char* msgBody,char* ouBuf,int iLen,int reqId);
std::string  PCPEncryptSendDataStr(const char* msgBody,int iLen,int reqId,std::string& req);
void PCPDecryptRcvData(const char* hexChar,char*outBuf,int iLen);
int  PCPDecryptRcvDataByMsgId(char const* inHexStr,char*outBuf,int inLen,int msgId,std::string& req);
int gzcompress(unsigned char *data, unsigned long ndata, unsigned char *zdata, unsigned long *nzdata);
int gzdecompress(unsigned char *zdata, unsigned long nzdata,unsigned char *data, unsigned long *ndata);

std::string EncryptString(const char* i_inStr, int i_len, const char* i_key);
std::string DecryptString(const char* i_inStr, int i_len, const char* i_key);

#endif
