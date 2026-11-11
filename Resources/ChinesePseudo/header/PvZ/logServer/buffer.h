/**
 * @brief  A non-lock circular buffer. 
 *
 * @author Zhong Weiqi
 * @date 2008/12/1
 *
 * Herm library
 * Copyright (c) 2008 by weiqi.zhong
 *
 * Permission to use, copy, modify, distribute and sell this software.
 */

#ifndef ARESH_BUFFER_H
#define ARESH_BUFFER_H
#include <cstring>


class  CBuffer
{
public:
	static const unsigned int MIN_SPACE_SIZE = 1;

	CBuffer(unsigned int size);
	~CBuffer();

	/**
     * @brief Read data but don't move the m_read
	 */
	unsigned int Peek(char* buff, unsigned int len);
	bool SeekReadPtr(unsigned int len);

	/**
     * @brief Fetch data to buff.
	 * @return -1, failed; other value is the size of read.
	 */
	unsigned int Fetch(char* buff, unsigned int len);
	/**
	 * @brief Read a block data.
	 * @return, -1, invalid message; other value, read size.
	 */
	unsigned int FetchChunk(char* buff, unsigned int len);
	bool Push(const char* buff, unsigned int len);

	inline void Clear()
	{
		m_write = m_read = 0;
	}

	inline unsigned int Length() const
	{
		return m_write - m_read;
	}

	inline bool Empty() const
	{
		return Length() == 0;
	}

	inline bool Full() const
	{
		return m_size - Length() == 0;
	}

	inline unsigned int Space() const
	{
		return m_size - Length();
	}
protected:
	inline bool IsPowerOf2(unsigned int x)
	{
		return (x != 0) && ((x & (x - 1)) == 0);
	}


	inline unsigned int min(unsigned int a, unsigned int b)
	{
		return a < b ? a : b;
	}


public:
	char* m_buff;	
	unsigned int m_size;	
	unsigned int m_write;  // data is added at offset (in % size)
	unsigned int m_read; // data is extracted from off. (out % size)
};


#endif
