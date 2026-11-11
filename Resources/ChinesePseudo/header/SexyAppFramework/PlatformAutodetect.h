#ifndef PLATFORMAUTODETECT_H_INCLUDED
#define PLATFORMAUTODETECT_H_INCLUDED

namespace Sexy
{
	enum PLATFORM
	{
		PLATFORM_WINDOWS,
		PLATFORM_MACOSX,
		PLATFORM_IPHONE,
		PLATFORM_IPAD,
		PLATFORM_XBOX360,
		PLATFORM_PS3,
		PLATFORM_WII,
		PLATFORM_ANDROID,
		PLATFORM_AIRPLAY,
		PLATFORM_VITA,
		PLATFORM_WINRTDESKTOP,
		PLATFORM_WINRTPHONE,
		PLATFORM_EMSCRIPTEN,
		PLATFORM_METROWIN8
	};
}

#undef HOST_PLATFORM

//first check if a host was explicitly set
#if defined HOST_WINDOWS
#define HOST_PLATFORM PLATFORM_WINDOWS
#elif defined HOST_MACOSX
#define HOST_PLATFORM PLATFORM_MACOSX
#elif defined HOST_IPHONEOS
#define HOST_PLATFORM PLATFORM_IPHONE
#elif defined HOST_XBOX360
#define HOST_PLATFORM PLATFORM_XBOX360
#elif defined HOST_PS3
#define HOST_PLATFORM PLATFORM_PS3
#elif defined HOST_WII
#define HOST_PLATFORM PLATFORM_WII
#elif defined HOST_AIRPLAY
#define HOST_PLATFORM PLATFORM_AIRPLAY
#elif defined HOST_VITA
#define HOST_PLATFORM PLATFORM_VITA
#elif defined HOST_ANDROID
#define HOST_PLATFORM PLATFORM_ANDROID
#elif defined HOST_METROWIN8
#define HOST_PLATFORM PLATFORM_METROWIN8
#elif defined HOST_WINRTDESKTOP
#define HOST_PLATFORM PLATFORM_WINRTDESKTOP
#elif defined HOST_WINRTPHONE
#define HOST_PLATFORM PLATFORM_WINRTPHONE
#elif defined HOST_EMSCRIPTEN
#define HOST_PLATFORM PLATFORM_EMSCRIPTEN
#endif

#ifndef HOST_PLATFORM

#if defined __METROWIN8__
	#define HOST_METROWIN8
	#define HOST_PLATFORM PLATFORM_METROWIN8
#elif defined __WINRTDESKTOP__     // Win32 can mean winRTdesktop, winRTphone, windows or xbox (assuming 360 only for now)
	#define HOST_WINRTDESKTOP
	#define HOST_PLATFORM PLATFORM_WINRTDESKTOP
#elif defined __WINRTPHONE__
	#define HOST_WINRTPHONE
	#define HOST_PLATFORM PLATFORM_WINRTPHONE
#elif defined _WIN32
    //win32 can mean windows or xbox (assuming 360 only for now)
	#ifdef _XBOX_VER
		#define HOST_XBOX360
		#define HOST_PLATFORM PLATFORM_XBOX360
	#else
		#define HOST_WINDOWS
		#define HOST_PLATFORM PLATFORM_WINDOWS
	#endif

#elif defined __APPLE__
#include "TargetConditionals.h"
#if (TARGET_OS_IPHONE)
#define HOST_IPHONEOS
#define HOST_PLATFORM PLATFORM_IPHONEOS
#else
#define HOST_MACOSX
#define HOST_PLATFORM PLATFORM_MACOSX
#endif


#elif defined RVL_OS
#define HOST_WII
#define HOST_PLATFORM PLATFORM_WII

#elif defined SN_TARGET_PS3

#define HOST_PS3
#define HOST_PLATFORM PLATFORM_PS3

#elif defined __psp2__
#define HOST_VITA
#define HOST_PLATFORM PLATFORM_VITA

#elif defined ANDROID
#define HOST_ANDROID
#define HOST_PLATFORM PLATFORM_ANDROID

#elif defined EMSCRIPTEN
#define HOST_EMSCRIPTEN
#define HOST_PLATFORM PLATFORM_EMSCRIPTEN
#endif



#endif


// Now that we know a host platform has been set, set the SEXY_IS_PLATFORM_* macros (e.g. SEXY_IS_PLATFORM_WINDOWS) to either 0 or 1

// start for setting all platforms to 0, then we'll selectively turn on whichever platform is current.
#define SEXY_IS_PLATFORM_WINDOWS 0
#define SEXY_IS_PLATFORM_MACOSX 0
#define SEXY_IS_PLATFORM_IOS 0
#define SEXY_IS_PLATFORM_XBOX360 0
#define SEXY_IS_PLATFORM_PS3 0
#define SEXY_IS_PLATFORM_WII 0
#define SEXY_IS_PLATFORM_AIRPLAY 0
#define SEXY_IS_PLATFORM_VITA 0
#define SEXY_IS_PLATFORM_ANDROID 0
#define SEXY_IS_PLATFORM_METROWIN8 0
#define SEXY_IS_PLATFORM_WINRTDESKTOP 0
#define SEXY_IS_PLATFORM_WINRTPHONE 0
#define SEXY_IS_PLATFORM_EMSCRIPTEN 0

