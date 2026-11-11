//**************** RtDelegate.h **********************
// (Also variously known as callback.h, BlindCallback.h, etc.)
// Copyright 1994 Rich Hickey
/* Permission to use, copy, modify, distribute and sell this software
 * for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Rich Hickey makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
*/

#ifndef __RTDELEGATE_H__
#define __RTDELEGATE_H__

#pragma once

// 08/31/96 Rich Hickey
// Added ==, != and <
//  They are not inline, source is in file callback.cpp
//  Note: You must compile and link in callback.obj if you use them
// C++ doesn't allow ptr-to-func to void * anymore -> changed to void (*)(void)
// Added compiler workarounds for MS VC++ 4.2
// Prefixed all macros with RHCB
// Note: derivation from DelegateBase is now public, and access functions
// (for func, callee etc) are provided >>for implementation use only<<

// 06/12/94 Rich Hickey
// 3rd major revision
// Now delegates are concrete classes, and should be held by value
// Virtual function mechanism removed
// Generic MakeDelegate() mechanism added for building delegates
// from both stand-alone functions and object/ptr-to-mem-func pairs

// 7/10/98 Casey Muratori
// Modified to work with MSVC 5.0 SP3

// 1/13/00 Scott Bilas
// Added member templates to get rid of dummy delegate* 0 first argument in
//  calls to MakeDelegate.
// Made comparisons optional to speed up delegate creation.

// 11/04/11 Chris Hargrove
// Added RHCB_NAMESPACE support for when an isolated namespace is needed
// Modified the template argument order for the Delegate#wRet forms
//  such that the return type is on the left of the template argument
//  list (rather than the right), to make it read more like a C++
//  method declaration; updated relevant doc comments accordingly.
// Added Invoke support using simple variant class to handle common
//  invoke situations (mostly base data types; complex argument/return
//  types should be passed via pointer).
// Renamed "CBFunctor" to "Delegate" to avoid terminology confusion,
//  since we can't typedef the template classes, and "delegate" is
//  a better match for our C#-ish event/delegate (signals and slots)
//  way of thinking.  Updated most comments to match.
// Added C#-style multicast "Event" classes corresponding to the
//  various delegate class signatures; not very documented at the
//  moment but if you've used C# events before you shouldn't be too
//  surprised by what they do; see "Event Section" for details (the
//  code's not too big since the delegates themselves still do most
//  of the underlying work).
// Matching the Delegate and Event pairing, added a primitive (but
//  still useful) DelegateClosure class to wrap around the common
//  case of "callback function with some environmental context".
//  See DelegateClosure for details.

/*
To use:

If you wish to build a component that provides/needs a callback, simply
specify and hold a Delegate of the type corresponding to the args
you wish to pass and the return value you need. There are 10 Delegates
from which to choose:

Delegate0
Delegate1<P1>
Delegate2<P1,P2>
Delegate3<P1,P2,P3>
Delegate4<P1,P2,P3,P4>
Delegate0wRet<RT>
Delegate1wRet<RT,P1>
Delegate2wRet<RT,P1,P2>
Delegate3wRet<RT,P1,P2,P3>
Delegate4wRet<RT,P1,P2,P3,P4>

These are parameterized by their args and return value if any. Each has
a default ctor and an operator() with the corresponding signature.

They can be treated and used just like ptr-to-functions.

If you want to be a client of a component that uses callbacks, you
create a Delegate by calling MakeDelegate().

There are three flavors of MakeDelegate - you can create a delegate from:

a ptr-to-stand-alone function
an object and a pointer-to-member function.
a pointer-to-member function (which will be called on first arg of delegate)

Note: this last was not covered in the article - see CBEXAM3.CPP

The current iteration of this library requires you pass MakeDelegate()
a dummy first argument of type ptr-to-the-delegate-type-you-want-to-create.
Simply cast 0 to provide this argument:

MakeDelegate((target-delegate*)0,ptr-to-function)
MakeDelegate((target-delegate*)0,reference-to-object,ptr-to-member-function)
MakeDelegate((target-delegate*)0,ptr-to-member-function)

Future versions will drop this requirement once member templates are
available.

The delegate system is 100% type safe. It is also type flexible. You can
build a delegate out of a function that is 'type compatible' with the
target delegate - it need not have an exactly matching signature. By
type compatible I mean a function with the same number of arguments, of
types reachable from the delegate's argument types by implicit conversion.
The return type of the function must be implicitly convertible to the
return type of the delegate. A delegate with no return can be built from a
function with a return - the return value is simply ignored.
(See ethel example below)

All the correct virtual function behavior is preserved. (see ricky
example below).

If you somehow try to create something in violation
of the type system you will get a compile-time or template-instantiation-
time error.

The Delegate base class and translator
classes are artifacts of this implementation. You should not write
code that relies upon their existence. Nor should you rely on the return
value of MakeDelegate being anything in particular.

All that is guaranteed is that the Delegate classes have a default ctor,
a ctor that can accept 0 as an initializer,
an operator() with the requested argument types and return type, an
operator that will allow it to be evaluated in a conditional (with
'true' meaning the delegate is set, 'false' meaning it is not), and that
Delegates can be constructed from the result of MakeDelegate(), given
you've passed something compatible to MakeDelegate(). In addition you
can compare 2 delegates with ==, !=, and <. 2 delegates with the same
'callee' (function, object and/or ptr-to-mem-func) shall compare
equal. op < forms an ordering relation across all callee types -> the
actual order is not meaningful or to be depended upon.

/////////////////////// BEGIN Example 1 //////////////////////////
#include <iostream>
#include "callback.hpp"

//do5Times() is a function that takes a delegate and invokes it 5 times

void do5Times(const Delegate1<int> &doIt)
	{
	for(int i=0;i<5;i++)
		doIt(i);
	}

//Here are some standalone functions

void fred(int i){cout << "fred: " << i<<endl;}
int ethel(long l){cout << "ethel: " << l<<endl;return l;}

//Here is a class with a virtual function, and a derived class

class B{
public:
	virtual void ricky(int i)
	   {cout << "B::ricky: " << i<<endl;}
};

class D:public B{
public:
	void ricky(int i)
	   {cout << "D::ricky: " << i<<endl;}
};

void main()
	{
	//create a typedef of the delegate type to simplify dummy argument
	typedef Delegate1<int> *FtorType;

	Delegate1<int> ftor;	//a delegate variable
	//make a delegate from ptr-to-function
	ftor = MakeDelegate((FtorType)0,fred);
	do5Times(ftor);
	//note ethel is not an exact match - ok, is compatible
	ftor = MakeDelegate((FtorType)0,ethel);
	do5Times(ftor);

	//create a D object to be a callback target
	D myD;
	//make delegate from object and ptr-to-member-func
	ftor = MakeDelegate((FtorType)0,myD,&B::ricky);
	do5Times(ftor);
	}
/////////////////////// END of example 1 //////////////////////////

/////////////////////// BEGIN Example 2 //////////////////////////
#include <iostream>
#include "callback.hpp"

//Button is a component that provides a delegate-based
//callback mechanism, so you can wire it up to whatever you wish

class Button{
public:
	//ctor takes a delegate and stores it away in a member

	Button(const Delegate0 &uponClickDoThis):notify(uponClickDoThis)
		{}
	void click()
		{
		//invoke the delegate, thus calling back client
		notify();
		}
private:
	//note this is a data member with a verb for a name - matches its
	//function-like usage
	Delegate0 notify;
};

class CDPlayer{
public:
	void play()
		{cout << "Playing"<<endl;}
	void stop()
		{cout << "Stopped"<<endl;}
};

void main()
	{
	CDPlayer myCD;
	Button playButton(MakeDelegate((Delegate0*)0,myCD,&CDPlayer::play));
	Button stopButton(MakeDelegate((Delegate0*)0,myCD,&CDPlayer::stop));
	playButton.click();	//calls myCD.play()
	stopButton.click();  //calls myCD.stop()
	}
/////////////////////// END of example 2 //////////////////////////

*/

//******************************************************************
///////////////////////////////////////////////////////////////////*
//WARNING - no need to read past this point, lest confusion ensue. *
//Only the curious need explore further - but remember			   *
//about that cat!						                           *
///////////////////////////////////////////////////////////////////*
//******************************************************************

//////////////////////////////
// COMPILER BUG WORKAROUNDS:
// As of version 4.02 Borland has a code generation bug
// returning the result of a call via a ptr-to-function in a template

#ifdef __BORLANDC__
#define RHCB_BC4_RET_BUG(x) RT(x)
#else
#define RHCB_BC4_RET_BUG(x) x
#endif

// MS VC++ 4.2 still has many bugs relating to templates
// This version works around them as best I can - however note that
// MS will allow 'void (T::*)()const' to bind to a non-const member function
// of T. In addition, they do not support overloading template functions
// based on constness of ptr-to-mem-funcs.
// When _MSC_VER is defined I provide only the const versions,however it is on
// the user's head, when calling MakeDelegate with a const T, to make sure
// that the pointed-to member function is also const since MS won't enforce it!

// Other than that the port is completely functional under VC++ 4.2

// One MS bug you may encounter during _use_ of the callbacks:
// If you pass them by reference you can't call op() on the reference
// Workaround is to pass by value.

/*
// MS unable to call operator() on template class reference
template <class T>
class Delegate{
public:
	void operator()(T t)const{};
};

void foo(const Delegate<int> &f)
	{
	f(1);	//error C2064: term does not evaluate to a function

	//works when f is passed by value
	}
*/

// Note: if you are porting to another compiler that is having trouble you
// can try defining some of these flags as well:


#if defined(_MSC_VER)	
#if (_MSC_VER < 1100)
#define RHCB_CANT_OVERLOAD_ON_CONSTNESS		//of mem funcs
#endif
#define RHCB_CANT_PASS_MEMFUNC_BY_REFERENCE	//like it says
#define RHCB_CANT_INIT_REFERENCE_CTOR_STYLE	//int i;int &ir(i); //MS falls down
#define RHCB_WONT_PERFORM_PTR_CONVERSION		//of 0 to ptr-to-any-type
#endif


// Don't touch this stuff
#if defined(RHCB_CANT_PASS_MEMFUNC_BY_REFERENCE)
#define RHCB_CONST_REF
#else
#define RHCB_CONST_REF const &
#endif

#if defined(RHCB_CANT_INIT_REFERENCE_CTOR_STYLE)
#define RHCB_CTOR_STYLE_INIT =
#else
#define RHCB_CTOR_STYLE_INIT
#endif

#if defined(RHCB_WONT_PERFORM_PTR_CONVERSION)
#define RHCB_DUMMY_INIT int
#else
#define RHCB_DUMMY_INIT DelegateBase::DummyInit *
#endif

////////////////////////////// THE CODE //////////////////////////

