#pragma once
#ifndef __RTOBJECT_H__
#define __RTOBJECT_H__
//****************************************************************************
//**
//**  File     :  RTOBJECT.H
//**  Summary  :  Header - RtObject, RtClass, and related support
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
/*
	"Runtime Object" system

	This component defines basic pseudo-reflective metaclasses and objects,
	based mostly on a pattern called "Reflective Factory" which I wrote many
	years ago, and which you can find here:
	
	http://www.gamedev.net/reference/articles/article1415.asp

	The code below is mostly the same as the example code I provided with that
	pattern, with a few syntactic sugar changes (such as increased template
	method usage now that MSVC doesn't horribly break on them).

	I'm wary to call this type of system "reflection" any more now that I've
	gone on to create real reflection systems; this is far more simplistic
	than that (although it works quite well alongside actual reflection
	support).  But despite this simplicity it's still a very useful pattern,
	and for lack of a better term we're calling it the RtObject system (short
	for "runtime object") because of its similarities to Rtti, but not
	specific to type information alone.
	
	The basic idea is that RtObjects have a bit more information about their
	runtime characteristics (such as metaclass information) than
	non-RtObjects usually do.  The nature of this additional information can
	and will change over time (via reflection information, hooks into object
	databases for serialization etc), but the essential idea remains the same.
*/
//============================================================================
//    HEADERS
//============================================================================
#include "RtId.h"

// external forward declarations
#ifdef SUPPORT_REFLECTION
namespace Reflection
{
	class RClass;
}
#endif

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
/*
	Internal macros; do not use directly
*/
#define RT_CLASS_DEFINE_BASE(xClass, xMetaClass) \
	private: \
		static xMetaClass* sClass; \
	public: \
		typedef xClass ThisClass; \
		typedef xMetaClass MetaClass; \
		\
		virtual Sexy::RtClass* GetClass() const override; \

#if !SEXY_IS_PLATFORM_WINDOWS
#	define REFERENCED_STATIC_METHOD __attribute((used))
#else
#	define REFERENCED_STATIC_METHOD 
#endif

// Adding REFERENCED_STATIC_METHOD to StaticGetClass(). This informs the compiler that this static method is actually referenced in the code and should be compiled in.
#define RT_CLASS_DEFINE_NEEDNEW(xClass, xSuperClass, xMetaClass) \
	RT_CLASS_DEFINE_BASE(xClass, xMetaClass); \
	typedef xSuperClass SuperClass; \
	static xMetaClass* StaticGetClass() REFERENCED_STATIC_METHOD;\
	static void StaticClassInit()	
	
#define RT_CLASS_DEFINE_ABSTRACTNEW(xClass) \
	private: \
		static xClass* StaticNew(); \
	public: \
		virtual bool IsAbstract() const override;

#define RT_CLASS_DEFINE_CONCRETENEW(xClass) \
	public: \
		static xClass* StaticNew(); \
		virtual bool IsAbstract() const override;

/*
	RT_CLASS_DEFINE(xClass, xSuperClass, xMetaClass)

	Macro used in the public interface of *concrete* RtObject-derived classes.
	xClass is the class name, xSuperClass is the immediate base class (RtObject
	or one of its subclasses), and xMetaClass is the class type (RtClass or one
	of its subclasses).

	The macro is immediately followed by braces containing the class initializer,
	which happens when the metaclass is first instantiated.  If the metaclass is
	RtClass itself, this block is usually empty (just a {} pair).  If a subclass
	of RtClass is used, this block can be used to set custom class properties etc.
	The block can also be placed in an implementation file instead, as a method
	with the name "StaticClassInit"; see Example 3.

	Example 1:
	
	RT_CLASS_DEFINE(RtMyObject, RtObject, RtClass) {}

	Example 2:
	
	RT_CLASS_DEFINE(RtMyObject, RtMyBaseObject, RtMyMetaClass)
	{
		StaticGetClass()->SetMyMetaClassStringProperty("Some string");
	}

	Example 3:

	// in the interface
	RT_CLASS_DEFINE(RtMyObject, RtMyBaseObject, RtMyMetaClass);
	// in the implementation
	void RtMyObject::StaticClassInit()
	{
		StaticGetClass()->SetMyMetaClassStringProperty("Some string");
	}
*/
#define RT_CLASS_DEFINE(xClass, xSuperClass, xMetaClass) \
	RT_CLASS_DEFINE_CONCRETENEW(xClass); \
	RT_CLASS_DEFINE_NEEDNEW(xClass, xSuperClass, xMetaClass)

