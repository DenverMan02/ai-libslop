#pragma once
#include "Common.h"
#include "Debug.h"
#include "Buffer.h"
#include <sys/types.h>
#include <vector>
#include <stack>

namespace Sexy
{
	// ----------------------------------------------------------------------
	// class StructuredData declaration
	// ----------------------------------------------------------------------
	
	class StructuredData
	{
	public:
        
		/**
		 * Maintainance note: if these are changed, be sure to follow up
		 * in StructuredDataValidator::SchemaValueTypeFromString so that
		 * the schema type strings map onto this enumeration properly.
		 */
		enum ValueType
		{
			SD_NULL,
			SD_STRING,
			SD_NUMBER,
			SD_INTEGER,
			SD_BOOLEAN,
			SD_OBJECT,
			SD_ARRAY,
			SD_JSON,
			SD_VALUE_TYPE_COUNT,
		};
		
		/**
		 * We are making these typedefs here to establish which C++ types
		 * we are using for the JSON types, which are more abstract.
		 * String is ASCII/UTF-8.
		 */
		typedef char Character;
		typedef const Character* String;
		typedef double Number;
		typedef int64 Integer;
		typedef bool Boolean;

		enum InitializationMode
		{
			INITIALIZING,
			EMPTY_OBJECT,
			EMPTY_ARRAY,
		};
		
		class Value;
		
		static String noName;
		
		StructuredData();
		StructuredData( InitializationMode initMode );
		StructuredData( const StructuredData& that );
		StructuredData& operator=( const StructuredData& that );
        
		/**
		 * Returns true if the buffer appears to contain binary serialized
		 * StructuredData.
		 */
		static bool InspectBuffer( const Buffer* buffer );
		
		/**
		 * Read from a binary serialized buffer.  After this call, the instance
		 * will be Readable, not Mutable, with compact string storage.
		 */
		bool ReadFromBuffer( const Buffer* buffer );
		
		/**
		 * Write to a binary serialized buffer.  If necessary, the string
		 * storage will be converted from the "sparse" format to the
		 * standard compact format.  See GetBufferForTextRead().
		 */
		void WriteToBuffer( Buffer* buffer ) const;

		/**
		 * Clears this object and marks the internal state for "sparse"
		 * string storage.  This is used when parsing from JSON or
		 * similar text representations.  This instance will be both
		 * Readable and Mutable.  Returns a pointer to the string buffer
		 * for the purpose of pre-loading the text data.
		 */
		Buffer* GetBufferForTextRead();
		
		/**
		 * Reset this instance to initial state, which is Mutable, not
		 * Readable, and with compact string storage.
		 */
        void Clear();
		
		void Clone( const StructuredData& that );
		
		/** Reserve storage for count values.  Does not change Size(). */
        void Reserve( uint32 count );
		
		/** Returns the total number of values stored. */
        uint32 Size() const;
		
		/** Returns true if Size() would return 0. */
		bool Empty() const;
		
		/* Returns true if this instance object can be accessed for reading.
		 */
		bool Readable() const;
		
		/* Returns true if this instance can be modified with the
		 * Begin/End/Add methods.
		 */
		bool Mutable() const;

		/* See StructuredDataValidator for details. */
		bool Validate( const StructuredData* schema, StructuredData* errors );
		
        const Value* Root() const;
		
		/* Return the value indicated by a simplified JSONPath.
		 * The path must start with $, indicating the root node,
		 * followed by a sequence of child selectors, which take one of
		 * the following three forms.
		 *   .name     Selects a child of an Object by name.
		 *   ['name']  Selects a child of an Object by name.
		 *   [index]   Select a child of an Array by index.
		 * Returns NULL if the path does not match an instance.
		 */
		const Value* ValueForPath( String path ) const;
		
		/* The XXXForPath methods find a value as described by ValueForPath.
		 * If no value is found, or if the value is not of the requested type,
		 * then defaultValue (or NULL if there is no defaultValue) is returned.
		 */
		String StringForPath( String path, String defaultValue ) const;
		SexyString SexyStringForPath( String path, const SexyString& defaultValue ) const;
		Integer IntegerForPath( String path, Integer defaultValue ) const;
		Number NumberForPath( String path, Number defaultValue ) const;
		Boolean BooleanForPath( String path, Boolean defaultValue ) const;
		const Value* ObjectForPath( String path ) const;
		const Value* ArrayForPath( String path ) const;
		