#include <string.h> //for memstuff
#include <stddef.h> //for size_t
#include <set>
#include <vector>

// CDH PopCap Framework specific (just for convenience; got tired of having
// to make sure this was consistently defined everywhere)
#ifndef RHCB_NAMESPACE
	#define RHCB_NAMESPACE Sexy
#endif

#ifdef RHCB_NAMESPACE
namespace RHCB_NAMESPACE {
#endif

//change these when your compiler gets bool
typedef int RHCB_BOOL;
//enum {RHCB_FALSE,RHCB_TRUE};

/************************* invoke variants *******************/

/*
	RtInvokeVariant
*/
class RtInvokeVariant;
template <typename T> class TRtInvokeVariantGetter { public: static T Get(const RtInvokeVariant* v); };

class RtInvokeVariant
{
public:
	enum EVariantType
	{
		VT_UInt32,
		VT_SInt32,
		VT_Float,
		VT_UInt64,
		VT_SInt64,
		VT_Double,
		VT_Ptr,
	};

	EVariantType mType;
	union
	{
        uint32 mUInt32;
        int32 mSInt32;
		float mFloat;
		uint64 mUInt64;
		int64 mSInt64;
		double mDouble;
		void* mPtr;
	};

	inline RtInvokeVariant() { mType = VT_UInt32; mUInt32 = 0; }
	inline RtInvokeVariant(bool inValue) { mType = VT_UInt32; mUInt32 = inValue ? 1 : 0; }
	inline RtInvokeVariant(char inValue) { mType = VT_SInt32; mSInt32 = inValue; }
	inline RtInvokeVariant(signed char inValue) { mType = VT_SInt32; mSInt32 = inValue; }
	inline RtInvokeVariant(unsigned char inValue) { mType = VT_UInt32; mUInt32 = inValue; }
	inline RtInvokeVariant(signed short inValue) { mType = VT_SInt32; mSInt32 = inValue; }
	inline RtInvokeVariant(unsigned short inValue) { mType = VT_UInt32; mUInt32 = inValue; }
    inline RtInvokeVariant(int32 inValue) { mType = VT_SInt32; mSInt32 = inValue; }
    inline RtInvokeVariant(uint32 inValue) { mType = VT_UInt32; mUInt32 = inValue; }
	inline RtInvokeVariant(wchar_t inValue) { mType = VT_UInt32; mUInt32 = inValue; }
	inline RtInvokeVariant(uint64 inValue) { mType = VT_UInt64; mUInt64 = inValue; }
	inline RtInvokeVariant(int64 inValue) { mType = VT_SInt64; mSInt64 = inValue; }
	inline RtInvokeVariant(const void* inValue) { mType = VT_Ptr; mPtr = (void*)inValue; }
    inline RtInvokeVariant(const char* inValue) { mType = VT_Ptr; mPtr = (char*)inValue; }
    inline RtInvokeVariant(const wchar_t* inValue) { mType = VT_Ptr; mPtr = (wchar_t*)inValue; }
	inline RtInvokeVariant(float inValue) { mType = VT_Float; mFloat = inValue; }
	inline RtInvokeVariant(double inValue) { mType = VT_Double; mDouble = inValue; }

	template <typename T> T Get() const { return TRtInvokeVariantGetter<T>::Get(this); }
    
    // We want to support some Return types that cannot be converted to supported RtInvokeVariants.
    // This method will have specializations for such types and will return a "void" RtInvokeVariant
    // for those specific types.
    // We do this rather than generate a compiler error because we want to allow those returned types
    // to be accessable via the Invoke() method of DelegateBase that is templatized on the return type.
    template <typename T>
    static RtInvokeVariant ConvertReturnValueToVariant(T inValue)
    {
        return RtInvokeVariant(inValue);
    }
};

// Specialization to allow strings to not generate errors when used as return values.
//
template<>
inline RtInvokeVariant RtInvokeVariant::ConvertReturnValueToVariant(std::string inValue)
{
    // $$$$ (avy) need to a make a "Void" variant value/type
    return RtInvokeVariant((int32)0);
}

#define RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(xType) template <> class TRtInvokeVariantGetter<xType> { public: static xType Get(const RtInvokeVariant* v) { return (xType)v->mUInt32; } }
#define RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(xType) template <> class TRtInvokeVariantGetter<xType> { public: static xType Get(const RtInvokeVariant* v) { return (xType)v->mSInt32; } }
#define RT_INVOKEVARIANT_DECLARE_TYPE_UINT64(xType) template <> class TRtInvokeVariantGetter<xType> { public: static xType Get(const RtInvokeVariant* v) { return (xType)v->mUInt64; } }
#define RT_INVOKEVARIANT_DECLARE_TYPE_SINT64(xType) template <> class TRtInvokeVariantGetter<xType> { public: static xType Get(const RtInvokeVariant* v) { return (xType)v->mSInt64; } }
#define RT_INVOKEVARIANT_DECLARE_TYPE_POINTER(xType) template <> class TRtInvokeVariantGetter<xType> { public: static xType Get(const RtInvokeVariant* v) { return (xType)v->mPtr; } }

RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(char);
RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(signed char);
RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(unsigned char);
RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(signed short);
RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(unsigned short);
RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(int32);
RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(uint32);
RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(wchar_t); // wchar_t's size is platform defined. serializing it is a bad idea.


RT_INVOKEVARIANT_DECLARE_TYPE_SINT64(int64);
RT_INVOKEVARIANT_DECLARE_TYPE_UINT64(uint64);

template <> class TRtInvokeVariantGetter<bool> { public: static bool Get(const RtInvokeVariant* v) { return (v->mUInt32 > 0); } };
template <> class TRtInvokeVariantGetter<float> { public: static float Get(const RtInvokeVariant* v) { return v->mFloat; } };
template <> class TRtInvokeVariantGetter<double> { public: static double Get(const RtInvokeVariant* v) { return v->mDouble; } };
template <typename T> class TRtInvokeVariantGetter<T*> { public: static T* Get(const RtInvokeVariant* v) { return (T*)v->mPtr; } };
template <typename T> class TRtInvokeVariantGetter<const T*> { public: static T* Get(const RtInvokeVariant* v) { return (T*)v->mPtr; } };
template <typename T> class TRtInvokeVariantGetter<T&> { public: static T& Get(const RtInvokeVariant* v) { return *((T*)v->mPtr); } };
template <typename T> class TRtInvokeVariantGetter<const T&> { public: static T& Get(const RtInvokeVariant* v) { return *((T*)v->mPtr); } };

/************************* general translators *******************/

template <class FUNC>
struct CBFunctionTranslatorX
{
	CBFunctionTranslatorX(FUNC f) : func(f)  {}
	FUNC func;
};

template <class CLASS, class MEMFUNC>
struct CBMemberTranslatorX
{
	CBMemberTranslatorX(CLASS& c, MEMFUNC mf) : cls(&c), mfunc(mf)  {}
    CBMemberTranslatorX(CLASS* c, MEMFUNC mf) : cls(c), mfunc(mf)  {}
	CLASS* cls;
	MEMFUNC mfunc;
};

// $ not currently used - no MakeDelegate will generate one (can't see the need yet)
template <class MEMFUNC>
struct CBMemberOf1stArgTranslatorX
{
	CBMemberOf1stArgTranslatorX(MEMFUNC mf) : mfunc(mf)  {}
	MEMFUNC mfunc;
};

template <class CLASS, class MEMFUNC>
inline CBMemberTranslatorX <CLASS, MEMFUNC>
MakeDelegate(CLASS& c, MEMFUNC mf)
	{
		return (CBMemberTranslatorX <CLASS, MEMFUNC> (c, mf));
	}

template <class CLASS, class MEMFUNC>
inline CBMemberTranslatorX <CLASS, MEMFUNC>
MakeDelegate(CLASS* c, MEMFUNC mf)
{
    return (CBMemberTranslatorX <CLASS, MEMFUNC> (c, mf));
}

template <class FUNC>
inline CBFunctionTranslatorX <FUNC>
MakeDelegate(FUNC f)
	{
		return (CBFunctionTranslatorX <FUNC> (f));
	}
    
/***** typeless representation of a function and optional object ******/

class DelegateBase{
public:
	//Note: ctors are protected

	//for evaluation in conditionals - can the delegate be called?
	operator RHCB_BOOL()const{return callee||data.func;}

   //The rest below for implementation use only !

	class DummyInit{
	};

	typedef void (*PFunc)();
	enum {MEM_FUNC_SIZE = 8};

	PFunc	getFunc() const {return data.func;}
	void *getCallee() const {return callee;}
	const char *getMemFunc() const {return data.memFunc;}
	
	RHCB_BOOL NeedsInstanceContext() const {return needsCallee;}
	void* GetInstanceContext() const { return callee; }
	void SetInstanceContext(void* inInstance) { callee = inInstance; }

	virtual void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const = 0;
    
	void Invoke(void* inInstance, RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		void* oldCallee = callee;
		callee = inInstance;
		Invoke(outRet, inArgs);
		callee = oldCallee;
	}
    
    template <typename RT>
    void InvokeWithTypedReturn(RT* outTypedReturn, const RtInvokeVariant* inArgs) const
    {
        InvokeUnsafeReturn(outTypedReturn, inArgs);
    }

    template <typename RT>
    void InvokeWithTypedReturn(void* inInstance, RT* outTypedReturn, const RtInvokeVariant* inArgs) const
    {
        void* oldCallee = callee;
		callee = inInstance;
        InvokeUnsafeReturn(outTypedReturn, inArgs);
        callee = oldCallee;
    }
    
protected:
    // $ This default implementation assumes no return value, DelegateWRetBase will override this
    // and all delegate types that have return types must inherit from DelegateWRetBase
    virtual void InvokeUnsafeReturn(void* outReturnType, const RtInvokeVariant* inArgs) const
    {
        // $$$$ (avy) should generate an error here.
        //SEXY_ERROR("InvokeWithTypedReturn() with a templatized return type was called on a delegate that has no return value.");
        Invoke(NULL, inArgs);
    }

    union FuncPtr
    {
        PFunc func;
#ifdef HOST_WINDOWS
		// sizeof ptr-to-member function on vs is different from on xcode
		// The result would be 4, 8, 12, 16 on vs but 16 on xcode
		// it seems the result depends on the inheritance relationship of each class
		// so the vs compiler cann't ensure the size of the char array
		char memFunc[MEM_FUNC_SIZE * 2]; 
#else
        char memFunc[sizeof(&DelegateBase::InvokeUnsafeReturn)]; // ptr-to-member functions may be a different size than a vanilla fn ptr
#endif
    } data;
	mutable void *callee;
	RHCB_BOOL needsCallee;