/*
	RT_CLASS_DEFINE_ABSTRACT(xClass, xSuperClass, xMetaClass)
	
	Macro used in the public interface of *abstract* RtObject-derived classes.

	The usage is exactly the same as RT_CLASS_DEFINE, except that
	the class is not allowed to be directly "new"d; this is used for abstract
	base classes that have pure virtual methods etc.
*/
#define RT_CLASS_DEFINE_ABSTRACT(xClass, xSuperClass, xMetaClass) \
	RT_CLASS_DEFINE_ABSTRACTNEW(xClass); \
	RT_CLASS_DEFINE_NEEDNEW(xClass, xSuperClass, xMetaClass)

/*
	RT_CLASS_IMPLEMENT(xClass)

	Macro used in a single .cpp file to hold the internal implementation
	of an RtObject-derived class.  Any RtObject-derived class must have this
	macro present once (and only once) in some source .cpp file for the
	matching library or executable, in order to avoid linker errors (if you
	get a linker error indicating that an "sClass" is missing, you probably
	forgot one of these).
*/
#define RT_CLASS_IMPLEMENT_BASE(xClass) \
    xClass::MetaClass* xClass::sClass = xClass::StaticGetClass(); \
    Sexy::RtClass* xClass::GetClass() const \
    { \
        return StaticGetClass(); \
    } \
    xClass::MetaClass* xClass::StaticGetClass() \
    { \
        if (!xClass::sClass) \
        { \
            xClass::sClass = xClass::MetaClass::StaticNew(); \
            xClass::sClass->ClassInit(#xClass, xClass::SuperClass::StaticGetClass(), (RtObject*(*)())xClass::StaticNew); \
            StaticClassInit(); \
        } \
        return xClass::sClass; \
    } \

#define RT_CLASS_IMPLEMENT(xClass) \
    RT_CLASS_IMPLEMENT_BASE(xClass) \
    xClass* xClass::StaticNew() \
    { \
        return new xClass; \
    } \
    bool xClass::IsAbstract() const \
    { \
        return false; \
    } \

#define RT_CLASS_IMPLEMENT_ABSTRACT(xClass) \
    RT_CLASS_IMPLEMENT_BASE(xClass) \
    xClass* xClass::StaticNew() \
    { \
        return 0; \
    } \
    bool xClass::IsAbstract() const \
    { \
        return true; \
    } \

/*
	RTC(xClass)
	
	Shorthand macro for easy metaclass access.  Because it's so short and
	may potentially clash with another macro/identifier, it is not used
	internally within the RtObject code, and can conditionally be omitted.
*/
#ifndef RT_NO_RTC_MACRO
	#define RTC(xClass) xClass::StaticGetClass()
#endif // RT_NO_RTC_MACRO

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
class RtObject;
class RtClass;
class RtProtocol;
class RtProtocolClass;
class RtSerializeContext;

/*
	RtObject

	Base "runtime object" type.  Any class wishing to use features
	like GetClass, IsA, etc. must derive from this type (in the case of
	multiple inheritance, RtObject must be the first base class).  Note that
	RtObject does not possess any data; its only added size overhead is a v-table.

	Along with the provided methods, RtObject-derived classes also have several useful
	typedefs that can be utilized in code: ThisClass, SuperClass, and MetaClass.
	These are typedef'ed to be the same as the arguments provided to
	RT_CLASS_DEFINE (for example, if RtMyObject's immediate superclass is RtObject,
	then RtMyObject::SuperClass will be typedef'ed to RtObject).

	Because RtObject-derived classes can be instantiated virtually (via RtClass::New()),
	they must have a default (no-argument) constructor available in order to compile.
	For this reason, a recommended pattern is to use initialization arguments on
	separate "Init" functions, rather than directly on constructors.
*/
class RtObject // abstract
{
protected:
	RtObject();

public:
    private:
        static RtClass* sClass;
    public:
        typedef RtObject ThisClass;
        typedef RtClass MetaClass;
    
        virtual Sexy::RtClass* GetClass() const;
    private:
        static RtObject* StaticNew();
    public:
        virtual bool IsAbstract() const;

	static RtClass* StaticGetClass();
    
    static std::vector<RtObject*> s_gm;
	/*
		Virtual destructor is required for RtObject-derived classes
	*/
	virtual ~RtObject();

	/*
		Method used to determine if this object is an instantiation of a given
		class or one of its subclasses.  If the provided metaclass is known at
		compile time, the template form below may be more convenient.
	*/
	virtual bool IsA(const RtClass* inClass) const;

	/*
		Delete the object; used as an alternative to the destructor so that
		derived-class virtual tables will remain intact during the deletion
		process.
	*/
    virtual void Delete();

	/*
		Template form of IsA, for classes known at compile time.  Note that this
		form is safe for null objects, so "obj" in the following example can be
		null and if so will return false accordingly (reducing the number of
		checks that calling code has to make).

		Example: bool isAMyObject = obj->IsA<RtMyObject>();
	*/
	template<class T> bool IsA() const { return this ? IsA(T::StaticGetClass()) : 0; }
	
	/*
		Dynamic-cast to a given type, based on IsA (will convert to null if IsA fails).

		Example: RtMyObject* myObj = obj->Cast<RtMyObject>();
	*/
	template<class T> T* Cast() const { return IsA<T>() ? (T*)this : 0; }
	
	/*
		Dynamic cast that assumes the desired type, with a DBG_ASSERT IsA test
	*/
	template<class T> T* CastChecked() const
	{
		DBG_ASSERT(IsA<T>());
		return (T*)this;
	}

	virtual bool Serialize(const RtSerializeContext& inContext);

	//PVZ2_CHINESE_BEGIN
	virtual bool SerializeJsonToObj(const std::string &i_json, const std::string& i_key);
	virtual bool SerializeObjToJson(std::string& i_json, const std::string& i_key);
	//PVZ2_CHINESE_END
};

/*
	RtClass

	Base metaclass type.  RtObject and all of its subclasses each have
	one RtClass instance (or a subclass of RtClass), accessible in one of
	two ways:

	Method 1: Get an RtClass via an object instance:

	RtObject* obj;
	RtClass* cls = obj->GetClass();

	Method 2: Get an RtClass statically from a given type:

	RtClass* cls = RtMyObject::StaticGetClass();

	Once you have the RtClass, you can then access information about the
	class such as its name, superclass, etc.  You can also use the RtClass
	to New() an instance of that class, even if you don't know the concrete
	class that is being constructed.

	If the given metaclass is actually a subclass of RtClass, you can Cast
	the RtClass to this metaclass to get additional class-specific information
	or perform other operations (note that the Cast is only required when
	GetClass() is used; StaticGetClass() will provide the appropriate metaclass
	directly).

	RtClass also has a handful of static methods, used to iterate through the
	classes in the system or to find a class by name.
*/
class RtClass
: public RtObject
{
protected:
	typedef std::vector<RtClass*> DVectorClass;
	typedef std::map<std::string, RtClass*> DMapStringToClass;
	typedef std::vector<RtProtocol*> DProtocolVector;

	const char* mClassName;
	RtClass* mClassSuper;
	RtObject* (*mClassNewFunc)();
	RtId mClassRtId;
	DProtocolVector mClassProtocolVector;
#ifdef SUPPORT_REFLECTION
	Reflection::RClass* mClassReflectionClass;
#endif

	static DVectorClass& StaticGetClassVectorRef();
	static DMapStringToClass& StaticGetClassMapRef();

public:
	RT_CLASS_DEFINE(RtClass, RtObject, RtClass);

	RtClass();
	~RtClass();

	/*
		Get the number of classes in the system, or a given class object
		by index less than this number.
	*/
	static unsigned long StaticGetClassCount();
	static RtClass* StaticGetClassIndexed(unsigned long inIndex);

	/*
		Get a class of a specific name; returns null if the class
		does not exist.
	*/
	static RtClass* StaticGetClassNamed(const char* inClassName);
	
	/*
		Cleanup function called on application shutdown, to delete
		the class instances (used to prevent memory leaks).
	*/
	static void StaticCleanup();

	/*
		Get the name of the class
	*/
	inline const char* GetName() const { return mClassName; }

	/*
		Get the superclass of the class (the single base class provided
		to the RT_CLASS_DEFINE macro, and the first class inherited from).
	*/
	inline RtClass* GetSuper() const { return mClassSuper; }
	
	/*
		Create an instance of the class; will return null if the class is abstract
	*/
	inline RtObject* New() const { return mClassNewFunc(); }
	
	/*
		Return whether or not a given class is part of this class's superclass
		chain (note that this *includes* this class, i.e. cls->IsDerivedFrom(cls)
		will return true).  Used by object "IsA" tests; effectively, obj->IsA(cls)
		is the same as obj->GetClass()->IsDerivedFrom(cls).
	*/
	virtual bool IsDerivedFrom(const RtClass* inClass) const;

	/*
		Template form of IsDerivedFrom, for convenience
	*/
	template<class T> bool IsDerivedFrom() const { return IsDerivedFrom(T::StaticGetClass()); }

	/*
		Get the RtId of this object within the system RtDbTable for RtClasses
	*/
	inline RtId GetRtId() { return mClassRtId; }

#ifdef SUPPORT_REFLECTION
	/*
		Set/get the bound reflection class equivalent for this RtClass, if one exists
	*/
	inline void SetBoundReflectionClass(Reflection::RClass* inClass) { mClassReflectionClass = inClass; }
	inline Reflection::RClass* GetBoundReflectionClass(bool inInherited = true) const
	{
		if (mClassReflectionClass || !inInherited)
			return mClassReflectionClass;

		for (const RtClass* cls = this; cls; cls = cls->GetSuper())
		{
			if (cls->mClassReflectionClass)
				return cls->mClassReflectionClass;
		}
		return NULL;
	}
#endif

	/*
		Add a protocol object, or find an existing protocol object by protocol class

		Note that when you add a protocol object, you relinquish control of the object;
		the RtClass will automatically delete all attached protocols when the class
		itself is deleted.
	*/
	void AddProtocol(RtProtocol* inProtocol);
	RtProtocol* FindProtocol(RtProtocolClass* inClass) const;

	/*
		Template form of FindProtocol, for convenience
	*/
	template <class T> T* FindProtocol() const { return FindProtocol(T::StaticGetClass())->template Cast<T>(); }

	/*
		Internal class initialization method; should not be called directly
	*/
	virtual void ClassInit(const char* inName, RtClass* inSuper, RtObject* (*inNewFunc)());

	virtual bool Serialize(const RtSerializeContext& inContext) override;
};

/*
	RtProtocolClass
	RtProtocol

	Protocols represent class-supported auxiliary "interfaces" which are not
	necessarily identified in the (fixed, compile-time) class interface
	directly, but rather determined at runtime via queries on the class
	using the FindProtocol method.  Classes which support a protocol can
	instantiate one during their static class initialization and add it
	onto the class via AddProtocol, so that later FindProtocol checks can
	retrieve it.

	The intent of this approach is to reduce feature "bubbling" up the
	class hierarchy.  The RtObject system is heavily based on single
	inheritance, which is a problem when multiple "fundamental" cross-cutting
	features come into play.  The naive approach would eventually have all
	of these "fundamental" features work their way up the hierarchy until they
	wind up in RtObject itself, which would transform from a lightweight
	data-less base class (vtbl notwithstanding) into a monstrosity.  This must
	be avoided at all costs.  By querying classes for what protocols they
	support, any RtObject can support any protocol interface without having
	another system automatically assume that they do just by nature of the
	object type alone, mitigating the bubbling effect.
	
	Most protocols support their interfaces via Delegates, which a class
	binds to during the static class initialization.  The delegate function
	can then either implement the matching protocol method directly, or route
	it to an appropriate method on the individual objects themselves depending
	on the situation.

	There are obvious (albeit usually minor) performance implications for
	the indirections involved in this approach.  Fortunately most of the
	systems involving protocols are not themselves performance-critical,
	at least on the framework side; application-specific protocols may have
	other constraints, but the fact that they're application-specific means
	that specialized knowledge may be available to find a more efficient
	alternative in these situations (for example, applications can use
	distinct RtDb tables for specialized object components that can be
	processed in bulk, instead of individually off their containing objects
	with slower protocol checks).
	
	The important takeaway here is that we want to watch out for bubbling in
	general, and use protocols whenever possible (with performance requirements
	being one of the limits on "possible") to prevent its far-reaching effects.

	If this documentation seems confusing, take a look at the usage of some
	system protocols like RtIdProtocol, to get a sense of what's going on.
*/
class RtProtocolClass
: public RtClass
{
public:
	RT_CLASS_DEFINE(RtProtocolClass, RtClass, RtClass) {}
};
class RtProtocol
: public RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(RtProtocol, RtObject, RtProtocolClass) {}
};

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
//**    END HEADER RTOBJECT.H
//**
//****************************************************************************


#endif // __RTOBJECT_H__
