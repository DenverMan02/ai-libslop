/*
 * AndroidViewContainerMgr.h
 *
 *  Created on: 2018-9-26
 *      Author: Administrator
 */

#ifndef ANDROIDVIEWCONTAINERMGR_H_
#define ANDROIDVIEWCONTAINERMGR_H_

#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"
#include "IViewContainer.h"
#include "LawnAppEnums.h"

class AndroidViewContainerMgr : public IViewContainer, public JavaBound< AndroidViewContainerMgr > {
public:
	enum ShowResultCode {
		SHOW_RESULT_SUCCESS = 0,
		SHOW_RESULT_FAILED,
		SHOW_RESULT_CANCELED
	};

	AndroidViewContainerMgr();
	virtual ~AndroidViewContainerMgr();

	// Initialize sdk or some configure
	virtual void Initialize();

	virtual void ShowWebView(const std::string& i_url);

	virtual void PassCallSettlement(const std::string& i_key, int i_count);

	virtual void PassCallLottery(const std::string& i_key, int i_id, int i_quantity, int i_index);

	virtual void PassCallScoreStoreInfo(const std::string& i_key, const std::string& i_info);

	virtual void PassCallScoreStoreBuy(const std::string& i_key, int i_id);

	virtual void PassCallConsumeCash(const std::string& i_key, int i_num);

	virtual void PassCallAddPlayTimes(const std::string& i_key, int i_result);

	static void ShowViewHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jint resultCode );

	static void CallSettlementHook( JNIEnv* env, jobject javaObject, jstring key, jint accScore, jint houseIdx, jint tombStoneIdx );
	static void CallLotteryHook( JNIEnv* env, jobject javaObject, jstring key );
	static void CallScoreStoreInfoHook( JNIEnv* env, jobject javaObject, jstring key );
	static void CallScoreStoreBuyHook( JNIEnv* env, jobject javaObject, jstring key, jint id );
	static void CallConsumeCashHook( JNIEnv* env, jobject javaObject, jstring key, jint num, jint id );
	static void CallCloseWebViewHook( JNIEnv* env, jobject javaObject );
	static void CallOpenAdHook( JNIEnv* env, jobject javaObject );
	static void CallAddPlayTimesHook( JNIEnv* env, jobject javaObject, jstring key, jint num, jint id );

private:
	virtual void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
	virtual void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );

	static JavaMethod<void>	JavaInitialize;
	static JavaMethod<void>	JavaShowWebView;
	static JavaMethod<void>	JavaPassCallSettlement;
	static JavaMethod<void>	JavaPassCallLottery;
	static JavaMethod<void>	JavaPassCallScoreStoreInfo;
	static JavaMethod<void>	JavaPassCallScoreStoreBuy;
	static JavaMethod<void>	JavaPassCallConsumeCash;
	static JavaMethod<void>	JavaPassCallAddPlayTimes;
};


#endif /* ANDROIDVIEWCONTAINERMGR_H_ */
