//
//  core.h
//  PlantsVersusZombies2
//
//  Created by Terrry Franguiadakis on 10/12/11.
//  Copyright 2011 Popcap. All rights reserved.
//

#ifndef PlantsVersusZombies2_core_h
#define PlantsVersusZombies2_core_h

#include <type_traits>

#include "Singleton.h"
#include "TimeMgr.h"

/*--------------------------------------------------------------------------*/
// Enum helpers

// Surround an enum "constant array" to set some basic default constants (first,
// last, end, count).

#define PVZ_BEGIN_ENUM(inPrefix)					\
inPrefix##Invalid = -1,								\
inPrefix##BeforeBegin = -1

#define PVZ_END_ENUM(inPrefix)						\
inPrefix##End,										\
inPrefix##Last  = inPrefix##End - 1,				\
inPrefix##Begin = inPrefix##BeforeBegin + 1,		\
inPrefix##Count = inPrefix##End - inPrefix##Begin

#define PVZ_BEGIN_FLAG_ENUM(inPrefix)				\
inPrefix##Invalid = -1,								\
inPrefix##BeforeBegin = -1,							\
inPrefix##None = 0,									\
inPrefix##_INDEX_INIT = -1

// PVZ_FLAG
//	- Use this to set up each entry in a flag enum
//	- ** Will cause a compile time error if you use more flags than are supported by sizeof(enum)! **
#define PVZ_FLAG(inName)							\
_INDEX_##inName,											/* Index */	\
_INDEX_ASSERT_##inName = 1 / (_INDEX_##inName - (sizeof(_INDEX_##inName) * 8)), /* Breaks compilation when you're out of flags! */ \
inName = (1LL << _INDEX_##inName),							/* Flag  */	\
_INDEX_RESET_##inName = _INDEX_##inName						/* Set up index for next flag */

#define PVZ_END_FLAG_ENUM(inPrefix)					\
inPrefix##End,										\
inPrefix##Everything = (1LL << inPrefix##End) - 1

// This macro allows you to use a typesafe bitflag parameter as a strict enum
// rather than simple an int or dword. The operators need to be defined so you
// can combine and test the component flags.
//
#define PVZ_MAKE_ENUM_BIT_OPERATORS(inEnumType) \
	inline inEnumType operator | (inEnumType a, inEnumType b) \
		{ return (inEnumType)(static_cast<typename std::underlying_type<inEnumType>::type>(a) | static_cast<typename std::underlying_type<inEnumType>::type>(b)); } \
	inline inEnumType operator & (inEnumType a, inEnumType b) \
		{ return (inEnumType)(static_cast<typename std::underlying_type<inEnumType>::type>(a) & static_cast<typename std::underlying_type<inEnumType>::type>(b)); } \
	inline inEnumType operator ^ (inEnumType a, inEnumType b) \
		{ return (inEnumType)(static_cast<typename std::underlying_type<inEnumType>::type>(a) ^ static_cast<typename std::underlying_type<inEnumType>::type>(b)); } \
	inline inEnumType operator ~ (inEnumType a) \
		{ return (inEnumType)~static_cast<typename std::underlying_type<inEnumType>::type>(a); } \
	inline inEnumType operator |= (inEnumType& a, inEnumType b) \
		{ return a = a | b; } \
	inline inEnumType operator &= (inEnumType& a, inEnumType b) \
		{ return a = a & b; }

template<typename Enum>
constexpr typename std::underlying_type<Enum>::type to_integral(Enum e)
{
	return static_cast<typename std::underlying_type<Enum>::type>(e);
}

// Returns 'true' if any of the bits in i_testFlag are set in i_testValue
template<typename T>
inline bool TestFlag(T i_testValue, T i_testFlag)
{
	return ((i_testValue & i_testFlag) != 0);
}
template<typename T>
inline bool TestAllFlags(T i_testValue, T i_testFlags)
{
	return ((i_testValue & i_testFlags) == i_testFlags);
}

template<typename T>
inline void SetFlag(T& io_value, T i_flag, bool i_on)
{
	if (i_on)
	{
		io_value |= (i_flag);
	}
	else
	{
		io_value &= ~(i_flag);
	}
}

template<typename T>
inline T ConvertIndexTo(int64 index)
{
	return (T)(1LL<<index);
}

// This macro allows you to use math operations on enums and still be
// relatively typesafe. Add more as you find the need.
//
#define PVZ_MAKE_ENUM_MATH_OPERATORS(inEnumType)                                  	\
inline inEnumType operator ++ (inEnumType& a)         /* prefix increment */  	\
{  return a = (inEnumType)(a + 1);  }                                       \
inline inEnumType operator ++ (inEnumType& a, int)    /* postfix increment */	\
{  inEnumType old = a;  ++a;  return old;  }                                \
inline inEnumType operator -- (inEnumType& a)         /* prefix decrement */	\
{  return a = (inEnumType)(a - 1);  }                                       \
inline inEnumType operator -- (inEnumType& a, int)    /* postfix decrement */	\
{  inEnumType old = a;  --a;  return old;  }                                \
inline inEnumType operator + (inEnumType a, inEnumType b)						\
{  return (inEnumType)((int)a + (int)b); }                                  \
inline inEnumType operator - (inEnumType a, inEnumType b)						\
{  return (inEnumType)((int)a - (int)b); }                                  \
inline inEnumType operator += (inEnumType& a, inEnumType b)						\
{  return a = (inEnumType)(a + b); }                                        \
inline inEnumType operator -= (inEnumType& a, inEnumType b)						\
{  return a = (inEnumType)(a - b); }										\
inline inEnumType operator + (inEnumType a, int b)								\
{  return (inEnumType)((int)a + b); }										\
inline inEnumType operator - (inEnumType a, int b)								\
{  return (inEnumType)((int)a - b); }										\
inline inEnumType operator += (inEnumType& a, int b)							\
{  return a = (inEnumType)((int)a + b); }									\
inline inEnumType operator -= (inEnumType& a, int b)							\
{  return a = (inEnumType)((int)a - b); }									\
inline inEnumType operator + (int a, inEnumType b)								\
{  return (inEnumType)(a + (int)b); }										\
inline inEnumType operator - (int a, inEnumType b)								\
{  return (inEnumType)(a - (int)b); }										\
inline int operator += (int& a, inEnumType b)									\
{  return a = a + (int)b; }													\
inline int operator -= (int& a, inEnumType b)									\
{  return a = a - (int)b; }


#define SAFE_DELETE(ptr) { if (ptr) {delete ptr; ptr = nullptr; }}
#define SAFE_DELETE_GAMEOBJ(ptr) { if (ptr.IsValid()) { ptr->Destroy(); } ptr.ClearId(); }


// Initialize a static vector in the current scope with the specified initial values
//
// Usage:
//		STATIC_VECTOR_INIT(std::string, k_propertyNames, "property1", "property2", "property3");
//		printf("%s", k_propertyNames[1].c_str()); // Outputs 'property2'
//
#define STATIC_VECTOR_INIT(innertype, name, ...) \
	static innertype name##_values[] = { __VA_ARGS__ }; \
	static std::vector<innertype> name(name##_values, name##_values + sizeof(name##_values) / sizeof(name##_values[0]));

#endif