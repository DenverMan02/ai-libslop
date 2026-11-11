#pragma once
#ifndef __XPRINTF_H__
#define __XPRINTF_H__
//****************************************************************************
//**
//**  File     :  XPRINTF.H
//**  Summary  :  Header - xprintf (eXtended printf)
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
/*
	The "xprintf" functions are variations on some of the standard
	printf-style formatted string functions, but with some useful extensions.

	------------------------------
		New Types
	------------------------------

	The following types are supported by xprintf, in addition to the standard
	types of c,C,d,i,o,u,x,X,e,E,f,g,G,n,p,s,S :

	1) b and B : Binary Integer

	   The b and B types have been added to output an integer in binary,
	   analagous to the x and X types for hex, and the o type for octal.
	   There is normally no difference between the two, however if the #
	   flag is also used, then lowercase b will output a "0b" prefix,
	   while uppercase B will output a "0B" prefix.

	2) m : FourCC Magic Markers

	   The m type emits an integer as a FourCC, where each byte of the
	   32-bit integer argument is emitted as a character (this also works
	   for 64-bit "EightCC" values, when using I64).  If the output is
	   reversed from what is desired, the tilde flag can be used (see below).

	------------------------------
		New Flags
	------------------------------

	The following flags are supported by xprintf, in addition to the standard
	flags of -,+,0,space,# :

	1) ~ : Tilde Flag - Byte Swapped Integer

	   The integer types d,i,o,u,x,X,p,b,B,m support the ~ (tilde) flag,
	   which will do an endian byte-swap on the integer value.  This can be
	   very handy in certain porting situations.

	2) ^ : Caret Flag - Spaced Delimited Integer

	   The integer types d,i,o,u,x,X,p,b,B,m support the ^ (caret) flag,
	   which will put a space after every N characters in the output.
	   The value of N is passed as an additional argument, which is after
	   any asterisk-based width/precision arguments, but before the integer
	   value itself.  This is particularly useful for hex and binary values.

	3) ' : Quote Flag - Single-Quoted Character or Double-Quoted String

	   The character/string types c,C,s,S and the FourCC type m support
	   the ' (quote) flag, which will surround the output in quotes.
	   Characters and FourCCs are surrounded by single-quotes, and strings
	   are surrounded by double-quotes.  For example, %'s behaves like a
	   shorthand for \"%s\" .

	4) , : Comma Flag - Locale-specific Comma-Separated Integer (SexyAppFramework)

	   The integer types d,i,o,u,x,X,p,b,B,m support the , (comma) flag,
	   which will call SexyAppFramework's CommaSeparate function to process the
	   integer in a locale-friendly manner.  Since CommaSeparate outputs a string,
	   many other aspects of the format specifier could be ignored or conflicting,
	   and any integer argument (whether it be %d or %x) will be treated the same.
	   For this reason, when using this flag it is recommended to stick with the
	   simple specifier of %,d and not layer too many other specifiers beyond this.

	------------------------------
		Extended Syntax
	------------------------------

	In addition to the usual printf syntax, an alternative "extended" syntax
	is available which adds features such as positional arguments, custom
	argument types, and embedded comments.

	If the first character after a percent is { (left curly-brace), then the
	extended syntax is used, ending at a } (right curly-brace).

	1) Embedded Comments

	If the first character after the left curly-brace is a - (hyphen), then
	this indicates an embedded comment, which ends with a terminating -}
	(hyphen and right curly-brace).  In other words, the entire embedded
	comment is surrounded by %{- and -} .
	
	Embedded comments are skipped in the output, and are particularly valuable
	for globalization/localization situations where you want to provide some
	context for localizers but don't have any alternative means of providing
	commentary.  For example, the string:
	
	"My favorite color is %{-blue, no wait it's actually-}green." is output as
	"My favorite color is green." .

	2) Positional Arguments

	When not using embedded comments, the extended syntax uses any of the
	following layouts:

	%{type}
	%{position:type}
	%{type:params}
	%{position:type:params}

	In other words, there are up to three colon-delimited fields; the type
	field is required, and it can optionally be preceded by a position and/or
	followed by optional parameters.

	The "position" is a zero-based integer indicating the argument position;
	if not present then the position of the previous argument plus one is
	used (so the position keeps incrementing by default, which is the
	expected behavior for non-positional arguments).
	
	Note that whenever a positional argument is used, all arguments from
	previous positions must be used somewhere in the format string as well
	(even if they end up being zero-length in the output); they can be
	out-of-order, they just have to show up somewhere, in order for their
	types to be known so the stack can be handled properly.  For example,
	if you output %{2:d} then the argument from position 2 will be used,
	however that requires that the arguments from positions 0 and 1 also be
	present somewhere in the format string so that the location of position
	2's argument can be located on the stack.

	To simplify this requirement, if you want to effectively skip an argument
	but don't want to have to explicitly make it zero-length in the output,
	you can prefix your position integer with a @ (at) character; if an @ is
	used, then the argument will handled properly on the stack, but will be
	automatically skipped in the output.  For example, if the following call
	is made:

	xsnprintf(buf, bufSize, "%{@0:d}%{@1:f}%{2:s}%{@3:d}%{4:s}\n", 5, 51.f, "Hello", 999, " there!");

	Then buf will be filled with "Hello there!"; the other positional
	arguments are in the format string for stack purposes, but will not show
	up in the output (effectively the @ sign reads like a notational marker,
	i.e. "At Position is Type").

	The "type" is the argument type, which can either be one of the standard
	single-character types used by the normal printf syntax, or a custom
	type supported by a registered handler (described below).

	The "params", if present, are the combination [flags][width][.precision]
	when the type is a standard single-character printf type; for example, the
	printf-style string %0.*s would have an alternative syntax of %{s:0.*} ,
	%#04x would have an alternative syntax of %{x:#04} and so on.  When the
	type is a custom type, the params are passed into the type's handler, and
	the usage will be type-specific.

	3) Custom Types

	If the special custom type handler "register" is used, new handlers can be
	installed for custom types.  This is done by calling an xprintf function
	with the syntax "%{register:mytype}", where mytype is the name of the
	custom type.  This xprintf call takes two arguments; the first is a
	function pointer of type FTypeHandlerA or FTypeHandlerW (depending on
	whether an ansi or wide character xprintf function is called), and the
	second argument is an integer size of the custom type on the stack.

	For example, if you have the following handler function that can handle
	a custom type "vec3" that contains three floats:

	void Vec3Handler(IBufferWriterA* inWriter, const char* inType, va_list& ioVarArgs, char* inParams);

	You can register it by calling:

	xsnprintf(NULL, 0, "%{register:vec3}", Vec3Handler, 3*sizeof(float));

	Then whenever a vec3 shows up in a format string, for example %{vec3} ,
	then Vec3Handler will be called to process it.

	Note that handlers must always read their provided argument size from
	ioVarArgs (for example, Vec3Handler must always read three floats),
	otherwise the stack can end up in an indeterminate state.  If your
	handler doesn't take any arguments at all, you can pass in an argument
	size of zero.

	For convenience, if a wide-character wxprintf function is called that
	uses a custom type, but no FTypeHandlerW has been registered for that
	type, then the ansi FTypeHandlerA list will also be checked, and
	appropriate conversions made if necessary.  This prevents having to
	make two custom handlers for every custom type, in the common case
	when only ansi characters would be output anyway (such as for numeric
	types).  However, if your custom type works with real non-numeric
	text output, then you should consider making separate ansi and wide
	versions of your handlers.
	
	------------------------------
		Compatibility
	------------------------------

	A lot of effort has been made to ensure compatibility with standard
	printf behavior (or at least MSVC's behavior, at the time of this
	writing) when working with normal printf syntax, however there are a few
	small unavoidable discrepancies which you should be aware of:

	1) %% is the only legal percent-literal
	
	   According to Microsoft's documentation, "if a percent sign is followed
	   by a character that has no meaning as a format field, the character is
	   copied" literally.  This is the usual way of getting percent signs to
	   emit to the output, by using %%.
	   
	   Unfortunately, the set of other characters that "have no meaning as a
	   format field" is vague, especially when MS-specific extensions are
	   involved; for this reason as well as some others (like odd syntax
	   highlighting behavior in some editors), percent-literals tend to be
	   avoided by most developers, except in the specific case of %%.

	   To complicate things further, xprintf adds several new characters to
	   the set of ones that have "meaning as a format field", reducing the
	   already-bizarre set of legal percent-literals even further.  To prevent
	   this problem from getting out of control, xprintf takes an axe to this
	   whole situation, and states outright that %% is a special case, and no
	   other percent-literals are supported.

	2) I64 is the only legal size prefix
	
	   Microsoft supports some specific "size prefix" markers, inserted after
	   the precision but before the type character.  These are entirely
	   MS-specific, and many of them ultimately have minimal effect because of
	   the way that varargs are passed on the stack; they appear to be
	   extremely rarely used.
	   
	   At this time, the only one of these that is supported by xprintf is
	   "I64", because of the unique role it serves in supplying 64-bit
	   integers; the other size prefixes like "h", "ll", "w", "I32" etc. are
	   not currently available.
*/
//============================================================================
//    HEADERS
//============================================================================
#include <stdio.h>
#include <stdarg.h>

