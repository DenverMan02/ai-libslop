//
//  PlatformInterface.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 6/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlatformInterface_h
#define PlantsVersusZombies2_PlatformInterface_h

#ifdef HOST_IPHONEOS
#include "drivers/app/iphoneos/ObjcInterface.h"
#include "SexyAppFramework/drivers/app/iPhoneOS/iPhoneOSAppDriver.h"
#endif

#ifdef HOST_ANDROID
#include "drivers/app/android/JavaInterface.h"
#include <drivers/app/android/AndroidAppDriver.h>
#endif

#include "Precompile.h"

namespace UserPrefs
{
	void				SetString(const std::string &i_key, std::string i_value);
	const std::string	GetString(const std::string& i_key, std::string i_defaultValue = "");
	const std::string	GetStringEx(const std::string& i_key, std::string i_defaultValue = "");
	bool              	GetBool(const std::string& i_key, bool defaultValue = false);
	int					GetInt(const std::string& i_key, int defaultValue = 0);
	void				SetInt(const std::string& i_key, int i_value);
	void				SetBool(const std::string& i_key, bool i_value);
	
	void				Synchronize();
	//PVZ2_CHINESE_BEGIN
	std::string GetDeviceType();
	//PVZ2_CHINESE_END
};

namespace CrashTracking
{
	// these four functions will set "variables" that will show up in crash logs
	void				SetString(const std::string& i_key, const std::string& i_value);
	void				SetBool(const std::string& i_key, const bool i_value);
	void				SetInt(const std::string& i_key, const int i_value);
	void				SetFloat(const std::string& i_key, const float i_value);

	// this spits a log format (as many times as is called) in crash logs
	void				Log(const std::string& i_log);
}

// C implementation of crash tracking (for swrve).
extern "C"
{
	// these four functions will set "variables" that will show up in crash logs
	void				CrashlyticsSetString(const char* i_key, const char* i_value);
	void				CrashlyticsSetBool(const char* i_key, const bool i_value);
	void				CrashlyticsSetInt(const char* i_key, const int i_value);
	void				CrashlyticsSetFloat(const char* i_key, const float i_value);

	// this spits a log format (as many times as is called) in crash logs
	void				CrashlyticsLog(const char* i_log);
}

#ifdef HOST_MACOSX
namespace UserPrefs
{
	inline void SetString(const std::string &i_key, std::string i_value)
	{
	}

	inline const std::string GetString(const std::string &i_key, std::string i_defaultValue)
	{
		return "";
	}

	inline bool GetBool(const std::string &i_key, bool i_defaultValue)
	{
		return false;
	}

	inline void SetBool(const std::string& i_key, bool i_value)
	{
	}

	inline int	GetInt(const std::string &i_key, int i_defaultValue)
	{
		return 0;
	}
    
    inline int SetInt(const std::string &i_key, int i_value)
    {
    }

	inline void Synchronize()
	{
	}
}
#endif
#endif
