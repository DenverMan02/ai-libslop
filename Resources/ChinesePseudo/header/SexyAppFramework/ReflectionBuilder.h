#pragma once
#ifndef __REFBUILDER_H__
#define __REFBUILDER_H__
//****************************************************************************
//**
//**  File     :  REFBUILDER.H
//**  Summary  :  Header - Reflection API - Manual Reflection Builder Macros
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
//============================================================================
//    HEADERS
//============================================================================
#include "Reflection.h"
#include "RtSerial.h"
#include <type_traits>

namespace Reflection {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================

/*
	Class Builder
*/

// classbuilder prologue

#define REFLECTION_CLASSBUILDER_BEGIN(xName) \
	{ \
		using namespace Reflection; \
		typedef xName DClassBuilderThisClass; \
		struct Local_Build_##xName \
		{ \
			static void Callback(IRefManualSymbolBuilder* inBuilder, RClass* inClass) \
			{ \
				RClassMember* lastClassMember__ = NULL;

// RtClass binding

#define REFLECTION_CLASSBUILDER_RTCLASS_BIND \
				{ \
					DClassBuilderThisClass::StaticGetClass()->SetBoundReflectionClass(inClass); \
					inClass->SetBoundRtClass(DClassBuilderThisClass::StaticGetClass()); \
				}

// ancestors

#define REFLECTION_CLASSBUILDER_ANCESTOR(xBaseClassName) \
                { \
                    static_assert(std::is_base_of<xBaseClassName, DClassBuilderThisClass>::value, "Mismatched Ancestor!"); \
                    RClass* ancestorClass__ = (RClass*)inBuilder->GetNamedType(#xBaseClassName)->GetDereferencedType(); \
                    DClassBuilderThisClass* nullObj__ = NULL; \
                    xBaseClassName* adjObj__ = static_cast<xBaseClassName*>(nullObj__); \
                    uintptr_t ptr__ = reinterpret_cast<uintptr_t>(adjObj__); \
                    DBG_ASSERT(TypeCanFitValue<uint32_t>(ptr__)); \
                    lastClassMember__ = inBuilder->BuildAncestor(inClass, ancestorClass__, (uint32)(ptr__)); \
                }

// fields
template <typename T, typename U, typename V> void ForceTypeCheck(U V::*)
{
    static_assert(std::is_same<T,U>::value || (std::is_enum<U>::value && std::is_same<T,int32>::value), "Mismatched reflection types.");
}

#define REFLECTION_CLASSBUILDER_FIELD_UNSAFE(xType, xFieldName) \
                { \
                    static_assert(!std::is_fundamental<xType>::value, "Unsafe serialization not allowed for fundamental types."); \
                    lastClassMember__ = inBuilder->BuildField(inClass, #xFieldName, offsetof(DClassBuilderThisClass, xFieldName), inBuilder->GetType<xType>(#xType)); \
                }


#define REFLECTION_CLASSBUILDER_FIELD(xType, xFieldName) \
				{ \
                    ForceTypeCheck<xType>(&DClassBuilderThisClass::xFieldName); \
					lastClassMember__ = inBuilder->BuildField(inClass, #xFieldName, offsetof(DClassBuilderThisClass, xFieldName), inBuilder->GetType<xType>(#xType)); \
				}

// [PVZ2 CHANGE BEGIN] (amcgee) Added a way to specify the fieldname in the json file that differs from the variable name
#define REFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(xType, xVariable, xFieldName) \
				{ \
					ForceTypeCheck<xType>(&DClassBuilderThisClass::xVariable); \
					lastClassMember__ = inBuilder->BuildField(inClass, #xFieldName, offsetof(DClassBuilderThisClass, xVariable), inBuilder->GetType<xType>(#xType)); \
				}
// [PVZ2 CHANGE END]
// A way to specify the fieldname in the json file that differs from the variable name
#define REFLECTION_CLASSBUILDER_FIELD_RENAME(xType, xVariable, xFieldName) \
				{ \
					ForceTypeCheck<xType>(&DClassBuilderThisClass::xVariable); \
					lastClassMember__ = inBuilder->BuildField(inClass, #xFieldName, offsetof(DClassBuilderThisClass, xVariable), inBuilder->GetType<xType>(#xType)); \
				}
#define REFLECTION_CLASSBUILDER_FIELD_RENAME_UNSAFE(xType, xVariable, xFieldName) \
                { \
                    lastClassMember__ = inBuilder->BuildField(inClass, #xFieldName, offsetof(DClassBuilderThisClass, xVariable), inBuilder->GetType<xType>(#xType)); \
                }

#define REFLECTION_CLASSBUILDER_FIELD_READONLY(xType, xFieldName) \
				{ \
					REFLECTION_CLASSBUILDER_FIELD(xType, xFieldName); \
						REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(readonly, true); \
				}

// function types (mostly internal)

#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<void>(), 1, inBuilder->GetType<RtSerialCommand*>("RtSerialCommand*"))

#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0 \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<void>(), 0)
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_1(xArg0) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<void>(), 1, inBuilder->GetType<xArg0>(#xArg0))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_2(xArg0, xArg1) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<void>(), 2, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_3(xArg0, xArg1, xArg2) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<void>(), 3, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_4(xArg0, xArg1, xArg2, xArg3) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<void>(), 4, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2), inBuilder->GetType<xArg3>(#xArg3))

#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0wRet(xReturnType) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<xReturnType>(#xReturnType), 0)
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_1wRet(xReturnType, xArg0) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<xReturnType>(#xReturnType), 1, inBuilder->GetType<xArg0>(#xArg0))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_2wRet(xReturnType, xArg0, xArg1) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<xReturnType>(#xReturnType), 2, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_3wRet(xReturnType, xArg0, xArg1, xArg2) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<xReturnType>(#xReturnType), 3, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_4wRet(xReturnType, xArg0, xArg1, xArg2, xArg3) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, inClass, inBuilder->GetType<xReturnType>(#xReturnType), 4, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2), inBuilder->GetType<xArg3>(#xArg3))

#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_0 \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<void>(), 0)
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_1(xArg0) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<void>(), 1, inBuilder->GetType<xArg0>(#xArg0))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_2(xArg0, xArg1) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<void>(), 2, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_3(xArg0, xArg1, xArg2) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<void>(), 3, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_4(xArg0, xArg1, xArg2, xArg3) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<void>(), 4, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2), inBuilder->GetType<xArg3>(#xArg3))

#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_0wRet(xReturnType) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<xReturnType>(#xReturnType), 0)
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_1wRet(xReturnType, xArg0) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<xReturnType>(#xReturnType), 1, inBuilder->GetType<xArg0>(#xArg0))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_2wRet(xReturnType, xArg0, xArg1) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<xReturnType>(#xReturnType), 2, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_3wRet(xReturnType, xArg0, xArg1, xArg2) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<xReturnType>(#xReturnType), 3, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2))
#define REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_4wRet(xReturnType, xArg0, xArg1, xArg2, xArg3) \
	inBuilder->GetFunctionType(RFunctionType::CT_Delegate, 0, inBuilder->GetType<xReturnType>(#xReturnType), 4, inBuilder->GetType<xArg0>(#xArg0), inBuilder->GetType<xArg1>(#xArg1), inBuilder->GetType<xArg2>(#xArg2), inBuilder->GetType<xArg3>(#xArg3))

// properties

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE_ASTYPE(xType, xSerialType, xPropName, xGetterMethod, xSetterMethod) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandSet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inThis->xSetterMethod((xSerialType)inCmd->mArgs->Read<xSerialType>(inCmd->mArgKey)); \
						} \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inCmd->mReturns->Write<xSerialType>(inCmd->mReturnKey, (xSerialType)inThis->xGetterMethod()); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> setDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandSet); \
					RMethod* setMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertySet", &setDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, setMethod__); \
				}

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE_READONLY_ASTYPE(xType, xSerialType, xPropName, xGetterMethod) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inCmd->mReturns->Write<xSerialType>(inCmd->mReturnKey, (xSerialType)inThis->xGetterMethod()); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, NULL); \
				}

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_STATIC_ASTYPE(xType, xSerialType, xPropName, xGetterFunc, xSetterFunc) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandSet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							xSetterFunc(inThis, (xSerialType)inCmd->mArgs->Read<xSerialType>(inCmd->mArgKey)); \
						} \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inCmd->mReturns->Write<xSerialType>(inCmd->mReturnKey, (xSerialType)xGetterFunc(inThis)); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> setDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandSet); \
					RMethod* setMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertySet", &setDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, setMethod__); \
				}

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_STATIC_READONLY_ASTYPE(xType, xSerialType, xPropName, xGetterFunc) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inCmd->mReturns->Write<xSerialType>(inCmd->mReturnKey, (xSerialType)xGetterFunc(inThis)); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, NULL); \
				}

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE(xType, xPropName, xGetterMethod, xSetterMethod) \
				REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE_ASTYPE(xType, xType, xPropName, xGetterMethod, xSetterMethod)

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE_READONLY(xType, xPropName, xGetterMethod) \
				REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_INSTANCE_READONLY_ASTYPE(xType, xType, xPropName, xGetterMethod)

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_STATIC(xType, xPropName, xGetterFunc, xSetterFunc) \
				REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_STATIC_ASTYPE(xType, xType, xPropName, xGetterFunc, xSetterFunc)

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_STATIC_READONLY(xType, xPropName, xGetterFunc) \
				REFLECTION_CLASSBUILDER_COMMANDPROPERTY_AUTO_STATIC_READONLY_ASTYPE(xType, xType, xPropName, xGetterFunc)

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_MANUAL_INSTANCE(xType, xPropName, xGetterMethod, xSetterMethod) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandSet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inThis->xSetterMethod(inCmd); \
						} \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inThis->xGetterMethod(inCmd); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> setDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandSet); \
					RMethod* setMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertySet", &setDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, setMethod__); \
				}

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_MANUAL_INSTANCE_READONLY(xType, xPropName, xGetterMethod) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							inThis->xGetterMethod(inCmd); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, NULL); \
				}

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_MANUAL_STATIC(xType, xPropName, xGetterFunc, xSetterFunc) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandSet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							xSetterFunc(inCmd); \
						} \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							xGetterFunc(inCmd); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> setDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandSet); \
					RMethod* setMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertySet", &setDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, setMethod__); \
				}

#define REFLECTION_CLASSBUILDER_COMMANDPROPERTY_MANUAL_STATIC_READONLY(xType, xPropName, xGetterFunc) \
				{ \
					struct Local_CmdProperty_##xPropName \
					{ \
						static void CommandGet(DClassBuilderThisClass* inThis, RtSerialCommand* inCmd) \
						{ \
							xGetterFunc(inCmd); \
						} \
					}; \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> getDelegate__ = MakeDelegate(Local_CmdProperty_##xPropName::CommandGet); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_CmdPropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, NULL); \
				}

#define REFLECTION_CLASSBUILDER_NATIVEPROPERTY_INSTANCE(xType, xPropName, xGetterMethod, xSetterMethod) \
				{ \
					static Delegate0wRet<xType> getDelegate__ = MakeDelegate(*((DClassBuilderThisClass*)NULL), &DClassBuilderThisClass::xGetterMethod); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_PropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0wRet(xType)); \
					static Delegate1<xType> setDelegate__ = MakeDelegate(*((DClassBuilderThisClass*)NULL), &DClassBuilderThisClass::xSetterMethod); \
					RMethod* setMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_PropertySet", &setDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_1(xType)); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, setMethod__); \
				}
#define REFLECTION_CLASSBUILDER_NATIVEPROPERTY_INSTANCE_READONLY(xType, xPropName, xGetterMethod) \
				{ \
					static Delegate0wRet<xType> getDelegate__ = MakeDelegate(*((DClassBuilderThisClass*)NULL), &DClassBuilderThisClass::xGetterMethod); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_PropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0wRet(xType)); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, NULL); \
				}

#define REFLECTION_CLASSBUILDER_NATIVEPROPERTY_STATIC(xType, xPropName, xGetterFunc, xSetterFunc) \
				{ \
					static Delegate1wRet<xType, DClassBuilderThisClass*> getDelegate__ = MakeDelegate(xGetterFunc); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_PropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0wRet(xType)); \
					static Delegate2<DClassBuilderThisClass*, xType> setDelegate__ = MakeDelegate(xSetterFunc); \
					RMethod* setMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_PropertySet", &setDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_1(xType)); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, setMethod__); \
				}
#define REFLECTION_CLASSBUILDER_NATIVEPROPERTY_STATIC_READONLY(xType, xPropName, xGetterFunc) \
				{ \
					static Delegate1wRet<xType, DClassBuilderThisClass*> getDelegate__ = MakeDelegate(xGetterFunc); \
					RMethod* getMethod__ = inBuilder->BuildMethod(inClass, #xPropName "_PropertyGet", &getDelegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0wRet(xType)); \
					lastClassMember__ = inBuilder->BuildProperty(inClass, #xPropName, inBuilder->GetType<xType>(#xType), getMethod__, NULL); \
				}

// methods - static / noreturn

#define REFLECTION_CLASSBUILDER_METHOD_STATIC_NORETURN_NOARGS(xName, xMethod) \
				{ \
					static Delegate0 delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_0 ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_NORETURN_ONEARG(xName, xMethod, xArg0) \
				{ \
					static Delegate1<xArg0> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_1(xArg0)); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_NORETURN_TWOARGS(xName, xMethod, xArg0, xArg1) \
				{ \
					static Delegate2<xArg0, xArg1> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_2(xArg0, xArg1)); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_NORETURN_THREEARGS(xName, xMethod, xArg0, xArg1, xArg2) \
				{ \
					static Delegate3<xArg0, xArg1, xArg2> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_3(xArg0, xArg1, xArg2)); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_NORETURN_FOURARGS(xName, xMethod, xArg0, xArg1, xArg2, xArg3) \
				{ \
					static Delegate4<xArg0, xArg1, xArg2, xArg3> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_4(xArg0, xArg1, xArg2, xArg3)); \
				}

// methods - static / withreturn

#define REFLECTION_CLASSBUILDER_METHOD_STATIC_WITHRETURN_NOARGS(xName, xMethod, xReturnType) \
				{ \
					static Delegate0wRet<xReturnType> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_0wRet(xReturnType) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_WITHRETURN_ONEARG(xName, xMethod, xReturnType, xArg0) \
				{ \
					static Delegate1wRet<xReturnType, xArg0> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_1wRet(xReturnType, xArg0) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_WITHRETURN_TWOARGS(xName, xMethod, xReturnType, xArg0, xArg1) \
				{ \
					static Delegate2wRet<xReturnType, xArg0, xArg1> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_2wRet(xReturnType, xArg0, xArg1) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_WITHRETURN_THREEARGS(xName, xMethod, xReturnType, xArg0, xArg1, xArg2) \
				{ \
					static Delegate3wRet<xReturnType, xArg0, xArg1, xArg2> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_3wRet(xReturnType, xArg0, xArg1, xArg2) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_STATIC_WITHRETURN_FOURARGS(xName, xMethod, xReturnType, xArg0, xArg1, xArg2, xArg3) \
				{ \
					static Delegate4wRet<xReturnType, xArg0, xArg1, xArg2, xArg3> delegate__ = MakeDelegate(xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_4wRet(xReturnType, xArg0, xArg1, xArg2, xArg3) ); \
				}

// methods - instance / noreturn

#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS(xName, xMethod) \
				{ \
					static Delegate0 delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0 ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(xName, xMethod, xArg0) \
				{ \
					static Delegate1<xArg0> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_1(xArg0) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_TWOARGS(xName, xMethod, xArg0, xArg1) \
				{ \
					static Delegate2<xArg0, xArg1> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_2(xArg0, xArg1) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_THREEARGS(xName, xMethod, xArg0, xArg1, xArg2) \
				{ \
					static Delegate3<xArg0, xArg1, xArg2> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_3(xArg0, xArg1, xArg2) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_FOURARGS(xName, xMethod, xArg0, xArg1, xArg2, xArg3) \
				{ \
					static Delegate4<xArg0, xArg1, xArg2, xArg3> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_4(xArg0, xArg1, xArg2, xArg3) ); \
				}

// methods - instance / withreturn

#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_WITHRETURN_NOARGS(xName, xMethod, xReturnType) \
				{ \
					static Delegate0wRet<xReturnType> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_0wRet(xReturnType) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_WITHRETURN_ONEARG(xName, xMethod, xReturnType, xArg0) \
				{ \
					static Delegate1wRet<xReturnType, xArg0> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_1wRet(xReturnType, xArg0) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_WITHRETURN_TWOARGS(xName, xMethod, xReturnType, xArg0, xArg1) \
				{ \
					static Delegate2wRet<xReturnType, xArg0, xArg1> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_2wRet(xReturnType, xArg0, xArg1) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_WITHRETURN_THREEARGS(xName, xMethod, xReturnType, xArg0, xArg1, xArg2) \
				{ \
					static Delegate3wRet<xReturnType, xArg0, xArg1, xArg2> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_3wRet(xReturnType, xArg0, xArg1, xArg2) ); \
				}
#define REFLECTION_CLASSBUILDER_METHOD_INSTANCE_WITHRETURN_FOURARGS(xName, xMethod, xReturnType, xArg0, xArg1, xArg2, xArg3) \
				{ \
					static Delegate4wRet<xReturnType, xArg0, xArg1, xArg2, xArg3> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_INSTANCE_4wRet(xReturnType, xArg0, xArg1, xArg2, xArg3) ); \
				}

// methods - command

#define REFLECTION_CLASSBUILDER_COMMANDMETHOD_INSTANCE(xName, xMethod) \
				{ \
					static Delegate1<RtSerialCommand*> delegate__ = MakeDelegate(*((DClassBuilderThisClass*)0), &DClassBuilderThisClass::xMethod); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
				}
#define REFLECTION_CLASSBUILDER_COMMANDMETHOD_STATIC(xName, xFunc) \
				{ \
					static Delegate2<DClassBuilderThisClass*, RtSerialCommand*> delegate__ = MakeDelegate(xFunc); \
					lastClassMember__ = inBuilder->BuildMethod(inClass, #xName, &delegate__, REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND, true ); \
				}

// events - noreturn

#define REFLECTION_CLASSBUILDER_EVENT_NORETURN_NOARGS(xEventName) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_0 ); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_NORETURN_ONEARG(xEventName, xArg0) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_1(xArg0)); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_NORETURN_TWOARGS(xEventName, xArg0, xArg1) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_2(xArg0, xArg1)); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_NORETURN_THREEARGS(xEventName, xArg0, xArg1, xArg2) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_3(xArg0, xArg1, xArg2)); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_NORETURN_FOURARGS(xEventName, xArg0, xArg1, xArg2, xArg3) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_4(xArg0, xArg1, xArg2, xArg3)); \
				}

// events - withreturn

#define REFLECTION_CLASSBUILDER_EVENT_WITHRETURN_NOARGS(xEventName, xReturnType) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_0wRet(xReturnType) ); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_WITHRETURN_ONEARG(xEventName, xReturnType, xArg0) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_1wRet(xReturnType, xArg0) ); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_WITHRETURN_TWOARGS(xEventName, xReturnType, xArg0, xArg1) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_2wRet(xReturnType, xArg0, xArg1) ); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_WITHRETURN_THREEARGS(xEventName, xReturnType, xArg0, xArg1, xArg2) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_3wRet(xReturnType, xArg0, xArg1, xArg2) ); \
				}
#define REFLECTION_CLASSBUILDER_EVENT_WITHRETURN_FOURARGS(xEventName, xReturnType, xArg0, xArg1, xArg2, xArg3) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_STATIC_4wRet(xReturnType, xArg0, xArg1, xArg2, xArg3) ); \
				}

// events - command

#define REFLECTION_CLASSBUILDER_COMMANDEVENT(xEventName) \
				{ \
					lastClassMember__ = inBuilder->BuildEvent(inClass, #xEventName, offsetof(DClassBuilderThisClass, xEventName), REFLECTION_CLASSBUILDER_FUNCTIONTYPE_SERIALCOMMAND ); \
				}

// attributes

#define REFLECTION_CLASSBUILDER_CLASSATTRIBUTE(xName, xValue) \
				inClass->GetMutableAttributes()->AddSymbol(#xName, inBuilder->BuildAttribute(#xName, xValue));
#define REFLECTION_CLASSBUILDER_MEMBERATTRIBUTE(xName, xValue) \
				lastClassMember__->GetMutableAttributes()->AddSymbol(#xName, inBuilder->BuildAttribute(#xName, xValue));

// classbuilder epilogue

#define REFLECTION_CLASSBUILDER_END(xName) \
			(void)&lastClassMember__; \
			} \
		}; \
		IRefManualSymbolBuilder* symBuilder__ = NULL; \
		CRefSymbolDb* symDb__ = CRefSymbolDb::GetManualReflection(); \
		if (symDb__) \
			symBuilder__ = symDb__->GetManualSymbolBuilder(); \
		if (symBuilder__) \
			symBuilder__->AddClass(#xName, Local_Build_##xName::Callback, sizeof(xName)); \
	}

/*
	Enum Builder
*/

// enumbuilder prologue

#define REFLECTION_ENUMBUILDER_BEGIN(xName) \
	{ \
		using namespace Reflection; \
		bool enumBuilderMembersAreFlags__ = false; \
		std::vector<IRefManualSymbolBuilder::DEnumMemberPair> enumBuilderMembers__;

// members

#define REFLECTION_ENUMBUILDER_MEMBER(xMemberName) \
		enumBuilderMembers__.push_back(IRefManualSymbolBuilder::DEnumMemberPair(#xMemberName, xMemberName));
	
// A way to provide a different name for an enum value	
#define REFLECTION_ENUMBUILDER_MEMBER_RENAME(xMemberName, xMemberValue) \
		enumBuilderMembers__.push_back(IRefManualSymbolBuilder::DEnumMemberPair(#xMemberName, xMemberValue));

#define REFLECTION_ENUMBUILDER_MEMBERS_ARE_FLAGS \
		enumBuilderMembersAreFlags__ = true;

// enumbuilder epilogue

#define REFLECTION_ENUMBUILDER_END(xName) \
		IRefManualSymbolBuilder* symBuilder__ = NULL; \
		CRefSymbolDb* symDb__ = CRefSymbolDb::GetManualReflection(); \
		if (symDb__) \
			symBuilder__ = symDb__->GetManualSymbolBuilder(); \
		if (symBuilder__) \
			symBuilder__->AddEnum(#xName, enumBuilderMembers__, enumBuilderMembersAreFlags__); \
	}

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace Sexy
//****************************************************************************
//**
//**    END HEADER REFBUILDER.H
//**
//****************************************************************************
#endif // __REFBUILDER_H__
