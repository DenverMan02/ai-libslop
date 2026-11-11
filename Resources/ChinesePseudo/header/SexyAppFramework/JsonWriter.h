
#pragma once
#ifndef SEXY_JSONWRITER_H_INCLUDE
#define SEXY_JSONWRITER_H_INCLUDE

#include "StructuredData.h"
#include <ostream>
#include <string>

namespace Sexy
{
	class StructuredData;
	class Buffer;
	
	class JsonWriter
	{
	public:
		
		enum Format
		{
			COMPACT,
			READABLE,
		};
		
		JsonWriter();
		JsonWriter( Format format );
		void SetOutputFormat( Format format );
		
		void Write( std::ostream& os, const StructuredData::Value* root, bool i_addQuote = true ) const;
        
        // $ Note: outputBuffer will contain the json characters, but will not
        // be a NULL terminated string (it is just the json data). If a string
        // is desired call Writer() with an std::ostream argument rather than
        // with a Buffer argument.
		void Write( Buffer* outputBuffer, const StructuredData::Value* root ) const;
		void WriteString( std::ostream& os, StructuredData::String str, bool i_addQuote = true ) const;
	protected:
		
		void Write( std::ostream& os, const StructuredData::Value* root, std::string prefix, bool writeName, bool i_addQuote = true ) const;
		
		
		std::string mNameSeparator;
		std::string mFieldTerminator;
		std::string mIndentation;
	};
	
}
#endif
