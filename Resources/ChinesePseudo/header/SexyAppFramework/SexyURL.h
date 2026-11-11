
#pragma once
#include "Common.h"

/**
 * Section 2.1 (The main parts of URLs) of RFC 1738 tells us that URLS take
 * the following basic form:
 *   <scheme>:<scheme-specific-part>
 *
 * Section 3.1 (Common Internet Scheme Syntax) further tells us that most
 * schemes use a standard pattern for the scheme-specific-part:
 *   //<user>:<password>@<host>:<port>/<url-path>
 *
 * Section 3.3 (HTTP) adds it's own particularites:
 *   http://<host>:<port>/<path>?<searchpart>
 *
 * Section 2.1 (URL Syntactic Components) of RFC 1808 elaborates on this,
 * where net_loc is per Section 3.1 of RFC 1738 above:
 *   <scheme>://<net_loc>/<path>;<params>?<query>#<fragment>
 *
 * For common schemes, this gives us
 *   <scheme>://<user>:<password>@<host>:<port>/<path>;<params>?<query>#<fragment>
 * with most of those components being optional or disallowed according to the scheme.
 *
 * Uncommon schemes may use anything for scheme-specific-part so long as
 * it does not start with double forward slash ("//").
 *
 * Wikipedia gives us this really boss diagram, based on Section 3 (Syntax Components)
 * of RFC 3986 (URI: Generic Syntax).
 * (http://en.wikipedia.org/wiki/URI_scheme#Generic_syntax)
 *
 *   foo://username:password@example.com:8042/over/there/index.dtb?type=animal&name=narwhal#nose
 *   \_/   \_______________/ \_________/ \__/            \___/ \_/ \______________________/ \__/
 *    |           |               |       |                |    |            |                |
 *    |       userinfo         hostname  port              |    |          query          fragment
 *    |    \________________________________/\_____________|____|/ \__/ \____/ \__/ \_____/
 *    |                    |                          |    |    |    |     |     |     |
 * scheme              authority                    path   |    |    interpretable as keys
 *  name   \_______________________________________________|____|/         |           |
 *    |                         |                          |    |    interpretable as values
 *    |                 hierarchical part                  |    |
 *    |                                                    |    |
 *    |            path               interpretable as filename |
 *    |   ___________|____________                              |
 *   / \ /                        \                             |
 *   urn:example:animal:ferret:nose               interpretable as extension
 *
 * scheme
 *  name  userinfo  hostname       query
 *   _|__   ___|__   ____|____   _____|_____
 *  /    \ /      \ /         \ /           \
 *  mailto:username@example.com?subject=Topic
 *
 */
class SexyURL
{
public:
	SexyURL();
	SexyURL( const std::string& fromString );
	
	SexyURL& operator=( const std::string& fromString );
	
	bool IsEmpty();
	void Clear();

	const std::string& AbsoluteString() const;
	
	/**
	 * Returns the <scheme> part of the URL.  Because schemes are case-
	 * insensitive, it will be converted to lower-case before it is returned.
	 */
	std::string Scheme() const;
	
	/** Returns the <user> part of the URL. */
	std::string User() const;
	
	/** Returns the <password> part of the URL. */
	std::string Password() const;

	/**
	 * Returns the <host> portion of the URL.  Because host names are case-
	 * insensitive, it will be converted to lower-case before it is returned.
	 */
	std::string Host() const;
	
	/** Returns the <port> part of the URL. */
	std::string Port() const;
	
	/** Returns the <path> part of the URL. */
	std::string Path() const;
	
	/** Returns the <params> part of the URL.  Different than the <query> part. */
	std::string Params() const;
	
	/** Returns the <query> part of the URL. */
	std::string Query() const;
	
	/** Returns the <fragment> part of the URL. */
	std::string Fragment() const;
	
	/**
	 * Examines the query string for a key=value pair with the specified
	 * key and, if found, returns the value.  Before returning the value,
	 * percent escapes are decoded and '+' characters are replace with spaces
	 * (per the "application/x-www-form-urlencoded" MIME type).
	 */
	std::string QueryValueForKey( const char* key ) const;
	
	/**
	 * Like QueryValueForKey(), but the fragment is searched instead of the
	 * query string.  This feature is provided for decoding Facebook single-
	 * sign-on URLs.
	 */
	std::string FragmentValueForKey( const char* key ) const;
	
protected:
	
	struct Range
	{
		size_t begin;
		size_t end;
		Range() : begin( 0 ), end( 0 ) {}
		Range( size_t b, size_t e ) : begin( b ), end( e ) {}
		size_t length() const { return end - begin; }
		bool empty() const { return end <= begin; }
		void clear() { begin = 0; end = 0; }
	};
	
	struct KeyedValue
	{
		Range key;
		Range value;
	};
	typedef std::vector< KeyedValue > KeyedValues;
	
	std::string mAbsoluteString;
	Range mScheme;
	Range mUser;
	Range mPassword;
	Range mHost;
	Range mPort;
	Range mPath;
	Range mParams;
	Range mQuery;
	Range mFragment;
	
	mutable KeyedValues mQueryValues;
	mutable KeyedValues mFragmentValues;
	
	void ClearComponents();
	void IdentifyComponents();
	void CrackKeyedValues( Range source, char pairSeparator, const char keySeparator, KeyedValues& keyedValues ) const;
	std::string ValueForKey( const char* key, KeyedValues& keyedValues ) const;
	bool StringWithoutPrefix( const std::string& str, Range range, const char* prefix, Range* output ) const;
	bool SplitStringFromLeft( const std::string& str, Range range, char separator, Range* left, Range* right ) const;
	bool SplitStringFromRight( const std::string& str, Range range, char separator, Range* left, Range* right ) const;
	size_t SeparateStringIntoParts( const std::string& str, Range range, const char* separators, ... ) const;
	std::string DecodedPart( Range part ) const;
	std::string MinisculePart( Range part ) const;
	
};

