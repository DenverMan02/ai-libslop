/*
 * AndroidShareDriverMgr.h
 *
 *  Created on: 2022-8-9
 *      Author: admin
 */

#ifndef ANDROIDSHAREDRIVERMGR_H_
#define ANDROIDSHAREDRIVERMGR_H_

#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"
#include "IShareDriver.h"
//#include "LawnAppEnums.h"

class AndroidShareDriverMgr : public IShareDriver, public JavaBound< AndroidShareDriverMgr > {
public:

	AndroidShareDriverMgr();
	virtual ~AndroidShareDriverMgr();

	// Initialize sdk or some configure
	virtual void Initialize();

	virtual void Share(SharePlatform i_platform, ScreenInfo i_info);

	bool IsClientInstalled(SharePlatform i_platform);

	void SaveScreenImageToGallery(ScreenInfo i_info);

	void SaveScreenImageToLocal(ScreenInfo i_info);

	bool DeleteLocalImage(ScreenInfo i_info);

	static void ShareCallback( JNIEnv* env, jobject javaObject, jint result, jstring platform );
	static void SaveCallback( JNIEnv* env, jobject javaObject, jint result );

private:
	virtual void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
	virtual void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );

	static JavaMethod<void>	JavaInitialize;
	static JavaMethod<void>	JavaDoShare;
	static JavaMethod<jboolean>	JavaIsClientInstalled;
	static JavaMethod<void>	JavaSaveImageToGallery;
};


#endif /* ANDROIDSHAREDRIVERMGR_H_ */
