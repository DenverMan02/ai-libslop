#ifndef __SEXYAPPFRAMEWORK_ENUMS_H__
#define __SEXYAPPFRAMEWORK_ENUMS_H__

#include "Common.h"

namespace Sexy
{

//--------------------------------------------------------------------------
// Enum helpers

// Surround an enum "constant array" to set some basic default constants (first,
// last, end, count).
//
#define SEXY_ENUM_BEGIN(inPrefix)						\
	inPrefix##Invalid = -1,								\
	inPrefix##BeforeBegin = -1
#define SEXY_ENUM_END(inPrefix)							\
	inPrefix##End,										\
	inPrefix##Last  = inPrefix##End - 1,				\
	inPrefix##Begin = inPrefix##BeforeBegin + 1,		\
	inPrefix##Count = inPrefix##End - inPrefix##Begin,  \
	inPrefix##ForceUInt32 = 0x7FFFFFFF

// This macro allows you to use a typesafe bitflag parameter as a strict enum
// rather than simple an int or dword. The operators need to be defined so you
// can combine and test the component flags.
//
#define SEXY_ENUM_MAKE_BIT_OPERATORS(inEnumType)                   	\
	inline inEnumType operator | (inEnumType a, inEnumType b)     	\
		{  return (inEnumType)((int32)a | (int32)b); }              \
	inline inEnumType operator & (inEnumType a, inEnumType b)     	\
		{  return (inEnumType)((int32)a & (int32)b); }				\
	inline inEnumType operator ^ (inEnumType a, inEnumType b)		\
		{  return (inEnumType)((int32)a ^ (int32)b); }              \
	inline inEnumType operator ~ (inEnumType a)						\
		{  return (inEnumType)~(int32)a; }							\
	inline inEnumType operator |= (inEnumType& a, inEnumType b)		\
		{  return a = a | b; }                                      \
	inline inEnumType operator &= (inEnumType& a, inEnumType b)		\
		{  return a = a & b; }

// This macro allows you to use math operations on enums and still be
// relatively typesafe. Add more as you find the need.
//
#define SEXY_ENUM_MAKE_MATH_OPERATORS(inEnumType)                                   \
	inline inEnumType operator ++ (inEnumType& a)         /* prefix increment */  	\
		{  return a = (inEnumType)(a + 1);  }                                       \
	inline inEnumType operator ++ (inEnumType& a, int)    /* postfix increment */	\
		{  inEnumType old = a;  ++a;  return old;  }                                \
	inline inEnumType operator -- (inEnumType& a)         /* prefix decrement */	\
		{  return a = (inEnumType)(a - 1);  }                                       \
	inline inEnumType operator -- (inEnumType& a, int)    /* postfix decrement */	\
		{  inEnumType old = a;  --a;  return old;  }                                \
	inline inEnumType operator + (inEnumType a, inEnumType b)						\
		{  return (inEnumType)((int32)a + (int32)b); }                              \
	inline inEnumType operator - (inEnumType a, inEnumType b)						\
		{  return (inEnumType)((int32)a - (int32)b); }                              \
	inline inEnumType operator += (inEnumType& a, inEnumType b)						\
		{  return a = (inEnumType)(a + b); }                                        \
	inline inEnumType operator -= (inEnumType& a, inEnumType b)						\
		{  return a = (inEnumType)(a - b); }										\
	inline inEnumType operator + (inEnumType a, int32 b)							\
		{  return (inEnumType)((int32)a + b); }										\
	inline inEnumType operator - (inEnumType a, int32 b)							\
		{  return (inEnumType)((int32)a - b); }										\
	inline inEnumType operator += (inEnumType& a, int32 b)							\
		{  return a = (inEnumType)((int32)a + b); }									\
	inline inEnumType operator -= (inEnumType& a, int32 b)							\
		{  return a = (inEnumType)((int32)a - b); }									\
	inline inEnumType operator + (int32 a, inEnumType b)							\
		{  return (inEnumType)(a + (int32)b); }										\
	inline inEnumType operator - (int32 a, inEnumType b)							\
		{  return (inEnumType)(a - (int32)b); }										\
	inline int32 operator += (int32& a, inEnumType b)								\
		{  return a = a + (int32)b; }												\
	inline int32 operator -= (int32& a, inEnumType b)								\
		{  return a = a - (int32)b; }


} //namespace Sexy

#endif // __SEXYAPPFRAMEWORK_ENUMS_H__