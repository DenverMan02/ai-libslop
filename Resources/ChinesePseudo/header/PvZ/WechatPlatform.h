/*
 * WechatPlatform.h
 *
 *  Created on: 2015-9-1
 *      Author: jianglc
 */

#ifndef WECHATPLATFORM_H_
#define WECHATPLATFORM_H_

#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"


class WechatPlatform : public JavaBound< WechatPlatform > {
public:
	enum ShareResultCode {
		SHARE_RESULT_SUCCESS = 0,
		SHARE_RESULT_FAILED,
		SHARE_RESULT_CANCELED
	};

	WechatPlatform();
	virtual ~WechatPlatform();

	// Initialize sdk or some configure
	virtual void Initialize();

	static void ExitGameHook( JNIEnv* env, jobject javaObject, jlong nativeObject );

	void DoShare();

	void ShareHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode );

private:
	virtual void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
	virtual void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );

	static JavaMethod<void>	JavaInitializeSDK;
	static JavaMethod<void>	JavaDoShare;
};

namespace Message
{
	void ShareComplete();
}


#endif /* WECHATPLATFORM_H_ */
