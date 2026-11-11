
#ifndef __SEXYAPPFRAMEWORK_CIRCULARBUFFER_H__
#define __SEXYAPPFRAMEWORK_CIRCULARBUFFER_H__

#include "Common.h"

namespace Sexy
{

//--------------------------------------------------------------------------
// Class CircularBuffer declaration

// $ this class takes a chunk of memory and turns it into a circular queue.
//   it never does any allocs from the Mem system but always works within
//   the memory you give it.
//
//   a write ptr will write into the buffer up until the read ptr. the read
//   ptr will chase the write ptr around, stopping when it reaches it. both
//   will wrap past the end of the memory block as needed.

// $ note: not thread-safe. use higher level locks if necessary.

class CircularBuffer
{
public:

	//-----------------------------------
	// Setup.

	CircularBuffer() 
	{ 
		Init(0, NULL, 0);
	}

	// give the buffer a piece of memory to work with and an alignment to use
	// when aligning pointers.
	void Init(int inAlignment, void* inBuffer, int inSizeBytes);

	// do we have memory to work with?
	inline bool IsInitialized() const 
	{ 
		return mBegin != NULL; 
	}

	// reset to Init() conditions
	void Reset();

	//-----------------------------------
	// Query

	// true if 'this' has been initialized
	inline bool IsValid() const 
	{ 
		return mBegin != NULL; 
	}

	// see if we're the same basic chunk
	inline bool IsSameMemoryBlock(const CircularBuffer& inOther) const 
	{ 
		return (mBegin == inOther.mBegin) && (mEnd == inOther.mEnd); 
	}

	// $ for these functions, 'no wrap' means the total amount of contiguous
	//   space after the pointer. shouldn't typically need to use the
	//   'no wrap' stuff, but the internal functions do a lot.

	// return available space to read/write
	inline int GetAvailableWriteBytes() const 
	{ 
		return mAvailableWrite; 
	}

	int GetAvailableWriteBytesNoWrap() const;

	inline int GetAvailableReadBytes() const 
	{ 
		return (int)(mEnd - mBegin) - mAvailableWrite; 
	}
	int GetAvailableReadBytesNoWrap() const;

	// return if we can read/write the given num bytes
	inline bool CanWrite(int inBytesToWrite) const 
	{ 
		return GetAvailableWriteBytes() >= inBytesToWrite; 
	}
	
	inline bool CanWriteNoWrap(int inBytesToWrite) const 
	{ 
		return GetAvailableWriteBytesNoWrap() >= inBytesToWrite; 
	}
	
	inline bool CanRead(int inBytesToRead) const 
	{ 
		return GetAvailableReadBytes() >= inBytesToRead; 
	}
	
	inline bool CanReadNoWrap(int inBytesToRead) const 
	{ 
		return GetAvailableReadBytesNoWrap() >= inBytesToRead; 
	}

	//-----------------------------------
	// Writing

	// write to the writeptr, asserts if not enough room
	void Write(const void* inDataToWrite, int inBytesToWrite);

	template <typename T>
	void Write(const T& inStructToWrite) 
	{ 
		Write(&inStructToWrite, sizeof(inStructToWrite)); 
	}

	// returns false if no room, otherwise writes it
	bool TryWrite(const void* inDataToWrite, int inBytesToWrite);

	template <typename T>
	bool TryWrite(const T& inStructToWrite)	
	{ 
		return TryWrite(&inStructToWrite, sizeof(inStructToWrite)); 
	}

	// advance the write pointer by the given size, asserts if no room
	uint8* AdvanceWritePtr(int inSizeBytes);

	// advance to the next alignment, asserts if no room
	void PadWriteToAlignment();

	// for direct access, such as reading in direct from a file. careful to
	// advance the pointer after you're done! here you will want to use the
	// 'no wrap' functions to make sure you don't go past the end when you
	// need to wrap.
	inline uint8* GetWritePtr() const 
	{ 
		return mWritePtr; 
	}

	// does a size check on T
	template <typename T>
	T* GetWritePtrT() const	
	{ 
		SEXY_ASSERT(CanWrite(sizeof(T))); return (T*)mWritePtr; 
	}

// Reading.

	// read from the readptr, asserts if not enough to read
	void Read(void* inDataToRead, int inBytesToRead);
	template <typename T>
	void Read(T& outStructToRead) 
	{ 
		return Read(&outStructToRead, sizeof(outStructToRead)); 
	}

	// returns false if not enough to read, otherwise reads it
	bool TryRead(void* inDataToRead, int inBytesToRead);
	template <typename T>
	bool TryRead(T& outStructToRead) 
	{ 
		return TryRead(&outStructToRead, sizeof(outStructToRead)); 
	}

	// use this to ffwd/rewind the read ptr (asserts if out of range)
	uint8* SeekReadPtr(int inSizeBytes);

	// advance to the next alignment, asserts if no room
	void AdvanceReadPtrToAlignment();

	// for direct access, such as reading in direct from a file. careful to
	// advance the pointer after you're done! here you will want to use the
	// 'no wrap' functions to make sure you don't go past the end when you
	// need to wrap.
	inline uint8* GetReadPtr() const 
	{ 
		return mReadPtr; 
	}

	// does a size check on T
	template <typename T>
	T* GetReadPtrT() const 
	{ 
		SEXY_ASSERT(CanRead(sizeof(T))); return (T*)mReadPtr; 
	}

private:
	int	  mAlignment;		// used for padding
	int	  mAvailableWrite;	// how much space is available to write
	uint8* mBegin;			// start of buffer capacity
	uint8* mEnd;				// end of buffer capacity
	uint8* mWritePtr;		// writing begins here, can go up to the read ptr (wrapping if needed)
	uint8* mReadPtr;			// reading begins here, can go up to the write ptr (wrapping if needed)
};

} // namespace Sexy

//--------------------------------------------------------------------------

#endif // __SEXYAPPFRAMEWORK_CIRCULARBUFFER__H__

//-----------------------------------EOF!-----------------------------------
