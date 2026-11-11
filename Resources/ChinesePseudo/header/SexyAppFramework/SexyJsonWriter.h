
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
		
		void Write( std::ostream& os, const StructuredData::Value* root ) const;
        
        // $ Note: outputBuffer will contain the json characters, but will not
        // be a NULL terminated string (it is just the json data). If a string
        // is desired call Writer() with an std::ostream argument rather than
        // with a Buffer argument.
		void Write( Buffer* outputBuffer, const StructuredData::Value* root ) const;
		
	protected:
		
		void Write( std::ostream& os, const StructuredData::Value* root, std::string prefix, bool writeName ) const;
		void WriteString( std::ostream& os, StructuredData::String str ) const;
		
		std::string mNameSeparator;
		std::string mFieldTerminator;
		std::string mIndentation;
	};
	
}
#endif