    DelegateBase()
    : callee(0)
    , needsCallee(false)
    {
        memset(data.memFunc, 0, sizeof(FuncPtr));
    }
    
    DelegateBase(const void *c,PFunc f, const void *mf,size_t sz)
    : callee((void *)c)
    , needsCallee(false)
    {
        memset(data.memFunc, 0, sizeof(FuncPtr));
        
        if(c)	//must be callee/memfunc
        {
            memcpy(data.memFunc,mf,sz);
        }
        else	//must be ptr-to-func
        {
            data.func = f;
        }
    }
    
    template <class FUNC> DelegateBase(const CBFunctionTranslatorX <FUNC> & t)
    : callee(0)
    , needsCallee(false)
    {
        memset(data.memFunc, 0, sizeof(FuncPtr));
        data.func = PFunc(t.func);
    }
    
    template <class CLASS, class MEMFUNC> DelegateBase( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
    : callee(t.cls)
    , needsCallee(true)
    {
        memset(data.memFunc, 0, sizeof(FuncPtr));
        memcpy(data.memFunc, &t.mfunc, sizeof(MEMFUNC));
    }
    
    template <class MEMFUNC> DelegateBase( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
    : callee(0)
    , needsCallee(false)
    {
        memset(data.memFunc, 0, sizeof(FuncPtr));
        memcpy(data.memFunc, &t.mfunc, sizeof(MEMFUNC));
    }
    
public:
    friend RHCB_BOOL operator==(const DelegateBase &lhs,const DelegateBase &rhs)
    {
        return memcmp(lhs.data.memFunc, rhs.data.memFunc, sizeof(FuncPtr)) == 0 && lhs.callee == rhs.callee && lhs.needsCallee == rhs.needsCallee;
    }
    
    friend RHCB_BOOL operator!=(const DelegateBase &lhs,const DelegateBase &rhs)
    { 
        return !(lhs == rhs);
    }
};

template<typename RT>
class DelegateWRetBase : public DelegateBase
{
public:
    // Override
    void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		RT rt = InternalInvokeWithTypedReturn(inArgs);
		if (outRet) *outRet = RtInvokeVariant::ConvertReturnValueToVariant(rt);
	}
    
protected:
    virtual RT InternalInvokeWithTypedReturn(const RtInvokeVariant* inArgs) const = 0;

    // Override
    void InvokeUnsafeReturn(void* outReturnType, const RtInvokeVariant* inArgs) const
    {
        // $ (avy) Danger! The caller MUST be certain to pass in a pointer of the correct return type for this delegate
        RT* pRt = reinterpret_cast<RT*>(outReturnType);
        *pRt = InternalInvokeWithTypedReturn(inArgs);
    }
    
    //
    // Implement the same constructors as DelegateBase
    //
    
    DelegateWRetBase(): DelegateBase()
    {
    }
    
    DelegateWRetBase(const void *c,PFunc f, const void *mf,size_t sz)
        : DelegateBase(c, f, mf, sz)
    {
    }
    
	template <class FUNC> DelegateWRetBase(const CBFunctionTranslatorX <FUNC> & t)
        : DelegateBase(t)
    {
    }
    
	template <class CLASS, class MEMFUNC> DelegateWRetBase( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
        : DelegateBase(t)
    {
    }
    
	template <class MEMFUNC> DelegateWRetBase( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
        : DelegateBase(t)
    {
    }

};


/************************* no arg - no return *******************/
#ifndef _MSC_VER
template <class Func> class CBFunctionTranslator0;
template <class Callee, class MemFunc> class CBMemberTranslator0;
#endif
    
class Delegate0:public DelegateBase{
public:
	Delegate0(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate0(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateBase(t), thunk(CBFunctionTranslator0 <FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate0( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberTranslator0 <CLASS, MEMFUNC>::thunk)  {}
	void operator()()const
		{
		thunk(*this);
		}
	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		thunk(*this);
		if (outRet) *outRet = RtInvokeVariant((int32)0);
	}
	//for STL
	typedef void result_type;
protected:
	typedef void (*Thunk)(const DelegateBase &);
	Delegate0(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		DelegateBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class Callee, class MemFunc>
class CBMemberTranslator0:public Delegate0{
public:
	CBMemberTranslator0(Callee &c,const MemFunc &m):
		Delegate0(thunk,&c,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(callee->*memFunc)();
		}
};

template <class Func>
class CBFunctionTranslator0:public Delegate0{
public:
	CBFunctionTranslator0(Func f):Delegate0(thunk,0,(PFunc)f,0,0){}
	static void thunk(const DelegateBase &ftor)
		{
		(Func(ftor.getFunc()))();
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class Callee,class TRT,class CallType>
inline CBMemberTranslator0<Callee,TRT (CallType::*)()>
MakeDelegate(Delegate0 *,Callee &c,TRT (CallType::* RHCB_CONST_REF f)())
	{
	typedef TRT (CallType::*MemFunc)();
	return CBMemberTranslator0<Callee,MemFunc>(c,f);
	}
#endif

template <class Callee,class TRT,class CallType>
inline CBMemberTranslator0<const Callee,TRT (CallType::*)()const>
MakeDelegate(Delegate0 *,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)()const)
	{
	typedef TRT (CallType::*MemFunc)()const;
	return CBMemberTranslator0<const Callee,MemFunc>(c,f);
	}

template <class TRT>
inline CBFunctionTranslator0<TRT (*)()>
MakeDelegate(Delegate0 *,TRT (*f)())
	{
	return CBFunctionTranslator0<TRT (*)()>(f);
	}


/************************* no arg - with return *******************/
#ifndef _MSC_VER
template <class RT, class Func> class CBFunctionTranslator0wRet;
template <class RT, class Callee, class MemFunc> class CBMemberTranslator0wRet;
#endif
    
template <class RT>
class Delegate0wRet:public DelegateWRetBase<RT> {
public:
	Delegate0wRet(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate0wRet(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateWRetBase<RT>(t), thunk(CBFunctionTranslator0wRet <RT, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate0wRet( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberTranslator0wRet <RT, CLASS, MEMFUNC>::thunk)  {}
	RT operator()()const
		{
		return RHCB_BC4_RET_BUG(thunk(*this));
		}
    
	//for STL
	typedef RT result_type;
protected:
    // Override
    RT InternalInvokeWithTypedReturn(const RtInvokeVariant* inArgs) const
    {
        return RHCB_BC4_RET_BUG(thunk(*this));
    }

	typedef RT (*Thunk)(const DelegateBase &);
	Delegate0wRet(Thunk t,const void *c,DelegateBase::PFunc f,const void *mf,size_t sz):
		DelegateWRetBase<RT>(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class RT,class Callee, class MemFunc>
class CBMemberTranslator0wRet:public Delegate0wRet<RT>{
public:
	CBMemberTranslator0wRet(Callee &c,const MemFunc &m):
		Delegate0wRet<RT>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((callee->*memFunc)());
		}
};

template <class RT,class Func>
class CBFunctionTranslator0wRet:public Delegate0wRet<RT>{
public:
	CBFunctionTranslator0wRet(Func f):Delegate0wRet<RT>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static RT thunk(const DelegateBase &ftor)
		{
		return (Func(ftor.getFunc()))();
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class Callee,class TRT,class CallType>
inline CBMemberTranslator0wRet<RT,Callee,TRT (CallType::*)()>
MakeDelegate(Delegate0wRet<RT>*,Callee &c,TRT (CallType::* RHCB_CONST_REF f)())
	{
	typedef TRT (CallType::*MemFunc)();
	return CBMemberTranslator0wRet<RT,Callee,MemFunc>(c,f);
	}
#endif

template <class RT,class Callee,class TRT,class CallType>
inline CBMemberTranslator0wRet<RT,const Callee,TRT (CallType::*)()const>
MakeDelegate(Delegate0wRet<RT>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)()const)
	{
	typedef TRT (CallType::*MemFunc)()const;
	return CBMemberTranslator0wRet<RT,const Callee,MemFunc>(c,f);
	}

template <class RT,class TRT>
inline CBFunctionTranslator0wRet<RT,TRT (*)()>
MakeDelegate(Delegate0wRet<RT>*,TRT (*f)())
	{
	return CBFunctionTranslator0wRet<RT,TRT (*)()>(f);
	}

/************************* one arg - no return *******************/
#ifndef _MSC_VER
template <class P1, class Func> class CBFunctionTranslator1;
template <class P1, class Callee, class MemFunc> class CBMemberTranslator1;
template <class P1, class MemFunc> class CBMemberOf1stArgTranslator1;
#endif
    
template <class P1>
class Delegate1:public DelegateBase{
public:
	Delegate1(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate1(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateBase(t), thunk(CBFunctionTranslator1 <P1, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate1( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberTranslator1 <P1, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate1( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberOf1stArgTranslator1 <P1, MEMFUNC>::thunk)  {}
	void operator()(P1 p1)const
		{
		thunk(*this,p1);
		}
	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		thunk(*this,p1);
		if (outRet) *outRet = RtInvokeVariant((int32)0);
	}
	//for STL
	typedef void result_type;
	typedef P1 first_argument_type;
protected:
	typedef void (*Thunk)(const DelegateBase &,P1);
	Delegate1(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		DelegateBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class Callee, class MemFunc>
class CBMemberTranslator1:public Delegate1<P1>{
public:
	CBMemberTranslator1(Callee &c,const MemFunc &m):
		Delegate1<P1>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(callee->*memFunc)(p1);
		}
};

template <class P1,class Func>
class CBFunctionTranslator1:public Delegate1<P1>{
public:
	CBFunctionTranslator1(Func f):Delegate1<P1>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static void thunk(const DelegateBase &ftor,P1 p1)
		{
		(Func(ftor.getFunc()))(p1);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class Callee,class TRT,class CallType,class TP1>
inline CBMemberTranslator1<P1,Callee,TRT (CallType::*)(TP1)>
MakeDelegate(Delegate1<P1>*,Callee &c,TRT (CallType::* RHCB_CONST_REF f)(TP1))
	{
	typedef TRT (CallType::*MemFunc)(TP1);
	return CBMemberTranslator1<P1,Callee,MemFunc>(c,f);
	}
#endif

template <class P1,class Callee,class TRT,class CallType,class TP1>
inline CBMemberTranslator1<P1,const Callee,TRT (CallType::*)(TP1)const>
MakeDelegate(Delegate1<P1>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1)const;
	return CBMemberTranslator1<P1,const Callee,MemFunc>(c,f);
	}

template <class P1,class TRT,class TP1>
inline CBFunctionTranslator1<P1,TRT (*)(TP1)>
MakeDelegate(Delegate1<P1>*,TRT (*f)(TP1))
	{
	return CBFunctionTranslator1<P1,TRT (*)(TP1)>(f);
	}

template <class P1,class MemFunc>
class CBMemberOf1stArgTranslator1:public Delegate1<P1>{
public:
	CBMemberOf1stArgTranslator1(const MemFunc &m):
		Delegate1<P1>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(p1.*memFunc)();
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class TRT,class CallType>
inline CBMemberOf1stArgTranslator1<P1,TRT (CallType::*)()>
MakeDelegate(Delegate1<P1>*,TRT (CallType::* RHCB_CONST_REF f)())
	{
	typedef TRT (CallType::*MemFunc)();
	return CBMemberOf1stArgTranslator1<P1,MemFunc>(f);
	}
#endif

template <class P1,class TRT,class CallType>
inline CBMemberOf1stArgTranslator1<P1,TRT (CallType::*)()const>
MakeDelegate(Delegate1<P1>*,TRT (CallType::* RHCB_CONST_REF f)()const)
	{
	typedef TRT (CallType::*MemFunc)()const;
	return CBMemberOf1stArgTranslator1<P1,MemFunc>(f);
	}

/************************* one arg - with return *******************/
#ifndef _MSC_VER
template <class RT, class P1, class Func> class CBFunctionTranslator1wRet;
template <class RT, class P1, class Callee, class MemFunc> class CBMemberTranslator1wRet;
template <class RT, class P1, class MemFunc> class CBMemberOf1stArgTranslator1wRet;
#endif
    
template <class RT,class P1>
class Delegate1wRet:public DelegateWRetBase<RT>{
public:
	Delegate1wRet(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate1wRet(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateWRetBase<RT>(t), thunk(CBFunctionTranslator1wRet <RT, P1, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate1wRet( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberTranslator1wRet <RT, P1, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate1wRet( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberOf1stArgTranslator1wRet <RT, P1, MEMFUNC>::thunk)  {}
	RT operator()(P1 p1)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1));
		}
	
	//for STL
	typedef RT result_type;
	typedef P1 first_argument_type;
protected:
    // Override
    RT InternalInvokeWithTypedReturn(const RtInvokeVariant* inArgs) const
    {
        P1 p1 = inArgs[0].Get<P1>();
		return RHCB_BC4_RET_BUG(thunk(*this,p1));
    }

	typedef RT (*Thunk)(const DelegateBase &,P1);
	Delegate1wRet(Thunk t,const void *c,DelegateBase::PFunc f,const void *mf,size_t sz):
		DelegateWRetBase<RT>(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class RT,class P1,class Callee, class MemFunc>
class CBMemberTranslator1wRet:public Delegate1wRet<RT,P1>{
public:
	CBMemberTranslator1wRet(Callee &c,const MemFunc &m):
		Delegate1wRet<RT,P1>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((callee->*memFunc)(p1));
		}
};

template <class RT,class P1,class Func>
class CBFunctionTranslator1wRet:public Delegate1wRet<RT,P1>{
public:
	CBFunctionTranslator1wRet(Func f):
		Delegate1wRet<RT,P1>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static RT thunk(const DelegateBase &ftor,P1 p1)
		{
		return (Func(ftor.getFunc()))(p1);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,
	class Callee,class TRT,class CallType,class TP1>
inline CBMemberTranslator1wRet<RT,P1,Callee,TRT (CallType::*)(TP1)>
MakeDelegate(Delegate1wRet<RT,P1>*,Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1))
	{
	typedef TRT (CallType::*MemFunc)(TP1);
	return CBMemberTranslator1wRet<RT,P1,Callee,MemFunc>(c,f);
	}
#endif

template <class RT,class P1,
	class Callee,class TRT,class CallType,class TP1>
inline CBMemberTranslator1wRet<RT,P1,
	const Callee,TRT (CallType::*)(TP1)const>
MakeDelegate(Delegate1wRet<RT,P1>*,
	const Callee &c,TRT (CallType::* RHCB_CONST_REF f)(TP1)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1)const;
	return CBMemberTranslator1wRet<RT,P1,const Callee,MemFunc>(c,f);
	}

template <class RT,class P1,class TRT,class TP1>
inline CBFunctionTranslator1wRet<RT,P1,TRT (*)(TP1)>
MakeDelegate(Delegate1wRet<RT,P1>*,TRT (*f)(TP1))
	{
	return CBFunctionTranslator1wRet<RT,P1,TRT (*)(TP1)>(f);
	}

template <class RT,class P1,class MemFunc>
class CBMemberOf1stArgTranslator1wRet:public Delegate1wRet<RT,P1>{
public:
	CBMemberOf1stArgTranslator1wRet(const MemFunc &m):
		Delegate1wRet<RT,P1>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((p1.*memFunc)());
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class TRT,class CallType>
inline CBMemberOf1stArgTranslator1wRet<RT,P1,TRT (CallType::*)()>
MakeDelegate(Delegate1wRet<RT,P1>*,TRT (CallType::* RHCB_CONST_REF f)())
	{
	typedef TRT (CallType::*MemFunc)();
	return CBMemberOf1stArgTranslator1wRet<RT,P1,MemFunc>(f);
	}
#endif

template <class RT,class P1,class TRT,class CallType>
inline CBMemberOf1stArgTranslator1wRet<RT,P1,TRT (CallType::*)()const>
MakeDelegate(Delegate1wRet<RT,P1>*,TRT (CallType::* RHCB_CONST_REF f)()const)
	{
	typedef TRT (CallType::*MemFunc)()const;
	return CBMemberOf1stArgTranslator1wRet<RT,P1,MemFunc>(f);
	}


/************************* two args - no return *******************/
#ifndef _MSC_VER
template <class P1, class P2, class Func> class CBFunctionTranslator2;
template <class P1, class P2, class Callee, class MemFunc> class CBMemberTranslator2;
template <class P1, class P2, class MemFunc> class CBMemberOf1stArgTranslator2;
#endif
    
template <class P1,class P2>
class Delegate2:public DelegateBase{
public:
	Delegate2(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate2(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateBase(t), thunk(CBFunctionTranslator2 <P1, P2, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate2( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberTranslator2 <P1, P2, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate2( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberOf1stArgTranslator2 <P1, P2, MEMFUNC>::thunk)  {}
	void operator()(P1 p1,P2 p2)const
		{
		thunk(*this,p1,p2);
		}
	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		thunk(*this,p1,p2);
		if (outRet) *outRet = RtInvokeVariant((int32)0);
	}
	//for STL
	typedef void result_type;
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
protected:
	typedef void (*Thunk)(const DelegateBase &,P1,P2);
	Delegate2(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		DelegateBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class Callee, class MemFunc>
class CBMemberTranslator2:public Delegate2<P1,P2>{
public:
	CBMemberTranslator2(Callee &c,const MemFunc &m):
		Delegate2<P1,P2>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(callee->*memFunc)(p1,p2);
		}
};

template <class P1,class P2,class Func>
class CBFunctionTranslator2:public Delegate2<P1,P2>{
public:
	CBFunctionTranslator2(Func f):Delegate2<P1,P2>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2)
		{
		(Func(ftor.getFunc()))(p1,p2);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class Callee,
	class TRT,class CallType,class TP1,class TP2>
inline CBMemberTranslator2<P1,P2,Callee,TRT (CallType::*)(TP1,TP2)>
MakeDelegate(Delegate2<P1,P2>*,Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2);
	return CBMemberTranslator2<P1,P2,Callee,MemFunc>(c,f);
	}
#endif

template <class P1,class P2,class Callee,
	class TRT,class CallType,class TP1,class TP2>
inline CBMemberTranslator2<P1,P2,const Callee,
	TRT (CallType::*)(TP1,TP2)const>
MakeDelegate(Delegate2<P1,P2>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2)const;
	return CBMemberTranslator2<P1,P2,const Callee,MemFunc>(c,f);
	}

template <class P1,class P2,class TRT,class TP1,class TP2>
inline CBFunctionTranslator2<P1,P2,TRT (*)(TP1,TP2)>
MakeDelegate(Delegate2<P1,P2>*,TRT (*f)(TP1,TP2))
	{
	return CBFunctionTranslator2<P1,P2,TRT (*)(TP1,TP2)>(f);
	}

template <class P1,class P2,class MemFunc>
class CBMemberOf1stArgTranslator2:public Delegate2<P1,P2>{
public:
	CBMemberOf1stArgTranslator2(const MemFunc &m):
		Delegate2<P1,P2>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(p1.*memFunc)(p2);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class TRT,class CallType,class TP1>
inline CBMemberOf1stArgTranslator2<P1,P2,TRT (CallType::*)(TP1)>
MakeDelegate(Delegate2<P1,P2>*,TRT (CallType::* RHCB_CONST_REF f)(TP1))
	{
	typedef TRT (CallType::*MemFunc)(TP1);
	return CBMemberOf1stArgTranslator2<P1,P2,MemFunc>(f);
	}
#endif

template <class P1,class P2,class TRT,class CallType,class TP1>
inline CBMemberOf1stArgTranslator2<P1,P2,TRT (CallType::*)(TP1)const>
MakeDelegate(Delegate2<P1,P2>*,TRT (CallType::* RHCB_CONST_REF f)(TP1)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1)const;
	return CBMemberOf1stArgTranslator2<P1,P2,MemFunc>(f);
	}


/************************* two args - with return *******************/
#ifndef _MSC_VER
template <class RT, class P1, class P2, class Func> class CBFunctionTranslator2wRet;
template <class RT, class P1, class P2, class Callee, class MemFunc> class CBMemberTranslator2wRet;
template <class RT, class P1, class P2, class MemFunc> class CBMemberOf1stArgTranslator2wRet;
#endif

template <class RT,class P1,class P2>
class Delegate2wRet:public DelegateWRetBase<RT>{
public:
	Delegate2wRet(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate2wRet(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateWRetBase<RT>(t), thunk(CBFunctionTranslator2wRet <RT, P1, P2, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate2wRet( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberTranslator2wRet <RT, P1, P2, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate2wRet( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberOf1stArgTranslator2wRet <RT, P1, P2, MEMFUNC>::thunk)  {}
	RT operator()(P1 p1,P2 p2)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2));
		}
	   
	//for STL
	typedef RT result_type;
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
protected:
    // Override
    RT InternalInvokeWithTypedReturn(const RtInvokeVariant* inArgs) const
    {
        P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2));
    }

	typedef RT (*Thunk)(const DelegateBase &,P1,P2);
	Delegate2wRet(Thunk t,const void *c,DelegateBase::PFunc f,const void *mf,size_t sz):
		DelegateWRetBase<RT>(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class RT,class P1,class P2,class Callee, class MemFunc>
class CBMemberTranslator2wRet:public Delegate2wRet<RT,P1,P2>{
public:
	CBMemberTranslator2wRet(Callee &c,const MemFunc &m):
		Delegate2wRet<RT,P1,P2>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((callee->*memFunc)(p1,p2));
		}
};

template <class RT,class P1,class P2,class Func>
class CBFunctionTranslator2wRet:public Delegate2wRet<RT,P1,P2>{
public:
	CBFunctionTranslator2wRet(Func f):
		Delegate2wRet<RT,P1,P2>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2)
		{
		return (Func(ftor.getFunc()))(p1,p2);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class P2,class Callee,
	class TRT,class CallType,class TP1,class TP2>
inline CBMemberTranslator2wRet<RT,P1,P2,Callee,
	TRT (CallType::*)(TP1,TP2)>
MakeDelegate(Delegate2wRet<RT,P1,P2>*,Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2);
	return CBMemberTranslator2wRet<RT,P1,P2,Callee,MemFunc>(c,f);
	}
#endif

template <class RT,class P1,class P2,class Callee,
	class TRT,class CallType,class TP1,class TP2>
inline CBMemberTranslator2wRet<RT,P1,P2,const Callee,
	TRT (CallType::*)(TP1,TP2)const>
MakeDelegate(Delegate2wRet<RT,P1,P2>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2)const;
	return CBMemberTranslator2wRet<RT,P1,P2,const Callee,MemFunc>(c,f);
	}

template <class RT,class P1,class P2,class TRT,class TP1,class TP2>
inline CBFunctionTranslator2wRet<RT,P1,P2,TRT (*)(TP1,TP2)>
MakeDelegate(Delegate2wRet<RT,P1,P2>*,TRT (*f)(TP1,TP2))
	{
	return CBFunctionTranslator2wRet<RT,P1,P2,TRT (*)(TP1,TP2)>(f);
	}

template <class RT,class P1,class P2,class MemFunc>
class CBMemberOf1stArgTranslator2wRet:public Delegate2wRet<RT,P1,P2>{
public:
	CBMemberOf1stArgTranslator2wRet(const MemFunc &m):
		Delegate2wRet<RT,P1,P2>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((p1.*memFunc)(p2));
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class P2,class TRT,class CallType,class TP1>
inline CBMemberOf1stArgTranslator2wRet<RT,P1,P2,TRT (CallType::*)(TP1)>
MakeDelegate(Delegate2wRet<RT,P1,P2>*,TRT (CallType::* RHCB_CONST_REF f)(TP1))
	{
	typedef TRT (CallType::*MemFunc)(TP1);
	return CBMemberOf1stArgTranslator2wRet<RT,P1,P2,MemFunc>(f);
	}
#endif

template <class RT,class P1,class P2,class TRT,class CallType,class TP1>
inline CBMemberOf1stArgTranslator2wRet<RT,P1,P2,TRT (CallType::*)(TP1)const>
MakeDelegate(Delegate2wRet<RT,P1,P2>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1)const;
	return CBMemberOf1stArgTranslator2wRet<RT,P1,P2,MemFunc>(f);
	}


/************************* three args - no return *******************/
#ifndef _MSC_VER
template <class P1, class P2, class P3, class Func> class CBFunctionTranslator3;
template <class P1, class P2, class P3, class Callee, class MemFunc> class CBMemberTranslator3;
template <class P1, class P2, class P3, class MemFunc> class CBMemberOf1stArgTranslator3;
#endif
        
template <class P1,class P2,class P3>
class Delegate3:public DelegateBase{
public:
	Delegate3(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate3(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateBase(t), thunk(CBFunctionTranslator3 <P1, P2, P3, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate3( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberTranslator3 <P1, P2, P3, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate3( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberOf1stArgTranslator3 <P1, P2, P3, MEMFUNC>::thunk)  {}
	void operator()(P1 p1,P2 p2,P3 p3)const
		{
		thunk(*this,p1,p2,p3);
		}
	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		thunk(*this,p1,p2,p3);
		if (outRet) *outRet = RtInvokeVariant((int32)0);
	}
	//for STL
	typedef void result_type;
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
	typedef P3 third_argument_type;
protected:
	typedef void (*Thunk)(const DelegateBase &,P1,P2,P3);
	Delegate3(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		DelegateBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class P3,class Callee, class MemFunc>
class CBMemberTranslator3:public Delegate3<P1,P2,P3>{
public:
	CBMemberTranslator3(Callee &c,const MemFunc &m):
		Delegate3<P1,P2,P3>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(callee->*memFunc)(p1,p2,p3);
		}
};

template <class P1,class P2,class P3,class Func>
class CBFunctionTranslator3:public Delegate3<P1,P2,P3>{
public:
	CBFunctionTranslator3(Func f):Delegate3<P1,P2,P3>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3)
		{
		(Func(ftor.getFunc()))(p1,p2,p3);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3>
inline CBMemberTranslator3<P1,P2,P3,Callee,
	TRT (CallType::*)(TP1,TP2,TP3)>
MakeDelegate(Delegate3<P1,P2,P3>*,Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3);
	return CBMemberTranslator3<P1,P2,P3,Callee,MemFunc>(c,f);
	}
#endif

template <class P1,class P2,class P3,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3>
inline CBMemberTranslator3<P1,P2,P3,const Callee,
	TRT (CallType::*)(TP1,TP2,TP3)const>
MakeDelegate(Delegate3<P1,P2,P3>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3)const;
	return CBMemberTranslator3<P1,P2,P3,const Callee,MemFunc>(c,f);
	}

template <class P1,class P2,class P3,
	class TRT,class TP1,class TP2,class TP3>
inline CBFunctionTranslator3<P1,P2,P3,TRT (*)(TP1,TP2,TP3)>
MakeDelegate(Delegate3<P1,P2,P3>*,TRT (*f)(TP1,TP2,TP3))
	{
	return CBFunctionTranslator3<P1,P2,P3,TRT (*)(TP1,TP2,TP3)>(f);
	}

template <class P1,class P2,class P3,class MemFunc>
class CBMemberOf1stArgTranslator3:public Delegate3<P1,P2,P3>{
public:
	CBMemberOf1stArgTranslator3(const MemFunc &m):
		Delegate3<P1,P2,P3>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(p1.*memFunc)(p2,p3);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class TRT,class CallType,
	class TP1,class TP2>
inline CBMemberOf1stArgTranslator3<P1,P2,P3,TRT (CallType::*)(TP1,TP2)>
MakeDelegate(Delegate3<P1,P2,P3>*,TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2);
	return CBMemberOf1stArgTranslator3<P1,P2,P3,MemFunc>(f);
	}
#endif

template <class P1,class P2,class P3,class TRT,class CallType,
	class TP1,class TP2>
inline CBMemberOf1stArgTranslator3<P1,P2,P3,TRT (CallType::*)(TP1,TP2)const>
MakeDelegate(Delegate3<P1,P2,P3>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2)const;
	return CBMemberOf1stArgTranslator3<P1,P2,P3,MemFunc>(f);
	}


/************************* three args - with return *******************/
#ifndef _MSC_VER
template <class RT, class P1, class P2, class P3, class Func> class CBFunctionTranslator3wRet;
template <class RT, class P1, class P2, class P3, class Callee, class MemFunc> class CBMemberTranslator3wRet;
template <class RT, class P1, class P2, class P3, class MemFunc> class CBMemberOf1stArgTranslator3wRet;
#endif    

template <class RT,class P1,class P2,class P3>
class Delegate3wRet:public DelegateWRetBase<RT>{
public:
	Delegate3wRet(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate3wRet(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateWRetBase<RT>(t), thunk(CBFunctionTranslator3wRet <RT, P1, P2, P3, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate3wRet( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberTranslator3wRet <RT, P1, P2, P3, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate3wRet( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberOf1stArgTranslator3wRet <RT, P1, P2, P3, MEMFUNC>::thunk)  {}
	RT operator()(P1 p1,P2 p2,P3 p3)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2,p3));
		}
	   
	//for STL
	typedef RT result_type;
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
	typedef P3 third_argument_type;
protected:
    // Override
    RT InternalInvokeWithTypedReturn(const RtInvokeVariant* inArgs) const
    {
    	P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2,p3));
    }

	typedef RT (*Thunk)(const DelegateBase &,P1,P2,P3);
	Delegate3wRet(Thunk t,const void *c,DelegateBase::PFunc f,const void *mf,size_t sz):
		DelegateWRetBase<RT>(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class RT,class P1,class P2,class P3,
	class Callee, class MemFunc>
class CBMemberTranslator3wRet:public Delegate3wRet<RT,P1,P2,P3>{
public:
	CBMemberTranslator3wRet(Callee &c,const MemFunc &m):
		Delegate3wRet<RT,P1,P2,P3>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((callee->*memFunc)(p1,p2,p3));
		}
};

template <class RT,class P1,class P2,class P3,class Func>
class CBFunctionTranslator3wRet:public Delegate3wRet<RT,P1,P2,P3>{
public:
	CBFunctionTranslator3wRet(Func f):
		Delegate3wRet<RT,P1,P2,P3>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3)
		{
		return (Func(ftor.getFunc()))(p1,p2,p3);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class P2,class P3,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3>
inline CBMemberTranslator3wRet<RT,P1,P2,P3,Callee,
	TRT (CallType::*)(TP1,TP2,TP3)>
MakeDelegate(Delegate3wRet<RT,P1,P2,P3>*,Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3);
	return CBMemberTranslator3wRet<RT,P1,P2,P3,Callee,MemFunc>(c,f);
	}
#endif

template <class RT,class P1,class P2,class P3,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3>
inline CBMemberTranslator3wRet<RT,P1,P2,P3,const Callee,
	TRT (CallType::*)(TP1,TP2,TP3)const>
MakeDelegate(Delegate3wRet<RT,P1,P2,P3>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3)const;
	return CBMemberTranslator3wRet<RT,P1,P2,P3,const Callee,MemFunc>(c,f);
	}

template <class RT,class P1,class P2,class P3,
	class TRT,class TP1,class TP2,class TP3>
inline CBFunctionTranslator3wRet<RT,P1,P2,P3,TRT (*)(TP1,TP2,TP3)>
MakeDelegate(Delegate3wRet<RT,P1,P2,P3>*,TRT (*f)(TP1,TP2,TP3))
	{
	return CBFunctionTranslator3wRet<RT,P1,P2,P3,TRT (*)(TP1,TP2,TP3)>(f);
	}

template <class RT,class P1,class P2,class P3,class MemFunc>
class CBMemberOf1stArgTranslator3wRet:public Delegate3wRet<RT,P1,P2,P3>{
public:
	CBMemberOf1stArgTranslator3wRet(const MemFunc &m):
		Delegate3wRet<RT,P1,P2,P3>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((p1.*memFunc)(p2,p3));
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class P2,class P3,class TRT,class CallType,
	class TP1,class TP2>
inline CBMemberOf1stArgTranslator3wRet<RT,P1,P2,P3,TRT (CallType::*)(TP1,TP2)>
MakeDelegate(Delegate3wRet<RT,P1,P2,P3>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2);
	return CBMemberOf1stArgTranslator3wRet<RT,P1,P2,P3,MemFunc>(f);
	}
#endif

template <class RT,class P1,class P2,class P3,class TRT,class CallType,
	class TP1,class TP2>
inline CBMemberOf1stArgTranslator3wRet<RT,P1,P2,P3,
	TRT (CallType::*)(TP1,TP2)const>
MakeDelegate(Delegate3wRet<RT,P1,P2,P3>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2)const;
	return CBMemberOf1stArgTranslator3wRet<RT,P1,P2,P3,MemFunc>(f);
	}


/************************* four args - no return *******************/
#ifndef _MSC_VER
template <class P1, class P2, class P3, class P4, class Func> class CBFunctionTranslator4;
template <class P1, class P2, class P3, class P4, class Callee, class MemFunc> class CBMemberTranslator4;
template <class P1, class P2, class P3, class P4, class MemFunc> class CBMemberOf1stArgTranslator4;
#endif
    
template <class P1,class P2,class P3,class P4>
class Delegate4:public DelegateBase{
public:
	Delegate4(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate4(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateBase(t), thunk(CBFunctionTranslator4 <P1, P2, P3, P4, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate4( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberTranslator4 <P1, P2, P3, P4, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate4( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateBase(t), thunk(CBMemberOf1stArgTranslator4 <P1, P2, P3, P4, MEMFUNC>::thunk)  {}
	void operator()(P1 p1,P2 p2,P3 p3,P4 p4)const
		{
		thunk(*this,p1,p2,p3,p4);
		}
	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		P4 p4 = inArgs[3].Get<P4>();
		thunk(*this,p1,p2,p3,p4);
		if (outRet) *outRet = RtInvokeVariant((int32)0);
	}
	//for STL
	typedef void result_type;
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
	typedef P3 third_argument_type;
	typedef P4 fourth_argument_type;
protected:
	typedef void (*Thunk)(const DelegateBase &,P1,P2,P3,P4);
	Delegate4(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		DelegateBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class P3,class P4,
	class Callee, class MemFunc>
class CBMemberTranslator4:public Delegate4<P1,P2,P3,P4>{
public:
	CBMemberTranslator4(Callee &c,const MemFunc &m):
		Delegate4<P1,P2,P3,P4>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(callee->*memFunc)(p1,p2,p3,p4);
		}
};

template <class P1,class P2,class P3,class P4,class Func>
class CBFunctionTranslator4:public Delegate4<P1,P2,P3,P4>{
public:
	CBFunctionTranslator4(Func f):
		Delegate4<P1,P2,P3,P4>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
		{
		(Func(ftor.getFunc()))(p1,p2,p3,p4);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class P4,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3,class TP4>
inline CBMemberTranslator4<P1,P2,P3,P4,Callee,
	TRT (CallType::*)(TP1,TP2,TP3,TP4)>
MakeDelegate(Delegate4<P1,P2,P3,P4>*,Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3,TP4))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3,TP4);
	return CBMemberTranslator4<P1,P2,P3,P4,Callee,MemFunc>(c,f);
	}
#endif

template <class P1,class P2,class P3,class P4,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3,class TP4>
inline CBMemberTranslator4<P1,P2,P3,P4,const Callee,
	TRT (CallType::*)(TP1,TP2,TP3,TP4)const>
MakeDelegate(Delegate4<P1,P2,P3,P4>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3,TP4)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3,TP4)const;
	return CBMemberTranslator4<P1,P2,P3,P4,const Callee,MemFunc>(c,f);
	}

template <class P1,class P2,class P3,class P4,
	class TRT,class TP1,class TP2,class TP3,class TP4>
inline CBFunctionTranslator4<P1,P2,P3,P4,TRT (*)(TP1,TP2,TP3,TP4)>
MakeDelegate(Delegate4<P1,P2,P3,P4>*,TRT (*f)(TP1,TP2,TP3,TP4))
	{
	return CBFunctionTranslator4<P1,P2,P3,P4,TRT (*)(TP1,TP2,TP3,TP4)>(f);
	}

template <class P1,class P2,class P3,class P4,class MemFunc>
class CBMemberOf1stArgTranslator4:public Delegate4<P1,P2,P3,P4>{
public:
	CBMemberOf1stArgTranslator4(const MemFunc &m):
		Delegate4<P1,P2,P3,P4>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static void thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(p1.*memFunc)(p2,p3,p4);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class P4,class TRT,class CallType,
	class TP1,class TP2,class TP3>
inline CBMemberOf1stArgTranslator4<P1,P2,P3,P4,TRT (CallType::*)(TP1,TP2,TP3)>
MakeDelegate(Delegate4<P1,P2,P3,P4>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3);
	return CBMemberOf1stArgTranslator4<P1,P2,P3,P4,MemFunc>(f);
	}
#endif

template <class P1,class P2,class P3,class P4,class TRT,class CallType,
	class TP1,class TP2,class TP3>
inline CBMemberOf1stArgTranslator4<P1,P2,P3,P4,
	TRT (CallType::*)(TP1,TP2,TP3)const>
MakeDelegate(Delegate4<P1,P2,P3,P4>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3)const;
	return CBMemberOf1stArgTranslator4<P1,P2,P3,P4,MemFunc>(f);
	}


/************************* four args - with return *******************/
#ifndef _MSC_VER
template <class RT, class P1, class P2, class P3, class P4, class Func> class CBFunctionTranslator4wRet;
template <class RT, class P1, class P2, class P3, class P4, class Callee, class MemFunc> class CBMemberTranslator4wRet;
template <class RT, class P1, class P2, class P3, class P4, class MemFunc> class CBMemberOf1stArgTranslator4wRet;
#endif

template <class RT,class P1,class P2,class P3,class P4>
class Delegate4wRet:public DelegateWRetBase<RT>{
public:
	Delegate4wRet(RHCB_DUMMY_INIT = 0){}
	template <class FUNC> Delegate4wRet(const CBFunctionTranslatorX <FUNC> & t)
		: DelegateWRetBase<RT>(t), thunk(CBFunctionTranslator4wRet <RT, P1, P2, P3, P4, FUNC>::thunk)  {}
	template <class CLASS, class MEMFUNC> Delegate4wRet( const CBMemberTranslatorX <CLASS, MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberTranslator4wRet <RT, P1, P2, P3, P4, CLASS, MEMFUNC>::thunk)  {}
	template <class MEMFUNC> Delegate4wRet( const CBMemberOf1stArgTranslatorX <MEMFUNC> & t )
		: DelegateWRetBase<RT>(t), thunk(CBMemberOf1stArgTranslator4wRet <RT, P1, P2, P3, P4, MEMFUNC>::thunk)  {}
	RT operator()(P1 p1,P2 p2,P3 p3,P4 p4)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2,p3,p4));
		}
    
	//for STL
	typedef RT result_type;
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
	typedef P3 third_argument_type;
	typedef P4 fourth_argument_type;
protected:
    // Override
    RT InternalInvokeWithTypedReturn(const RtInvokeVariant* inArgs) const
    {
        P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		P4 p4 = inArgs[3].Get<P4>();
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2,p3,p4));
    }

	typedef RT (*Thunk)(const DelegateBase &,P1,P2,P3,P4);
	Delegate4wRet(Thunk t,const void *c,DelegateBase::PFunc f,const void *mf,size_t sz):
    DelegateWRetBase<RT>(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class RT,class P1,class P2,class P3,class P4,
	class Callee, class MemFunc>
class CBMemberTranslator4wRet:public Delegate4wRet<RT,P1,P2,P3,P4>{
public:
	CBMemberTranslator4wRet(Callee &c,const MemFunc &m):
		Delegate4wRet<RT,P1,P2,P3,P4>(thunk,&c,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((callee->*memFunc)(p1,p2,p3,p4));
		}
};

template <class RT,class P1,class P2,class P3,class P4,class Func>
class CBFunctionTranslator4wRet:public Delegate4wRet<RT,P1,P2,P3,P4>{
public:
	CBFunctionTranslator4wRet(Func f):
		Delegate4wRet<RT,P1,P2,P3,P4>(thunk,0,(DelegateBase::PFunc)f,0,0){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
		{
		return (Func(ftor.getFunc()))(p1,p2,p3,p4);
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class P2,class P3,class P4,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3,class TP4>
inline CBMemberTranslator4wRet<RT,P1,P2,P3,P4,Callee,
	TRT (CallType::*)(TP1,TP2,TP3,TP4)>
MakeDelegate(Delegate4wRet<RT,P1,P2,P3,P4>*,Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3,TP4))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3,TP4);
	return CBMemberTranslator4wRet<RT,P1,P2,P3,P4,Callee,MemFunc>(c,f);
	}
#endif

template <class RT,class P1,class P2,class P3,class P4,class Callee,
	class TRT,class CallType,class TP1,class TP2,class TP3,class TP4>
inline CBMemberTranslator4wRet<RT,P1,P2,P3,P4,const Callee,
	TRT (CallType::*)(TP1,TP2,TP3,TP4)const>
MakeDelegate(Delegate4wRet<RT,P1,P2,P3,P4>*,const Callee &c,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3,TP4)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3,TP4)const;
	return CBMemberTranslator4wRet<RT,P1,P2,P3,P4,const Callee,MemFunc>(c,f);
	}

template <class RT,class P1,class P2,class P3,class P4,
	class TRT,class TP1,class TP2,class TP3,class TP4>
inline CBFunctionTranslator4wRet<RT,P1,P2,P3,P4,TRT (*)(TP1,TP2,TP3,TP4)>
MakeDelegate(Delegate4wRet<RT,P1,P2,P3,P4>*,TRT (*f)(TP1,TP2,TP3,TP4))
	{
	return CBFunctionTranslator4wRet
		<RT,P1,P2,P3,P4,TRT (*)(TP1,TP2,TP3,TP4)>(f);
	}


template <class RT,class P1,class P2,class P3,class P4,class MemFunc>
class CBMemberOf1stArgTranslator4wRet:public Delegate4wRet<RT,P1,P2,P3,P4>{
public:
	CBMemberOf1stArgTranslator4wRet(const MemFunc &m):
		Delegate4wRet<RT,P1,P2,P3,P4>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
	static RT thunk(const DelegateBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
		{
		MemFunc &memFunc RHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		return RHCB_BC4_RET_BUG((p1.*memFunc)(p2,p3,p4));
		}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class P2,class P3,class P4,class TRT,
	class CallType,class TP1,class TP2,class TP3>
inline CBMemberOf1stArgTranslator4wRet<RT,P1,P2,P3,P4,
	TRT (CallType::*)(TP1,TP2,TP3)>
MakeDelegate(Delegate4wRet<RT,P1,P2,P3,P4>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3))
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3);
	return CBMemberOf1stArgTranslator4wRet<RT,P1,P2,P3,P4,MemFunc>(f);
	}
#endif

template <class RT,class P1,class P2,class P3,class P4,class TRT,
	class CallType,class TP1,class TP2,class TP3>
inline CBMemberOf1stArgTranslator4wRet<RT,P1,P2,P3,P4,
	TRT (CallType::*)(TP1,TP2,TP3)const>
MakeDelegate(Delegate4wRet<RT,P1,P2,P3,P4>*,
	TRT (CallType::* RHCB_CONST_REF f)(TP1,TP2,TP3)const)
	{
	typedef TRT (CallType::*MemFunc)(TP1,TP2,TP3)const;
	return CBMemberOf1stArgTranslator4wRet<RT,P1,P2,P3,P4,MemFunc>(f);
	}

/************************* Event Section ********************/
/*
	CDH FIXME$$$ this needs more documentation.  For now just
	know that it's modeled after C# events, paired with the
	various Delegate# and Delegate#wRet classes.
	
	You can use operator += and -=, or explicitly call
	Connect/Disconnect if you like.  Operator ^= is like +=,
	but the underlying call to Connect inserts the delegate
	at the front of the delegate list; think of the caret
	visually and you can probably see why that operator was
	chosen (it's a bit of "overload abuse", but whatever).
	
	Operator () on the event will call down to Execute; for
	void-returning events (the common case) this is a
	straightforward multicast, but for events with a return
	value a number of possible operations may occur on the
	individual results to determine an aggregate return value,
	and this is specified by the EventReturnBehavior.  For the
	Event#wRet classes, the default EventReturnBehavior is
	specified as the first template argument, ahead of the
	return type.
*/

#ifdef _MSC_VER
// we disable the following warning because if we try to correct it with RT!=0, it can cause the same warning in reverse depending on the type of RT
#pragma warning(disable: 4800) // 'int' : forcing value to bool 'true' or 'false' (performance warning)
#endif

// Current set of return behaviors for Event#wRet events; this will
// grow over time based on the kinds of aggregations we find useful.
namespace EventReturnBehavior
{
	enum EEventReturnBehavior
	{
		// return value is ignored; always returns zero
		Ignore,

		// return values are accumulated via operator +=
		Accumulate,

		// boolean logic; permutations of logical and/or, short circuiting or not, and default value in case of an empty event
		//   LogicalAnd: If any return false, aggregate returns false
		//   LogicalOr: If any return true, aggregate returns true
		//   ShortCircuit: For LogicalAnd, returns immediately on first false delegate result; for LogicalOr, returns immediately on first true delegate result
		//   NoShortCircult: Executes all delegates before returning aggregate result
		//   DefaultFalse/DefaultTrue: Aggregate value returned in case there are no delegates (and ONLY if there are no delegates), otherwise normal boolean logic is used
		LogicalAnd_ShortCircuit_DefaultFalse,
		LogicalAnd_ShortCircuit_DefaultTrue,
		LogicalAnd_NoShortCircuit_DefaultFalse,
		LogicalAnd_NoShortCircuit_DefaultTrue,
		LogicalOr_ShortCircuit_DefaultFalse,
		LogicalOr_ShortCircuit_DefaultTrue,
		LogicalOr_NoShortCircuit_DefaultFalse,
		LogicalOr_NoShortCircuit_DefaultTrue,
	};
};

class EventBase
{
public:
	virtual void ConnectUnsafe(const DelegateBase* inDelegatePtr, bool inInsertAtFront = false) = 0;
	virtual void DisconnectUnsafe(const DelegateBase* inDelegatePtr) = 0;
	virtual void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const = 0;
};

#define EVENT_DELEGATE_CONTAINER_TYPE std::vector<DelegateType>
#define EVENT_DELEGATE_CONTAINER_ADD(xDelegate, xInsertAtFront) \
	{ \
		if (!xInsertAtFront) \
			mDelegates.push_back(xDelegate); \
		else \
			mDelegates.insert(mDelegates.begin(), xDelegate); \
	}
#define EVENT_DELEGATE_CONTAINER_REMOVE(xDelegate) \
	{ \
		DelegateType d(xDelegate); \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			if (mDelegates[i] == d) \
            { \
                mDelegates.erase(mDelegates.begin()+i); \
                --i; \
				--delegateCount; \
            } \
		} \
	}
#define EVENT_DELEGATE_CONTAINER_REMOVE_INSTANCE(xInstancePtr) \
	{ \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			if (mDelegates[i].GetInstanceContext() == (xInstancePtr)) \
            { \
                mDelegates.erase(mDelegates.begin()+i); \
                --i; \
				--delegateCount; \
            } \
		} \
	}

#define EVENT_BODY_NO_RETURN \
private: \
	typedef EVENT_DELEGATE_CONTAINER_TYPE DelegateContainer; \
	DelegateContainer mDelegates; \
 \
public: \
	void Connect(const DelegateType& inDelegate, bool inInsertAtFront = false) { EVENT_DELEGATE_CONTAINER_ADD(inDelegate, inInsertAtFront); } \
	void ConnectUnsafe(const DelegateBase* inDelegatePtr, bool inInsertAtFront = false) { DelegateType dlg = *((DelegateType*)inDelegatePtr); EVENT_DELEGATE_CONTAINER_ADD(dlg, inInsertAtFront); } \
	template <class CLASS, class MEMFUNC> void Connect(CLASS& inClass, MEMFUNC inMemFunc, bool inInsertAtFront = false) { EVENT_DELEGATE_CONTAINER_ADD(MakeDelegate(inClass, inMemFunc), inInsertAtFront); } \
	template <class FUNC> void Connect(FUNC inFunc, bool inInsertAtFront = false) { EVENT_DELEGATE_CONTAINER_ADD(MakeDelegate(inFunc), inInsertAtFront); } \
 \
	void Disconnect(const DelegateType& inDelegate) { EVENT_DELEGATE_CONTAINER_REMOVE(inDelegate); } \
	void DisconnectUnsafe(const DelegateBase* inDelegatePtr) { DelegateType dlg = *((DelegateType*)inDelegatePtr); EVENT_DELEGATE_CONTAINER_REMOVE(dlg); } \
	template <class CLASS, class MEMFUNC> void Disconnect(CLASS& inClass, MEMFUNC inMemFunc) { EVENT_DELEGATE_CONTAINER_REMOVE(MakeDelegate(inClass, inMemFunc)); } \
	template <class FUNC> void Disconnect(FUNC inFunc) { EVENT_DELEGATE_CONTAINER_REMOVE(MakeDelegate(inFunc)); } \
	void Disconnect(void* inInstanceContext) { EVENT_DELEGATE_CONTAINER_REMOVE_INSTANCE(inInstanceContext); } \
 \
	unsigned long GetDelegateCount() const { return (unsigned long)mDelegates.size(); } \
	const DelegateType& GetDelegateIndexed(unsigned long inIndex) const { return mDelegates[inIndex]; } \
 \
	void Reset() { mDelegates.clear(); } \
 \
	void Execute EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
            mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
	} \
 \
	inline void operator += (const DelegateType& inDelegate) { Connect(inDelegate); } \
	inline void operator ^= (const DelegateType& inDelegate) { Connect(inDelegate, true); } \
	inline void operator -= (const DelegateType& inDelegate) { Disconnect(inDelegate); } \
	inline void operator -= (void* inInstanceContext) { Disconnect(inInstanceContext); } \
	inline void operator() EVENT_EXECUTE_FORMALARGUMENTS const { return Execute EVENT_EXECUTE_ACTUALARGUMENTS; } \


#define EVENT_BODY_WITH_RETURN \
private: \
	typedef EVENT_DELEGATE_CONTAINER_TYPE DelegateContainer; \
	DelegateContainer mDelegates; \
 \
public: \
	void Connect(const DelegateType& inDelegate, bool inInsertAtFront = false) { EVENT_DELEGATE_CONTAINER_ADD(inDelegate, inInsertAtFront); } \
	void ConnectUnsafe(const DelegateBase* inDelegatePtr, bool inInsertAtFront = false) { DelegateType dlg = *((DelegateType*)inDelegatePtr); EVENT_DELEGATE_CONTAINER_ADD(dlg, inInsertAtFront); } \
	template <class CLASS, class MEMFUNC> void Connect(CLASS& inClass, MEMFUNC inMemFunc, bool inInsertAtFront = false) { EVENT_DELEGATE_CONTAINER_ADD(MakeDelegate(inClass, inMemFunc), inInsertAtFront); } \
	template <class FUNC> void Connect(FUNC inFunc, bool inInsertAtFront = false) { EVENT_DELEGATE_CONTAINER_ADD(MakeDelegate(inFunc), inInsertAtFront); } \
 \
	void Disconnect(const DelegateType& inDelegate) { EVENT_DELEGATE_CONTAINER_REMOVE(inDelegate); } \
	void DisconnectUnsafe(const DelegateBase* inDelegatePtr) { DelegateType dlg = *((DelegateType*)inDelegatePtr); EVENT_DELEGATE_CONTAINER_REMOVE(dlg); } \
	template <class CLASS, class MEMFUNC> void Disconnect(CLASS& inClass, MEMFUNC inMemFunc) { EVENT_DELEGATE_CONTAINER_REMOVE(MakeDelegate(inClass, inMemFunc)); } \
	template <class FUNC> void Disconnect(FUNC inFunc) { EVENT_DELEGATE_CONTAINER_REMOVE(MakeDelegate(inFunc)); } \
	void Disconnect(void* inInstanceContext) { EVENT_DELEGATE_CONTAINER_REMOVE_INSTANCE(inInstanceContext); } \
 \
	unsigned long GetDelegateCount() const { return (unsigned long)mDelegates.size(); } \
	const DelegateType& GetDelegateIndexed(unsigned long inIndex) const { return mDelegates[inIndex]; } \
 \
	void Reset() { mDelegates.clear(); } \
 \
	RT Execute EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		switch(EVENTRETURNBEHAVIOR) \
		{ \
		case EventReturnBehavior::Accumulate: return ExecuteAccumulateResult EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalAnd_ShortCircuit_DefaultFalse: return ExecuteLogicalAnd_ShortCircuit_DefaultFalse EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalAnd_ShortCircuit_DefaultTrue: return ExecuteLogicalAnd_ShortCircuit_DefaultTrue EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalAnd_NoShortCircuit_DefaultFalse: return ExecuteLogicalAnd_NoShortCircuit_DefaultFalse EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalAnd_NoShortCircuit_DefaultTrue: return ExecuteLogicalAnd_NoShortCircuit_DefaultTrue EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalOr_ShortCircuit_DefaultFalse: return ExecuteLogicalOr_ShortCircuit_DefaultFalse EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalOr_ShortCircuit_DefaultTrue: return ExecuteLogicalOr_ShortCircuit_DefaultTrue EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalOr_NoShortCircuit_DefaultFalse: return ExecuteLogicalOr_NoShortCircuit_DefaultFalse EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::LogicalOr_NoShortCircuit_DefaultTrue: return ExecuteLogicalOr_NoShortCircuit_DefaultTrue EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		case EventReturnBehavior::Ignore: /* fallthrough */ \
		default: \
			return ExecuteIgnoreResult EVENT_EXECUTE_ACTUALARGUMENTS; break; \
		} \
	} \
 \
	RT ExecuteIgnoreResult EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
			mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
		return (RT)0; \
	} \
	RT ExecuteAccumulateResult EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		RT result = (RT)0; \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
			result += mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
		return result; \
	} \
	RT ExecuteLogicalAnd_ShortCircuit_DefaultFalse EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		if (mDelegates.empty()) \
			return (RT)false; \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			if (result == (RT)false) \
				return result; \
		} \
		return (RT)true; \
	} \
	RT ExecuteLogicalAnd_ShortCircuit_DefaultTrue EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			if (result == (RT)false) \
				return result; \
		} \
		return (RT)true; \
	} \
	RT ExecuteLogicalAnd_NoShortCircuit_DefaultFalse EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		if (mDelegates.empty()) \
			return (RT)false; \
		bool accResult = true; \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			accResult = accResult && (bool)result; \
		} \
		return (RT)accResult; \
	} \
	RT ExecuteLogicalAnd_NoShortCircuit_DefaultTrue EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		bool accResult = true; \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			accResult = accResult && (bool)result; \
		} \
		return (RT)accResult; \
	} \
	RT ExecuteLogicalOr_ShortCircuit_DefaultFalse EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			if (result != (RT)false) \
				return result; \
		} \
		return (RT)false; \
	} \
	RT ExecuteLogicalOr_ShortCircuit_DefaultTrue EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		if (mDelegates.empty()) \
			return (RT)true; \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			if (result != (RT)false) \
				return result; \
		} \
		return (RT)false; \
	} \
	RT ExecuteLogicalOr_NoShortCircuit_DefaultFalse EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		bool accResult = false; \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			accResult = accResult || (bool)result; \
		} \
		return (RT)accResult; \
	} \
	RT ExecuteLogicalOr_NoShortCircuit_DefaultTrue EVENT_EXECUTE_FORMALARGUMENTS const \
	{ \
		if (mDelegates.empty()) \
			return (RT)true; \
		bool accResult = false; \
        int delegateCount = (int)mDelegates.size(); \
        for (int i=0; i<delegateCount; ++i) \
		{ \
			RT result = mDelegates[i] EVENT_EXECUTE_ACTUALARGUMENTS; \
			accResult = accResult || (bool)result; \
		} \
		return (RT)accResult; \
	} \
 \
	inline void operator += (const DelegateType& inDelegate) { Connect(inDelegate); } \
	inline void operator ^= (const DelegateType& inDelegate) { Connect(inDelegate, true); } \
	inline void operator -= (const DelegateType& inDelegate) { Disconnect(inDelegate); } \
	inline void operator -= (void* inInstanceContext) { Disconnect(inInstanceContext); } \
	inline RT operator() EVENT_EXECUTE_FORMALARGUMENTS const { return Execute EVENT_EXECUTE_ACTUALARGUMENTS; } \

