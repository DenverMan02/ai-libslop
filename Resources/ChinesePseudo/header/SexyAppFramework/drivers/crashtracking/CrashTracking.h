//
//  CrashTracking.h
//  SexyAppFramework Prime
//
//  Created by Austin McGee on 6/9/14.
//
//

#ifndef SexyAppFramework_Prime_CrashTracking_h
#define SexyAppFramework_Prime_CrashTracking_h

#include <string>

namespace CrashTracking
{
	// these four functions will set "variables" that will show up in crash logs
	void				SetString(const std::string& i_key, const std::string& i_value);
	void				SetBool(const std::string& i_key, const bool i_value);
	void				SetInt(const std::string& i_key, const int i_value);
	void				SetFloat(const std::string& i_key, const float i_value);

	// this spits a log format (as many times as is called) in crash logs
	void				Log(const std::string& i_log);
    
    // manually force a crash
    void                ForceCrash();
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
    
    // manually force a crash
    void                CrashlyticsForceCrash();
}

#ifdef HOST_MACOSX
namespace CrashTracking
{
	inline void SetString(const std::string& i_key, const std::string& i_value) {}
	inline void SetBool(const std::string& i_key, const bool i_value) {}
	inline void SetInt(const std::string& i_key, const int i_value) {}
	inline void SetFloat(const std::string& i_key, const float i_value) {}
	inline void Log(const std::string& i_log) {}
}
#endif

#endif