		void AppendToQueryString( std::string& queryString ) const;
		
		void BeginObject( String name );
		void BeginObject();
		void EndObject();
		
		void BeginArray( String name );
		void BeginArray();
		void EndArray();
        
        void AddNull( String name );
		void AddNull();
		void AddString( String name, String stringValue );
		void AddString( String stringValue );
		void AddString( String name, const std::string& stringValue );
		void AddString( const std::string& stringValue );
#ifdef _USE_WIDE_STRING
		void AddString( String name, const SexyString& value );
		void AddString( const SexyString& value );
#endif
		void AddJSON( String name, String jsonValue );
		void AddNumber( String name, Number numberValue );
		void AddNumber( Number numberValue );
		void AddInteger( String name, Integer integerValue );
		void AddInteger( Integer integerValue );
		void AddBoolean( String name, Boolean booleanValue );
		void AddBoolean( Boolean booleanValue );
		void AddValue( String name, const Value* value );
		void AddValue( const Value* value );

        void BeginContainer( String name, ValueType containerType );
        void EndContainer( ValueType type );

		void SetNull( const Value*& container, String name );
		void SetString( const Value*& container, String name, String stringValue );
		void SetNumber( const Value*& container, String name, Number numberValue );
		void SetInteger( const Value*& container, String name, Integer integerValue );
		void SetBoolean( const Value*& container, String name, Boolean booleanValue );
		void SetValue( const Value*& container, String name, const Value* value );
		
		const StructuredData::Value* EraseValue( const Value*& container, String name );
		
		void WriteToConsole() const;

        void MakeStringsCompact() const;
		
		class Value
		{
		public:
			
			Value();
			
			String Name() const;
			ValueType Type() const;

			const Value* ValueForName( String name ) const;
			
			String StringForName( String name, String defaultValue = "" ) const;
			SexyString SexyStringForName( String name, SexyString defaultValue = SexyString() ) const;
			Integer IntegerForName( String name, Integer defaultValue = 0 ) const;
            StructuredData::Integer IntegerForNameForce( String name, Integer defaultValue ) const;
			Number NumberForName( String name, Number defaultValue = 0.0f ) const;
			Boolean BooleanForName( String name, Boolean defaultValue = false ) const;
			const Value* ObjectForName( String name ) const;
			const Value* ArrayForName( String name ) const;
			
			const Value* ValueAtIndex( std::ptrdiff_t index ) const;
			
			/* See StructuredData::ValueForPath for details.
			 * This method differs from that root level method in that you
			 * do not start the path with the root node indicator "$".
			 * Instead, the path argument to this method should begin directly
			 * with a child selector, such as ".name" or "[index]"
			 */
			const Value* ValueForPath( String path ) const;

			String StringForPath( String path, String defaultValue ) const;
			SexyString SexyStringForPath( String path, const SexyString& defaultValue ) const;
			Integer IntegerForPath( String path, Integer defaultValue ) const;
			Number NumberForPath( String path, Number defaultValue ) const;
			Boolean BooleanForPath( String path, Boolean defaultValue ) const;
			const Value* ObjectForPath( String path ) const;
			const Value* ArrayForPath( String path ) const;
			
			bool IsNull() const;
			bool IsString() const;
			bool IsNumber() const;
			bool IsInteger() const;
			bool IsBoolean() const;
			bool IsObject() const;
			bool IsArray() const;
			bool IsJSON() const;

			
			bool HasName() const;
			bool IsPrimitive() const;
			bool IsContainer() const;
			
			String GetString() const;
			String GetJSON() const;

			Integer GetInteger() const;
			Number GetNumber() const;
			Boolean GetBoolean() const;
			
			std::string StringValue() const;
			void AppendValueToString( std::string& str ) const;
			void AppendToQueryString( std::string& queryString ) const;

			const Value* ChildrenBegin() const;
			const Value* ChildrenEnd() const;
			uint32 ChildCount() const;
			const Value* FirstChild() const;
			const Value* Next() const;

		protected:
			
			friend class StructuredData;
			friend class StructuredDataValidator;

			struct Container
			{
				uint32 childCount;
				uint32 size;
			};
			