namespace xprintf {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
/*
	TBufferWriter (IBufferWriterA & IBufferWriterW)
	
	Interface used internally by xprintf to write to output buffers.
	Not normally used by client applications unless you need to call
	xibwprintf / wxibwprintf for some reason, or you want to register
	new custom type handlers (which will need to work with this interface).
*/
template <typename T> class TBufferWriter
{
public:
	// write a character to the output buffer; returns true if written successfully,
	// false if not (if the buffer is full etc).
	virtual bool BufferWriteChar(T inChar) = 0;

	// write string to buffer; if inLen is nonzero then at most that number of
	// characters should be written.  Returns number of characters actually written
	virtual int BufferWriteString(const T* inStr, int inLen=0) = 0;

	// make sure output buffer is currently null-terminated
	virtual void BufferTerminate() = 0;
	
	// get the output buffer as a string
	virtual const T* BufferGetString() = 0;
	
	// returns current write position within the buffer
	virtual int BufferGetPosition() const = 0;

	// returns whether output buffer is currently full
	virtual bool BufferIsFull() const = 0;
};
typedef TBufferWriter<char> IBufferWriterA;
typedef TBufferWriter<wchar_t> IBufferWriterW;

/*
	FTypeHandlerA / FTypeHandlerW
	Type handler callback functions, for custom types.  See documentation
	above for more information on how to register custom type handlers.

	When the callback is called from within the xprintf functions, inWriter will
	always be a valid writer (it should never be null), and inType will be the
	type being handled (so the same handler can be used for multiple types).
	The inParams argument is non-const because it points to temporary scratch
	memory, so you can alter it at will within the handler.

	Regardless of other behavior within the handler, it has one critical
	requirement: it *MUST* advance ioVarArgs by the exact size provided when
	the type was registered.  Failure to do this can cause improper stack
	handling, which would be very bad.  Also, please do not call xprintf
	functions from within type handlers themselves, in order to avoid nasty
	reentrancy issues.
*/
typedef void (*FTypeHandlerA)(IBufferWriterA* inWriter, const char* inType, va_list& ioVarArgs, char* inParams);
typedef void (*FTypeHandlerW)(IBufferWriterW* inWriter, const wchar_t* inType, va_list& ioVarArgs, wchar_t* inParams);

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
/*
	xibwprintf / wxibwprintf

	Fundamental xprintf functions, using an IBufferWriter* interface (hence
	the "ibw" in the name); other functions like xvsnprintf and xsnprintf
	are wrappers around these.  If you pass in a null buffer writer, an internal
	"null writer" implementation will be used instead (so that handlers will
	still always have a non-null writer interface).
*/
int xibwprintf(IBufferWriterA* inWriter, const char* inFmt, va_list inArgs);
int wxibwprintf(IBufferWriterW* inWriter, const wchar_t* inFmt, va_list inArgs);

/*
	xvsnprintf / wxvsnprintf

	Analogues to vsnprintf and vsnwprintf, respectively; uses xibwprintf
	and wxibwprintf internally.
*/
int xvsnprintf(char* inBuf, size_t inMaxCount, const char* inFmt, va_list inArgs);
int wxvsnprintf(wchar_t* inBuf, size_t inMaxCount, const wchar_t* inFmt, va_list inArgs);

/*
	xsnprintf / wxsnprintf

	Analogues to snprintf and snwprintf, respectively; uses xibwprintf
	and wxibwprintf internally.
*/
int xsnprintf(char* inBuf, size_t inMaxCount, const char* inFmt, ... );
int wxsnprintf(wchar_t* inBuf, size_t inMaxCount, const wchar_t* inFmt, ... );

//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace xprintf
//****************************************************************************
//**
//**    END HEADER XPRINTF.H
//**
//****************************************************************************
#endif // __XPRINTF_H__
