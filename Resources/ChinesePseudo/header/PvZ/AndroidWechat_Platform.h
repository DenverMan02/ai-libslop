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
#include "IWechat_Platform.h"
#include "LawnAppEnums.h"

class AndroidWechatPlatform : public IWechatPlatform, public JavaBound< AndroidWechatPlatform > {
public:
	enum ShareResultCode {
		SHARE_RESULT_SUCCESS = 0,
		SHARE_RESULT_FAILED,
		SHARE_RESULT_CANCELED
	};

	AndroidWechatPlatform();
	virtual ~AndroidWechatPlatform();

	// Initialize sdk or some configure
	virtual void Initialize();

	static void ExitGameHook( JNIEnv* env, jobject javaObject, jlong nativeObject );

	virtual void DoShare(const std::string& i_url, bool toTimeLine);

	static void ShareHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode );

	virtual bool IsWeChatInstalled();

private:
	virtual void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
	virtual void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );

	static JavaMethod<void>	JavaInitializeSDK;
	static JavaMethod<void>	JavaDoShare;
	static JavaMethod<jboolean> JavaIsWechatInstalled;

	static std::map<PlatformType, std::string> AndroidWechatAPPIDS;
};

#endif /* WECHATPLATFORM_H_ */