// Event0
#define EVENT_EXECUTE_FORMALARGUMENTS ()
#define EVENT_EXECUTE_ACTUALARGUMENTS ()
class Event0
: public EventBase
{
public:
	typedef Delegate0 DelegateType;

	EVENT_BODY_NO_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		Execute();
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event1
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1)
template <class P1>
class Event1
: public EventBase
{
public:
	typedef Delegate1<P1> DelegateType;

	EVENT_BODY_NO_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		Execute(p1);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event2
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1, P2 p2)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1, p2)
template <class P1, class P2>
class Event2
: public EventBase
{
public:
	typedef Delegate2<P1,P2> DelegateType;

	EVENT_BODY_NO_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		Execute(p1, p2);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event3
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1, P2 p2, P3 p3)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1, p2, p3)
template <class P1, class P2, class P3>
class Event3
: public EventBase
{
public:
	typedef Delegate3<P1,P2,P3> DelegateType;

	EVENT_BODY_NO_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		Execute(p1, p2, p3);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event4
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1, P2 p2, P3 p3, P4 p4)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1, p2, p3, p4)
template <class P1, class P2, class P3, class P4>
class Event4
: public EventBase
{
public:
	typedef Delegate4<P1,P2,P3,P4> DelegateType;

	EVENT_BODY_NO_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		P4 p4 = inArgs[3].Get<P4>();
		Execute(p1, p2, p3, p4);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event0wRet
#define EVENT_EXECUTE_FORMALARGUMENTS ()
#define EVENT_EXECUTE_ACTUALARGUMENTS ()
template <int EVENTRETURNBEHAVIOR, class RT>
class Event0wRet
: public EventBase
{
public:
	typedef Delegate0wRet<RT> DelegateType;

	EVENT_BODY_WITH_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		RT rt = Execute();
		if (outRet) *outRet = RtInvokeVariant(rt);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event1wRet
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1)
template <int EVENTRETURNBEHAVIOR, class RT, class P1>
class Event1wRet
: public EventBase
{
public:
	typedef Delegate1wRet<RT,P1> DelegateType;

	EVENT_BODY_WITH_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		RT rt = Execute(p1);
		if (outRet) *outRet = RtInvokeVariant(rt);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event2wRet
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1, P2 p2)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1, p2)
template <int EVENTRETURNBEHAVIOR, class RT, class P1, class P2>
class Event2wRet
: public EventBase
{
public:
	typedef Delegate2wRet<RT,P1,P2> DelegateType;

	EVENT_BODY_WITH_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		RT rt = Execute(p1,p2);
		if (outRet) *outRet = RtInvokeVariant(rt);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event3wRet
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1, P2 p2, P3 p3)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1, p2, p3)
template <int EVENTRETURNBEHAVIOR, class RT, class P1, class P2, class P3>
class Event3wRet
: public EventBase
{
public:
	typedef Delegate3wRet<RT,P1,P2,P3> DelegateType;

	EVENT_BODY_WITH_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		RT rt = Execute(p1,p2,p3);
		if (outRet) *outRet = RtInvokeVariant(rt);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

// Event4wRet
#define EVENT_EXECUTE_FORMALARGUMENTS (P1 p1, P2 p2, P3 p3, P4 p4)
#define EVENT_EXECUTE_ACTUALARGUMENTS (p1, p2, p3, p4)
template <int EVENTRETURNBEHAVIOR, class RT, class P1, class P2, class P3, class P4>
class Event4wRet
: public EventBase
{
public:
	typedef Delegate4wRet<RT,P1,P2,P3,P4> DelegateType;

	EVENT_BODY_WITH_RETURN

	void Invoke(RtInvokeVariant* outRet, const RtInvokeVariant* inArgs) const
	{
		P1 p1 = inArgs[0].Get<P1>();
		P2 p2 = inArgs[1].Get<P2>();
		P3 p3 = inArgs[2].Get<P3>();
		P4 p4 = inArgs[3].Get<P4>();
		RT rt = Execute(p1,p2,p3,p4);
		if (outRet) *outRet = RtInvokeVariant(rt);
	}
};
#undef EVENT_EXECUTE_FORMALARGUMENTS
#undef EVENT_EXECUTE_ACTUALARGUMENTS

/************************* Delegate Closures ********************/

/*
	DelegateClosure - small convenience wrapper around a delegate
	whose object context actually contains the delegate itself.
	Used mostly for lightweight callbacks that need some context;
	this context can be specified as structure members which are
	initialized in the constructor.  The subclass then implements
	the closure function itself as "Func" with a signature matching
	the provided delegate type.

	In this sense it's somewhat like a closure, but with the
	environment capture context provided explicitly (via constructor
	arguments), and Func representing the closure signature.
	We could ostensibly do some preprocessor magic to make this
	look more like C++2011 lambdas, but alas the processor just
	isn't quite flexible enough when it comes to compound statements
	and formal/actual argument signatures etc.  So this is as close
	as we can do for now.  Still pretty useful though; they're verbose
	to define but easy to actually use, and the latter is usually more
	common than the former.

	Example:

	// DelegateClosure takes the subclass itself, and the signature
	// expressed as a delegate type, as template arguments
	struct MyClosure
	: public DelegateClosure<MyClosure, Delegate2wRet<bool, float, char*> >
	{
	    // capture context expressed as structure members
		float mCaptureContextFloat;
		char* mCaptureContextString;

		// initialization of capture context through constructor
		MyClosure(float inFloat, char* inString)
		: mCaptureContextFloat(inFloat)
		, mCaptureContextString(inString)
		{}

		// Func signature matches the delegate type provided as a
		// template argument in the DelegateClosure derivation above
		bool Func(float inArgFloat, char* inArgString)
		{
			return ((inArgFloat == mCaptureContextFloat)
			     && (!strcmp(inArgString, mCaptureContextString)));
		}
	};

	MyClosure closure(12345.f, "Capture Context String"); // create the closure object
	Delegate2wRet<bool, float, char*> someDelegate = closure; // conversion to delegate type is allowed
	bool delegateResult = someDelegate(54321.f, "Argument String"); // first invocation
	printf("Delegate result is %s\n", delegateResult ? "true" : "false");
	delegateResult = someDelegate(12345.f, "Capture Context String"); // second invocation
	printf("Delegate result is %s\n", delegateResult ? "true" : "false");

	Output:
	
	Delegate result is false
	Delegate result is true
*/
template <class SUBCLASS, class DELEGATECLASS>
class DelegateClosure
{
protected:
	DELEGATECLASS mDelegate;

public:
	DelegateClosure() { mDelegate = MakeDelegate(*((SUBCLASS*)this), &SUBCLASS::Func); }

	DELEGATECLASS& GetDelegate() { return mDelegate; }
	const DELEGATECLASS& GetDelegate() const { return mDelegate; }

	operator DELEGATECLASS& () { return mDelegate; }
	operator const DELEGATECLASS& () const { return mDelegate; }
};

#ifdef _MSC_VER
#pragma warning(default: 4800) // 'int' : forcing value to bool 'true' or 'false'
#endif

/***************************** the end ***********************/

#ifdef RHCB_NAMESPACE
}
#endif

#endif	// __RTDELEGATE_H__
