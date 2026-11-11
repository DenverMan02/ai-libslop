
#pragma once
#include "StructuredData.h"
#include "Buffer.h"
#include <string>
#include <deque>
#include <stack>
#include <vector>

namespace Sexy
{

	class JsonReader
	{
	public:
		typedef uchar Char;
		typedef Char* Location;
		
		JsonReader();

		/**
		 * Read a UTF-8 encoded JSON character buffer into StructuredData.
		 * The buffer WILL BE modified.  Specifically, strings will be decoded
		 * and null-terminated and pointers to these strings within the
		 * buffer will be passed to the StructuredData instance.
		 * Returns false if there is an error.
		 */
		bool Read( const std::string& path,      /* out */ StructuredData* data, /* out, optional */ StructuredData* errors );
		bool Read( /* in */ Buffer* buffer,      /* out */ StructuredData* data, /* out, optional */ StructuredData* errors );
		bool Read( uchar* buffer, uint32 length, /* out */ StructuredData* data, /* out, optional */ StructuredData* errors );
		bool Read( uchar* begin, uchar* end,     /* out */ StructuredData* data, /* out, optional */ StructuredData* errors );
		
		/**
		 * Returns true if the buffer looks like it might contain JSON data.
		 */
		bool Inspect( Buffer* buffer );
		bool Inspect( uchar* buffer, uint32 length );
		bool Inspect( uchar* begin, uchar* end );
		
	private:
		enum TokenType
		{
			tokenEndOfStream = 0,
			tokenObjectBegin,
			tokenObjectEnd,
			tokenArrayBegin,
			tokenArrayEnd,
			tokenString,
			tokenNumber,
			tokenTrue,
			tokenFalse,
			tokenNull,
			tokenArraySeparator,
			tokenMemberSeparator,
			tokenComment,
			tokenError
		};
		
		struct Token
		{
			TokenType type;
			Location start;
			Location end;
			int32 line;
			int32 column;
		};
		
		typedef StructuredData::Value Value;
		typedef StructuredData::String String;
		typedef StructuredData::Integer Integer;
		typedef uint64 Unsigned;

		bool ReadValue( String name );
		bool ReadObject( Token &token );
		bool ReadArray( Token &token );
		bool DecodeNumber( Token &token, String name );
		bool ReadString( Token &token, String name );
		
		Char GetNextChar();
		void ScanWhitespace();
		void UpdateLineAndColumn( Char c );
		void ScanToken( Token &token );
		bool ScanExpectedToken( Token& token, TokenType expectedType, const char* errorMessage );
		void ScanCommentTokens( Token &token );
		bool ScanComment();
		bool ScanCStyleComment();
		bool ScanCppStyleComment();
		bool ScanPattern( const char* pattern, int patternLength );
		bool ScanString();
		void ScanNumber();

		bool DecodeString( Token &token, String& decoded );
		bool DecodeDouble( Token &token, String name );
		bool DecodeUnicodeCodePoint( Token &token, Location &current, Location end, uint32 &unicode );
		bool DecodeUnicodeEscapeSequence( Token &token, Location &current, Location end, uint32 &unicode );
		Location WriteCodePointToUTF8( uint32 cp, Location out );
		
		bool AddError( const std::string &message, Token &token, Location extra = 0 );
		bool AddErrorAndRecover( const std::string &message, Token &token, TokenType skipUntilToken );
		bool RecoverFromError( TokenType skipUntilToken );
		
		StructuredData* mData;
		StructuredData* mErrors;
		Location mBegin;
		Location mEnd;
		Location mCurrent;
		int32 mLine;
		int32 mColumn;
		Char mLineBreakTrackingChar;
	};

	inline bool JsonReader::Read( Buffer* buffer, StructuredData* data, StructuredData* errors )
	{
		return Read( buffer->GetDataPtr(), buffer->GetDataLen(), data, errors );
	}
	
	inline bool JsonReader::Read( uchar* buffer, uint32 length, StructuredData* data, StructuredData* errors )
	{
		return Read( buffer, buffer + length, data, errors );
	}
	
	inline bool JsonReader::Inspect( Buffer* buffer )
	{
		return Inspect( buffer->GetDataPtr(), buffer->GetDataLen() );
	}
	
	inline bool JsonReader::Inspect( uchar* buffer, uint32 length )
	{
		return Inspect( buffer, buffer + length );
	}
	
}
