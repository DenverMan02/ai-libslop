/*
 * AndroidAchievementDriverMgr.h
 *
 *  Created on: 2023-3-15
 *      Author: admin
 */

#ifndef ANDROIDACHIEVEMENTDRIVERMGR_H_
#define ANDROIDACHIEVEMENTDRIVERMGR_H_

#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"
#include "INewAchievementDriver.h"
//#include "LawnAppEnums.h"

class AndroidAchievementDriverMgr : public INewAchievementDriver, public JavaBound< AndroidAchievementDriverMgr >
{
public:

	AndroidAchievementDriverMgr();
	virtual ~AndroidAchievementDriverMgr();

	// Initialize sdk or some configure
	virtual void Initialize();

	void SetAchievement(const std::string& i_id, int i_type, double i_value, std::function<void(bool)> i_callback);

	static void SetAchievementCallback( JNIEnv* env, jobject javaObject, jint result );
	static void QueryAllAchievementCallback( JNIEnv* env, jobject javaObject, jint result );

	void QueryAllAchievement(std::function<void(std::vector<AchievementInfo>)> i_callback);

private:
	virtual void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
	virtual void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );

	static JavaMethod<void>	JavaInitialize;
	static JavaMethod<void>	JavaDoSetAchievement;
	static JavaMethod<void>	JavaDoQueryAllAchievement;

	static std::function<void(bool)> m_SetAchievementCallback;
	static std::function<void(std::vector<AchievementInfo>)> m_QueryAllAchievementCallback;
};


#endif /* ANDROIDACHIEVEMENTDRIVERMGR_H_ */