#if defined HOST_WINDOWS
#	undef SEXY_IS_PLATFORM_WINDOWS
#	define SEXY_IS_PLATFORM_WINDOWS 1
#	define SEXY_PLATFORM_NAME "Windows"
#	define SEXY_PLATFORM_SHORTNAME "win32"
#elif defined HOST_MACOSX
#	undef SEXY_IS_PLATFORM_MACOSX
#	define SEXY_IS_PLATFORM_MACOSX 1
#	define SEXY_PLATFORM_NAME "Mac OSX"
#	define SEXY_PLATFORM_SHORTNAME "osx"
#elif defined(HOST_IPHONEOS) || defined(HOST_IOS)
#	undef SEXY_IS_PLATFORM_IOS
#	define SEXY_IS_PLATFORM_IOS 1
#	define SEXY_PLATFORM_NAME "iOS"
#	define SEXY_PLATFORM_SHORTNAME "ios"
#elif defined HOST_XBOX360
#	undef SEXY_IS_PLATFORM_XBOX360
#	define SEXY_IS_PLATFORM_XBOX360 1
#	define SEXY_PLATFORM_NAME "XBox 360"
#	define SEXY_PLATFORM_SHORTNAME "xbox360"
#elif defined HOST_PS3
#	undef SEXY_IS_PLATFORM_PS3
#	define SEXY_IS_PLATFORM_PS3 1
#	define SEXY_PLATFORM_NAME "PlayStation3"
#	define SEXY_PLATFORM_SHORTNAME "ps3"
#elif defined HOST_WII
#	undef SEXY_IS_PLATFORM_WII
#	define SEXY_IS_PLATFORM_WII 1
#	define SEXY_PLATFORM_NAME "Wii"
#	define SEXY_PLATFORM_SHORTNAME "wii"
#elif defined HOST_AIRPLAY
#	undef SEXY_IS_PLATFORM_AIRPLAY
#	define SEXY_IS_PLATFORM_AIRPLAY 1
#	define SEXY_PLATFORM_NAME "Airplay"
#	define SEXY_PLATFORM_SHORTNAME "airplay"
#elif defined HOST_VITA
#	undef SEXY_IS_PLATFORM_VITA
#	define SEXY_IS_PLATFORM_VITA 1
#	define SEXY_PLATFORM_NAME "PlayStation Portable 2"
#	define SEXY_PLATFORM_SHORTNAME "psp2"
#elif defined HOST_ANDROID
#	undef SEXY_IS_PLATFORM_ANDROID
#	define SEXY_IS_PLATFORM_ANDROID 1
#	define SEXY_PLATFORM_NAME "Android"
#	define SEXY_PLATFORM_SHORTNAME "android"
#elif defined HOST_METROWIN8
#	undef SEXY_IS_PLATFORM_METROWIN8
#	define SEXY_IS_PLATFORM_METROWIN8 1
#	define SEXY_PLATFORM_NAME "MetroWin8"
#	define SEXY_PLATFORM_SHORTNAME "Win8"
#elif defined HOST_WINRTDESKTOP
#	undef SEXY_IS_PLATFORM_WINRTDESKTOP
#	define SEXY_IS_PLATFORM_WINRTDESKTOP 1
#	define SEXY_PLATFORM_NAME "Windows 8 Desktop"
#	define SEXY_PLATFORM_SHORTNAME "winrtdesktop"
#elif defined HOST_WINRTPHONE
#	undef SEXY_IS_PLATFORM_WINRTPHONE
#	define SEXY_IS_PLATFORM_WINRTPHONE 1
#	define SEXY_PLATFORM_NAME "Windows 8 Phone"
#	define SEXY_PLATFORM_SHORTNAME "winrtphone"
#elif defined HOST_EMSCRIPTEN
#	undef SEXY_IS_PLATFORM_EM
#	define SEXY_IS_PLATFORM_EM 1
#	define SEXY_PLATFORM_NAME "Emscripten HTML5"
#	define SEXY_PLATFORM_SHORTNAME "em"
#endif


#if SEXY_IS_PLATFORM_XBOX360
#include "drivers/misc/xbox360/Platform.h"
#elif SEXY_IS_PLATFORM_WINDOWS
#include "drivers/misc/windows/Platform.h"
#elif SEXY_IS_PLATFORM_MACOSX
#include "drivers/misc/macosx/Platform.h"
#elif SEXY_IS_PLATFORM_IOS
#include "drivers/misc/iphoneos/Platform.h"
#elif SEXY_IS_PLATFORM_AIRPLAY
#include "drivers/misc/airplay/Platform.h"
#elif SEXY_IS_PLATFORM_WII
#include "drivers/misc/wii/Platform.h"
#elif SEXY_IS_PLATFORM_PS3
#include "drivers/misc/ps3/Platform.h"
#elif SEXY_IS_PLATFORM_VITA
#include "drivers/misc/vita/Platform.h"
#elif SEXY_IS_PLATFORM_ANDROID
#include "drivers/misc/android/Platform.h"
#elif SEXY_IS_PLATFORM_METROWIN8
#include "drivers/misc/metrowin8/Platform.h"
#elif SEXY_IS_PLATFORM_WINRTDESKTOP
#include "drivers/misc/winrt/desktop/Platform.h"
#elif SEXY_IS_PLATFORM_WINRTPHONE
#include "drivers/misc/winrt/phone/Platform.h"
#elif defined HOST_EMSCRIPTEN
#include "drivers/misc/em/Platform.h"
#endif


#endif

