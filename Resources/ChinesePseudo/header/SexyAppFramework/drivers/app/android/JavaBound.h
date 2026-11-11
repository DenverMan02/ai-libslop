#pragma once

#include <string>
#include <jni.h>
#include <stdarg.h>
#include <android/log.h>

// --------------------------------------------------------------------------
// class JavaString
// --------------------------------------------------------------------------

class JavaString
{
	JNIEnv* mEnv;
	jstring mStr;
public:
	JavaString( JNIEnv* env, const std::string& str );
	~JavaString();
	operator jstring();
	
	static std::string ToString( JNIEnv* env, jstring jstr );
};

inline JavaString::JavaString( JNIEnv* env, const std::string& str )
	: mEnv( env )
{
	mStr = mEnv->NewStringUTF( str.c_str() );
}

inline JavaString::~JavaString()
{
	mEnv->DeleteLocalRef( mStr );
}

inline JavaString::operator jstring()
{
	return mStr;
}

// --------------------------------------------------------------------------
// class JavaException
// --------------------------------------------------------------------------

class JavaException
{
public:
   static bool CheckAndClear( JNIEnv* env );
};

// --------------------------------------------------------------------------
// class JavaClass
// --------------------------------------------------------------------------

class JavaClass
{
public:

	JavaClass();
	virtual ~JavaClass();
	bool init( JNIEnv* env, const char* javaClassName );
	bool valid() const;
	operator jclass() const;
	const std::string& name() const;
	void registerNatives( const JNINativeMethod* nativeMethods, jint count ) const;

protected:

	JNIEnv* mEnv;
	jclass mClass;
	std::string mDebugName;

};

// --------------------------------------------------------------------------
// class JavaMethodBase
// --------------------------------------------------------------------------

class JavaMethodBase
{
public:

	JavaMethodBase();
	bool init( JNIEnv* env, const JavaClass& javaClass, const char* name, const char* signature );
	bool valid();
	operator jmethodID() const;
	const std::string& name() const;

protected:

	JNIEnv* mEnv;
	jmethodID mID;
	std::string mDebugName;

};

// --------------------------------------------------------------------------
// class JavaMethod
// --------------------------------------------------------------------------

template< typename JavaReturnType >
class JavaMethod
	: public JavaMethodBase
{
public:
	JavaReturnType operator()( JNIEnv* env, jobject instance, ... )
	{
		JavaReturnType result;
		va_list arguments;
		va_start( arguments, instance );
		if ( NULL == mID )
		{
			__android_log_print( ANDROID_LOG_ERROR, "JavaMethod", "no methodID to call %s", mDebugName.c_str() );
		}
		else if ( NULL == instance )
		{
			__android_log_print( ANDROID_LOG_ERROR, "JavaMethod", "no jobject to call %s", mDebugName.c_str() );
		}
		else
		{
			//__android_log_print( ANDROID_LOG_DEBUG, "JavaMethod", "<%p> call %s", instance, mDebugName.c_str() );
			result = callv( env, instance, arguments );
		}
		va_end( arguments );
		JavaException::CheckAndClear( env );
		return result;
	}

protected:
	JavaReturnType callv( JNIEnv* env, jobject instance, va_list args )
	{
		__android_log_print( ANDROID_LOG_ERROR, "JavaMethod", "callv() - should never call this un-specialized implementation.  It doesn't invoke anything!" );
		return JavaReturnType();
	}

};

template<>
inline void JavaMethod< void >::operator()( JNIEnv* env, jobject instance, ... )
{
	va_list arguments;
	va_start( arguments, instance );
	if ( NULL == mID )
	{
		__android_log_print( ANDROID_LOG_ERROR, "JavaMethod", "no methodID to call %s", mDebugName.c_str() );
	}
	else if ( NULL == instance )
	{
		__android_log_print( ANDROID_LOG_ERROR, "JavaMethod", "no jobject to call %s", mDebugName.c_str() );
	}
	else
	{
		//__android_log_print( ANDROID_LOG_DEBUG, "JavaMethod", "<%p> call %s", instance, mDebugName.c_str() );
		env->CallVoidMethodV( instance, mID, arguments );
	}
	va_end( arguments );
	JavaException::CheckAndClear( env );
}

template<>
inline jobject JavaMethod< jobject >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallObjectMethodV( instance, mID, arguments );
}

template<>
inline jstring JavaMethod< jstring >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return (jstring)env->CallObjectMethodV( instance, mID, arguments );
}

template<>
inline jboolean JavaMethod< jboolean >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallBooleanMethodV( instance, mID, arguments );
}

template<>
inline jbyte JavaMethod< jbyte >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallByteMethodV( instance, mID, arguments );
}

template<>
inline jchar JavaMethod< jchar >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallCharMethodV( instance, mID, arguments );
}

template<>
inline jshort JavaMethod< jshort >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallShortMethodV( instance, mID, arguments );
}

template<>
inline jint JavaMethod< jint >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallIntMethodV( instance, mID, arguments );
}

template<>
inline jlong JavaMethod< jlong >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallLongMethodV( instance, mID, arguments );
}

template<>
inline jfloat JavaMethod< jfloat >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallFloatMethodV( instance, mID, arguments );
}

template<>
inline jdouble JavaMethod< jdouble >::callv( JNIEnv* env, jobject instance, va_list arguments )
{
	return env->CallDoubleMethodV( instance, mID, arguments );
}

// --------------------------------------------------------------------------
// class JavaBase
// --------------------------------------------------------------------------

class JavaBase
{
protected:

	JavaBase();
	virtual ~JavaBase();

	void InitJava( JNIEnv* env, JavaClass& javaClass, const char* javaClassName );
	virtual void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
	virtual void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );
	void ConstructJavaObject( JNIEnv* env, const JavaClass& javaClass, const JavaMethodBase& ctor, va_list args );
	void AttachJavaObject( JNIEnv* env, jobject javaObject );

	jobject mJavaObject;
};

// --------------------------------------------------------------------------
// template class JavaBound
// --------------------------------------------------------------------------

template< typename Client >
class JavaBound : public JavaBase
{
	typedef JavaBase super;
	static JavaClass sJavaClass;
	static JavaMethod< void > sJavaCtor;

protected:

	void AttachJava( JNIEnv* env, const char* javaClassName, jobject localObjectRef )
	{
		InitJava( env, sJavaClass, javaClassName );
		AttachJavaObject( env, localObjectRef );
	}

	void ConstructJava( JNIEnv* env, const char* javaClassName, const char* ctorSignature, ... )
	{
		InitJava( env, sJavaClass, javaClassName );
		if ( sJavaClass.valid() )
		{
			if ( ! sJavaCtor.valid() )
			{
				sJavaCtor.init( env, sJavaClass, "<init>", ctorSignature );
			}
			if ( sJavaCtor.valid() )
			{
				va_list args;
				va_start( args, ctorSignature );
				ConstructJavaObject( env, sJavaClass, sJavaCtor, args );
				va_end( args );
			}
		}
	}
};

template< typename Client >
JavaClass JavaBound< Client >::sJavaClass;

template< typename Client >
JavaMethod< void > JavaBound< Client >::sJavaCtor;