			union Storage
			{
				String asString;
				Number asNumber;
				Integer asInteger;
				Boolean asBoolean;
				Container asContainer;
			};

			uint32 Size() const;
			bool IsNamed( const Character* begin, const Character* end ) const;
			const Value* DefaultValueForProperty( const Character* begin, const Character* end ) const;
			void ReadFromBuffer( const Buffer* buffer, const Character* stringBasePointer, uint32 stringsSize, int32 version );
			void WriteToBuffer( Buffer* buffer, const Character* stringBasePointer ) const;
			void WriteToConsole( size_t index ) const;
			static size_t StringOffset( const String& string, const Character* stringBasePointer );
	
			ValueType mType;
			String mName;
			Storage mStorage;
			mutable const Value* mSchema;
			
		};
		
    protected:

		friend class StructuredDataValidator;
		friend class JsonReader;
		
		enum Mode
		{
			INITIALIZING_SPARSE,
			INITIALIZING_COMPACT,
			ACCESSING_SPARSE,
			ACCESSING_COMPACT,
		};
		
		bool Initializing() const;
		bool Sparse() const;
		
        std::ptrdiff_t IndexOfValue( const Value* value );
        Value* ValueAtIndex( std::ptrdiff_t index );
		
        Value* AddValue( String name, ValueType type );
		Value* SetPrimitive( const Value*& container, String name, ValueType type );
		Value* ReplaceValue( const Value*& container, String name, const Value* incomingValue );
		Value* ReplaceChild( const Value*& container, Value* childFirst, Value* childLast, const Value* withFirst, const Value* withLast );

		String InternalizeString( String s );
		String InternalizeString( const Character* str, size_t len );

		void IntegrateStringsAppendix() const;
		String EmbufferString( String str ) const;
		String EmbufferString( const std::string& str ) const;
		String EmbufferString( const Character* begin, const Character* end ) const;
		String EmbufferString( const Character* str, size_t len ) const;
		void RebaseStringPointers( const Character* fromBase, const Character* toBase ) const;
		String RebufferString( String str, Character** stringsEnd ) const;

		const Character* RebaseString( const Character* s, const Character* fromBase, const Character* toBase ) const;
		
#if 1
		uint32 Mark();
		void Rewind( uint32 mark );
		void Pop();
#endif

        typedef std::vector< Value > Values;
        typedef std::vector< uint32 > Stack;

		mutable Buffer mStrings;
		mutable Values mValues;
		mutable Mode mMode;
		mutable size_t mStringsAppendix;
        Stack mOpenContainer;
		const StructuredData* mSchema;

	};

	// ----------------------------------------------------------------------
	// class StructuredData inline implementation
	// ----------------------------------------------------------------------
	
	inline void StructuredData::AddString( String name, const std::string& stringValue )
	{
		AddString( name, stringValue.c_str() );
	}

#ifdef _USE_WIDE_STRING
	inline void StructuredData::AddString( String name, const SexyString& stringValue )
	{
		AddString( name, SexyStringToString( stringValue ) );
	}
#endif
	
	inline void StructuredData::BeginObject()
	{
		BeginObject( noName );
	}
	
	inline void StructuredData::BeginArray()
	{
		BeginArray( noName );
	}
	
	inline void StructuredData::AddNull()
	{
		AddNull( noName );
	}
	
	inline void StructuredData::AddString( String stringValue )
	{
		AddString( noName, stringValue );
	}
	
	inline void StructuredData::AddString( const std::string& stringValue )
	{
		AddString( noName, stringValue );
	}

#ifdef _USE_WIDE_STRING
	inline void StructuredData::AddString( const SexyString& stringValue )
	{
		AddString( noName, stringValue );
	}
#endif

	inline void StructuredData::AddNumber( Number numberValue )
	{
		AddNumber( noName, numberValue );
	}
	
	inline void StructuredData::AddInteger( Integer integerValue )
	{
		AddInteger( noName, integerValue );
	}
	
	inline void StructuredData::AddBoolean( Boolean booleanValue )
	{
		AddBoolean( noName, booleanValue );
	}

	inline void StructuredData::AddValue( const Value* value )
	{
		AddValue( noName, value );
	}
	
    inline std::ptrdiff_t StructuredData::IndexOfValue( const Value* value )
	{
		Value* valuesBegin = &mValues[0];
#if SEXY_IS_BUILD_DEBUG
		DBG_ASSERT( value >= valuesBegin );
#endif // SEXY_IS_BUILD_DEBUG
		return value - valuesBegin;
	}

