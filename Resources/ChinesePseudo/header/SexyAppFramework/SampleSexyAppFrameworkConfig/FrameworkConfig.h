#ifndef __SEXYAPPFRAMEWORKCONFIG_FRAMEWORKCONFIG_H__
#define __SEXYAPPFRAMEWORKCONFIG_FRAMEWORKCONFIG_H__

//
// Below are various defines that can be uncommented to enable/disable different 
// features in the framework. Some of these defines are mutually exclusive.
//

//---------------------------------------------------------------------------------
// LiveLink
// 
// By default LiveLink will be enabled on platforms that support it in debug builds.
// It will be disabled on all other platforms and builds.
//

// If your platform supports live link you can use WANTS_LIVELINK_ENABLED to force 
// livelink to be enabled in builds other than Debug builds.

//#define WANTS_LIVELINK_ENABLED

// Use WANTS_LIVELINK_DISABLED to force live link to be disabled even in debug 
// builds.

//#define WANTS_LIVELINK_DISABLED

//---------------------------------------------------------------------------------
// ModVals
//

// There are two modval implementations. Legacy modvals work on windows and macosx.
// Currently this is the default system.
// The other modvals system uses LiveLink and works on windows, ios and macosx 
// currently. Use WANTS_MODVALS_LIVELINK_ENABLED to force the livelink modvals 
// system to be used.

//#define WANTS_MODVALS_LIVELINK_ENABLED
//#define WANTS_MODVALS_LEGACY_ENABLED

//
// Even if a modvals system (livelink/legacy) has been selected, modvals can still
// be enabled/disabled. Modvals are enabled by default in all builds except 
// RELEASEFINAL builds.
// You may use WANTS_MODVALS_DISABLED to disable modvals in other builds such as 
// debug or release builds. Or you could use WANTS_MODVALS_ENABLED to force modvals
// to be enabled (such as RELEASEFINAL! not recommended, but possible).
//

//#define WANTS_MODVALS_DISABLED
//#define WANTS_MODVALS_ENABLED

//---------------------------------------------------------------------------------
// Wwise
//

// By default the standard IAudioDriver interface is enabled.  This in turn uses the
// SoundManager, SoundInstance, and MusicInterface interfaces.
//

// If your platform supports Wwise you can use WANTS_WWISE_ENABLED to replace the standard
// IAudioDriver interface (as well as the SoundManager, SoundInstance, and MusicInterface
// interfaces) with a new IInteractiveAudioDriver interface, which provides access to Wwise
// interactive audio.  This will also enable the SoundBank interface.  Your app will need to
// link to the necessary Wwise libraries in order to build.

//#define WANTS_WWISE_ENABLED

// By default, communication with the Wwise Authoring tool is enabled in debug builds and disabled
// in release builds.  Use WANTS_WWISE_COMM_ENABLED to enable communication even in release builds,
// and WANTS_WWISE_COMM_DISABLED to disable communication even in debug builds.

//#define WANTS_WWISE_COMM_ENABLED
//#define WANTS_WWISE_COMM_DISABLED

// Note that whenever communicating with the Wwise Authoring tool, you must link to the
// CommunicationCentral library.  Also, it is necessary to link to the debug versions of all
// of the Wwise libraries.  Since this causes link issues when building Windows, communicating
// with the authoring tool is always disabled for Windows release builds, and the
// WANTS_WWISE_COMM_ENABLED flag will have no effect.

// Note
// For any game-specific modifications to prime, please ifdef the sections of applicable code with: PRIME_FOR_{GAME NAME}


//---------------------------------------------------------------------------------
// Bejeweled Blitz-specific settings for Prime
//

//#define PRIME_FOR_BEJBLITZ

#include "UserLocalConfig.h"

#endif // __SEXYAPPFRAMEWORKCONFIG_FRAMEWORKCONFIG_H__
