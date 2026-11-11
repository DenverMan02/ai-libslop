#pragma once
#ifndef __REFLECTIONTAGS_H__
#define __REFLECTIONTAGS_H__
//****************************************************************************
//**
//**  File     :  REFLECTIONTAGS.H
//**  Summary  :  Header - Reflection - Attribute Tags
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
#ifndef SUPPORT_AUTOREFLECTION
	// Reflection API is not supported for releasefinal builds; attribute tag macros are stubbed out
	#define REFLECT_EXPORT
	#define REFLECT_ATTR_CLASS(xAttrType, xKey, xValue)
	#define REFLECT_ATTR_FIELD(xFieldName, xAttrType, xKey, xValue)
	#define REFLECT_ATTR_METHOD(xMethodName, xAttrType, xKey, xValue)
	#define REFLECT_ATTR_ENUM_FLAGS
#else
	#define REFLECT_EXPORT __declspec(dllexport)

	// class attribute
	#define REFLECT_ATTR_CLASS(xAttrType, xKey, xValue) \
		static REFLECT_EXPORT xAttrType __cdecl REFLECT_ATTR$CLASS$##xKey() { return xValue; }

	// field attribute
	#define REFLECT_ATTR_FIELD(xFieldName, xAttrType, xKey, xValue) \
		static REFLECT_EXPORT xAttrType __cdecl REFLECT_ATTR$FIELD$##xFieldName##$##xKey() { return xValue; }

	// method attribute
	#define REFLECT_ATTR_METHOD(xMethodName, xAttrType, xKey, xValue) \
		static REFLECT_EXPORT xAttrType __cdecl REFLECT_ATTR$METHOD$##xMethodName##$##xKey() { return xValue; } \

	// enum attributes (special case)
	#define REFLECT_ATTR_ENUM_FLAGS \
		REFLECT_ATTR$ENUM$FLAGS = 0xffffffff
#endif

// common attributes
#define RA_DISPLAYFIELDTYPE(xFieldName, xTypeStr) REFLECT_ATTR_FIELD(xFieldName, const char*, DisplayType, xTypeStr)

// common meta-methods
#define RA_METAMETHOD_TOSTRING(xMethodName) \
	REFLECT_ATTR_CLASS(const char*, ToStringMethod, #xMethodName "Proxy") \
	REFLECT_EXPORT void __cdecl xMethodName##Proxy(char* theBuffer, int theBufferLen) \
	{ \
		std::string s = xMethodName(); \
		strncpy_s(theBuffer, theBufferLen, s.c_str(), theBufferLen); \
	} \
	std::string xMethodName()


//****************************************************************************
//**
//**    END HEADER REFLECTIONTAGS.H
//**
//****************************************************************************
#endif // __REFLECTIONTAGS_H__