    inline StructuredData::Value* StructuredData::ValueAtIndex( std::ptrdiff_t index )
	{
		Value* valuesBegin = &mValues.front();
		return valuesBegin + index;
	}
	
	inline const StructuredData::Character* StructuredData::RebaseString( const Character* s, const Character* fromBase, const Character* toBase ) const
	{
		return s ? ( s - fromBase + toBase ) : s;
	}
	
	// ----------------------------------------------------------------------
	// class StructuredData::Value inline implementation
	// ----------------------------------------------------------------------
	
	inline StructuredData::String StructuredData::Value::Name() const
	{
		return mName;
	}
	
	inline StructuredData::ValueType StructuredData::Value::Type() const
	{
		return mType;
	}
	
	inline uint32 StructuredData::Value::ChildCount() const
	{
		return mStorage.asContainer.childCount;
	}
	
	inline const StructuredData::Value* StructuredData::Value::FirstChild() const
	{
		return ChildrenBegin();
	}
	
	inline const StructuredData::Value* StructuredData::Value::Next() const
	{
		if ( IsContainer() )
		{
			return ChildrenEnd();
		}
		return this + 1;
	}
	
	inline const StructuredData::Value* StructuredData::Value::ChildrenBegin() const
	{
		DBG_ASSERT( IsContainer() );
		return this + 1;
	}
	
	inline const StructuredData::Value* StructuredData::Value::ChildrenEnd() const
	{
		DBG_ASSERT( IsContainer() );
		return this + mStorage.asContainer.size;
	}
	
	inline bool StructuredData::Value::IsNull() const
	{
		return SD_NULL == mType;
	}
	
	inline bool StructuredData::Value::IsString() const
	{
		return SD_STRING == mType;
	}
	
	inline bool StructuredData::Value::IsJSON() const
	{
		return SD_JSON == mType;
	}

	inline bool StructuredData::Value::IsNumber() const
	{
		return SD_NUMBER == mType || SD_INTEGER == mType;
	}
	
	inline bool StructuredData::Value::IsInteger() const
	{
		return SD_INTEGER == mType;
	}
	
	inline bool StructuredData::Value::IsBoolean() const
	{
		return SD_BOOLEAN == mType;
	}
	
	inline bool StructuredData::Value::IsObject() const
	{
		return SD_OBJECT == mType;
	}
	
	inline bool StructuredData::Value::IsArray() const
	{
		return SD_ARRAY == mType;
	}
	
	inline bool StructuredData::Value::HasName() const
	{
		return mName && *(mName);
	}
	
	inline bool StructuredData::Value::IsPrimitive() const
	{
		return ! IsContainer();
	}
	
	inline bool StructuredData::Value::IsContainer() const
	{
		return IsObject() || IsArray();
	}
	
	inline StructuredData::Integer StructuredData::Value::GetInteger() const
	{
		DBG_ASSERT( IsInteger() );
		return mStorage.asInteger;
	}
	
	inline StructuredData::Number StructuredData::Value::GetNumber() const
	{
		DBG_ASSERT( IsNumber() );
		return SD_NUMBER == mType ? mStorage.asNumber : mStorage.asInteger;
	}
	
	inline StructuredData::Boolean StructuredData::Value::GetBoolean() const
	{
		DBG_ASSERT( IsBoolean() );
		return mStorage.asBoolean;
	}
	
	inline StructuredData::String StructuredData::Value::GetString() const
	{
		DBG_ASSERT( IsString() );
		return mStorage.asString;
	}
	
	inline StructuredData::String StructuredData::Value::GetJSON() const
	{
		DBG_ASSERT( IsJSON() );
		return mStorage.asString;
	}

	inline uint32 StructuredData::Value::Size() const
	{
		if ( IsContainer() )
		{
			return mStorage.asContainer.size;
		}
		return 1;
	}

	inline bool StructuredData::Value::IsNamed( const Character* begin, const Character* end ) const
	{
		const Character* p = begin;
		const Character* n = mName;
		while ( p < end && *n )
		{
			if ( *p++ != *n++ )
			{
				return false;
			}
		}
		return ( p == end && *n == '\0' );
	}
	
}

