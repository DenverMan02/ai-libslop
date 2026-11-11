/** 
 * @author weiqi.zhong
 * @date 2013
 *
 * Herm library
 * Copyright (c) 2008 by Zhong Weiqi(wiqi.zhong@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 */

#ifndef HERM_FRAMEWORK_SOCK_BUFFER_H
#define HERM_FRAMEWORK_SOCK_BUFFER_H
#include <cstring>
#include"buffer.h"


class StreamBuffer : public CBuffer
{
public:
	StreamBuffer(unsigned int size);
	~StreamBuffer();

	/**
     * @brief Receive from Stream.
	 */
	int   Receive();
	char* GetBufReadStart(unsigned int& len);
	void  SetBuffReadPos(unsigned int posDelt);
	void  Clean();

	char* GetBufWriteStart(unsigned int& len);
	void  SetBuffWrtieStart(unsigned int posDelt);
    
    int   CheckGetAPhpPakage(char* oBuff,unsigned short maxLen);
    
	int   CheckGetAPackage(char* oBuff,unsigned short maxLen);
	bool  PushAPacket(const char* iBuff,unsigned short masLen);
    
    bool  PushAPacket(const char* iBuff,unsigned int msgLen);
    int   CheckGetAPackage(char* oBuff,unsigned int  maxLen);
    
	bool  PushAPakcetNoLen(const char* iBuff,unsigned short msgLen);


	/**
	 * @brief Send data by Stream.
	 * @param s, the source of data.
	 * @return true, succefully; false, the space of buffer is empty.
	 */
//	bool Send();

	
private:
};

#endif
