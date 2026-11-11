
#pragma once
#include "Buffer.h"
#include <cstddef>

namespace Sexy
{

	class Base64
	{
	public:
		
		enum Mode
		{
			STANDARD,
			URL,
		};

		Base64();
		Base64( Mode mode );

		void SetMode( Mode mode );
		
		size_t SizeForEncodeBuffer( size_t inputLength ) const;
		size_t Encode( uchar* output, const uchar* input, size_t inputLength ) const;
		
		size_t SizeForDecodeBuffer( size_t inputLength ) const;
		size_t Decode( uchar* output, const uchar* input, size_t inputLength ) const;

		void Encode( Buffer* outputBuffer, const uchar* input, size_t inputLength );
		void Encode( Buffer* outputBuffer, const Buffer* inputBuffer );
		void Decode( Buffer* outputBuffer, const uchar* input, size_t inputLength );
		void Decode( Buffer* outputBuffer, const Buffer* inputBuffer );
		
	protected:

		void SelectTable( uchar* encodeTable, uchar* decodeTable );
		
		Mode mMode;
		unsigned char mPaddingChar;
		unsigned char* mEncodeTable;
		unsigned char* mDecodeTable;

	};
	
}
