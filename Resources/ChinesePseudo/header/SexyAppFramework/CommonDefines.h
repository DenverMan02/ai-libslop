#ifndef __SEXYAPPFRAMEWORK_COMMONDEFINES_H__
#define __SEXYAPPFRAMEWORK_COMMONDEFINES_H__

//--------------------------------------------------------------------------
// Feature Flags/macros
//--------------------------------------------------------------------------

//
// Reporting
//
// Available project defines: WANTS_REPORTING_DISABLED, WANTS_REPORTING_ENABLED
//

#ifdef SUPPORT_REPORTING
#	define IS_SUPPORT_REPORTING_DEFINED (1)
#else
#	define IS_SUPPORT_REPORTING_DEFINED (0)
#endif

#if (defined(WANTS_REPORTING_DISABLED) && defined(WANTS_REPORTING_ENABLED))
#	error "Both WANTS_REPORTING_DISABLED and WANTS_REPORTING_ENABLED are defined. Only one or neither should be defined."
#endif

#if defined(WANTS_REPORTING_ENABLED)
#	define SEXY_IS_REPORTING_ENABLED (1)
#	define PRIME_IS_REPORTING_ENABLED (IS_SUPPORT_REPORTING_DEFINED)
#elif defined(WANTS_REPORTING_DISABLED)
#	define SEXY_IS_REPORTING_ENABLED (0)
#	define PRIME_IS_REPORTING_ENABLED (0)
#else
#	define SEXY_IS_REPORTING_ENABLED (SEXY_IS_BUILD_DEBUG && IS_SUPPORT_REPORTING_DEFINED)
//TODO: Ensure this works
#	define PRIME_IS_REPORTING_ENABLED (!(defined RELEASEFINAL) && IS_SUPPORT_REPORTING_DEFINED )
#endif



//
// Assert
//
// Available project defines: WANTS_ASSERT_DISABLED, WANTS_ASSERT_ENABLED
//

#if (defined(WANTS_ASSERT_ENABLED) && defined(WANTS_ASSERT_DISABLED))
#	error "Both WANTS_ASSERT_ENABLED and WANTS_ASSERT_DISABLED are defined. Only one or neither should be defined."
#endif

// set to 0 to disable asserts/verifies only.
#if defined(WANTS_ASSERT_ENABLED)
#	define SEXY_IS_ASSERT_ENABLED (1)
#	define PRIME_IS_ASSERT_ENABLED (IS_SUPPORT_REPORTING_DEFINED)
#elif defined(WANTS_ASSERT_DISABLED)
#	define SEXY_IS_ASSERT_ENABLED (0)
#	define PRIME_IS_ASSERT_ENABLED (0)
#else
#	define SEXY_IS_ASSERT_ENABLED (SEXY_IS_BUILD_DEBUG)
//TODO: Ensure this works
#	define PRIME_IS_ASSERT_ENABLED (!(defined RELEASEFINAL) && IS_SUPPORT_REPORTING_DEFINED)
#endif

#ifdef PRIME_FOR_PVZ2
//Debug Draw
#if defined(WANTS_DEBUG_DRAW_ENABLED)
#	define DEBUG_DRAW_ENABLED (1)
#elif defined(WANTS_DEBUG_DRAW_DISABLED)
#	define DEBUG_DRAW_ENABLED (0)
#else
#	define DEBUG_DRAW_ENABLED (!(defined RELEASEFINAL))
#endif

//RSB Patching
#ifdef SUPPORT_RSB_PATCHING
#	define IS_SUPPORT_RSB_PATCHING_DEFINED (1)
#else
#	define IS_SUPPORT_RSB_PATCHING_DEFINED (0)
#endif

#if (defined(WANTS_RSB_PATCHING_DISABLED) && defined(WANTS_RSB_PATCHING_ENABLED))
#	error "Both WANTS_RSB_PATCHING_DISABLED and WANTS_RSB_PATCHING_ENABLED are defined. Only one or neither should be defined."
#endif

#if defined(WANTS_RSB_PATCHING_ENABLED)
#	define PRIME_IS_RSB_PATCHING_ENABLED (IS_SUPPORT_RSB_PATCHING_DEFINED)
#elif defined(WANTS_RSB_PATCHING_DISABLED)
#	define PRIME_IS_RSB_PATCHING_ENABLED (0)
#else
#	define PRIME_IS_RSB_PATCHING_ENABLED (0)
#endif
#endif // PRIME_FOR_PVZ2

//
// LiveLink
//
// Available project defines: WANTS_LIVELINK_ENABLED, WANTS_LIVELINK_DISABLED
//


#ifdef SUPPORT_LIVELINK
#	define IS_SUPPORT_LIVELINK_DEFINED (1)
#else 
#	define IS_SUPPORT_LIVELINK_DEFINED (0)
#endif

#if (defined(WANTS_LIVELINK_ENABLED) && defined(WANTS_LIVELINK_DISABLED))
#	error "Both WANTS_LIVELINK_ENABLED and WANTS_LIVELINK_DISABLED are defined. Only one or neither should be defined."
#endif

#if defined(WANTS_LIVELINK_ENABLED)
#	define SEXY_IS_LIVELINK_ENABLED (IS_SUPPORT_LIVELINK_DEFINED)
#elif defined(WANTS_LIVELINK_DISABLED)
#	define SEXY_IS_LIVELINK_ENABLED (0)
#else
#	define SEXY_IS_LIVELINK_ENABLED (IS_SUPPORT_LIVELINK_DEFINED && SEXY_IS_BUILD_DEBUG)
#endif


//
// ModVals
//
// Available project defines: WANTS_MODVALS_ENABLED, WANTS_MODVALS_DISABLED, WANTS_MODVALS_LEGACY_ENABLED, WANTS_MODVALS_LIVELINK_ENABLED
//


#if (defined(RELEASEFINAL) || defined(RELEASE_FINAL))
#	define IS_RELEASEFINAL_DEFINED (1)
#else
#	define IS_RELEASEFINAL_DEFINED (0)
#endif

#ifdef WANTS_MODVALS_LIVELINK_ENABLED
#	define IS_WANTS_MODVALS_LIVELINK_ENABLED_DEFINED (1)
#else
#	define IS_WANTS_MODVALS_LIVELINK_ENABLED_DEFINED (0)
#endif

#ifdef WANTS_MODVALS_LEGACY_ENABLED
#	define IS_WANTS_MODVALS_LEGACY_ENABLED_DEFINED (1)
#else
#	define IS_WANTS_MODVALS_LEGACY_ENABLED_DEFINED (0)
#endif

#if (defined(WANTS_MODVALS_ENABLED) && defined(WANTS_MODVALS_DISABLED))
#	error "Both WANTS_MODVALS_ENABLED and WANTS_MODVALS_DISABLED are defined. Only one or neither should be defined."
#endif

#if (IS_WANTS_MODVALS_LIVELINK_ENABLED_DEFINED && IS_WANTS_MODVALS_LEGACY_ENABLED_DEFINED)
#	error "Both WANTS_MODVALS_LIVELINK_ENABLED and WANTS_MODVALS_LEGACY_ENABLED are defined. Only one or neither should be defined."
#endif


#define SEXY_IS_MODVALS_LIVELINK_ENABLED ((IS_WANTS_MODVALS_LIVELINK_ENABLED_DEFINED && SEXY_IS_LIVELINK_ENABLED))
// Default the legacy modvals unless livelink modvals have been enabled
#define SEXY_IS_MODVALS_LEGACY_ENABLED (!SEXY_IS_MODVALS_LIVELINK_ENABLED)

// Some sanity checking. One and only one LiveLink or Legacy modvals must be enabled. It is not valid for neither or both to be enabled.
#if (SEXY_IS_MODVALS_LIVELINK_ENABLED && SEXY_IS_MODVALS_LEGACY_ENABLED )
#	error "Both LiveLink modvals and legacy modvals are enabled, this should not be possible. Either one of the other should be enabled, even if ModVals in general are disabled."
#elif (!SEXY_IS_MODVALS_LIVELINK_ENABLED && !SEXY_IS_MODVALS_LEGACY_ENABLED)
#	error "Both LiveLink modvals and legacy modvals are disabled, this should not be possible. Either one of the other should be enabled, even if ModVals in general are disabled."
#endif


#if defined(WANTS_MODVALS_DISABLED)
#	define SEXY_IS_MODVALS_ENABLED (0)
#elif defined(WANTS_MODVALS_ENABLED)
#	define SEXY_IS_MODVALS_ENABLED (1)
#else
#	define SEXY_IS_MODVALS_ENABLED (!IS_RELEASEFINAL_DEFINED)
#endif

// Patchup: force modvals to be disabled if we are supposed to be using 
// legacy modvals, but legacy modvals are not supported on the current platform
#if (SEXY_IS_MODVALS_ENABLED && SEXY_IS_MODVALS_LEGACY_ENABLED && defined(SEXY_DISABLE_MODVAL_LEGACY))
#	undef SEXY_IS_MODVALS_ENABLED 
#	define SEXY_IS_MODVALS_ENABLED (0)
#endif


//
// Wwise Interactive Audio
//
// Available project define: c
// Only allow this to be defined if it's wanted and Wwise is supported
//

#ifdef SUPPORT_WWISE
#	define IS_SUPPORT_WWISE_DEFINED (1)
#else 
#	define IS_SUPPORT_WWISE_DEFINED (0)
#endif

#if defined(WANTS_WWISE_ENABLED)
#	define SEXY_IS_WWISE_ENABLED (IS_SUPPORT_WWISE_DEFINED)
#else
#	define SEXY_IS_WWISE_ENABLED (0)
#endif

#if (defined(WANTS_WWISE_COMM_ENABLED) && defined(WANTS_WWISE_COMM_DISABLED))
#	error "Both WANTS_WWISE_COMM_ENABLED and WANTS_WWISE_COMM_DISABLED are defined. Only one or neither should be defined."
#endif

// Wwise communication with the authoring tool is never supported on Windows release builds
#ifdef HOST_WINDOWS
#	define IS_SUPPORT_WWISE_COMM_RELEASE (0)
#else 
#	define IS_SUPPORT_WWISE_COMM_RELEASE (1)
#endif

#if defined(WANTS_WWISE_COMM_ENABLED)
#	define SEXY_IS_WWISE_COMM_ENABLED (SEXY_IS_BUILD_DEBUG || IS_SUPPORT_WWISE_COMM_RELEASE)
#elif defined(WANTS_WWISE_COMM_DISABLED)
#	define SEXY_IS_WWISE_COMM_ENABLED (0)
#else
#	define SEXY_IS_WWISE_COMM_ENABLED (SEXY_IS_BUILD_DEBUG)
#endif

//
// Device Cameras
//
// Android and iOS devices can use the buit-in cameras
//

#if defined( SUPPORT_CAMERA )
#  define IS_SUPPORT_CAMERA_DEFINED (1)
#else
#  define IS_SUPPORT_CAMERA_DEFINED (0)
#endif

#if defined(WANTS_CAMERA_ENABLED)
#	define SEXY_IS_CAMERA_ENABLED (IS_SUPPORT_CAMERA_DEFINED)
#else
#	define SEXY_IS_CAMERA_ENABLED (0)
#endif

//PVZ2_CHINESE_BEGIN
//
// integrate WeChat of QQ
//
//

#if defined( SUPPORT_WECHAT )
#  define IS_SUPPORT_WECHAT_DEFINED (1)
#else
#  define IS_SUPPORT_WECHAT_DEFINED (0)
#endif

#if defined(WANTS_WECHAT_ENABLED)
#	define SEXY_IS_WECHAT_ENABLED (IS_SUPPORT_WECHAT_DEFINED)
#else
#	define SEXY_IS_WECHAT_ENABLED (0)
#endif

//
//
// define macro to support screen stretch or not
//

#if defined( SUPPORT_SCREEN_STRETCH )
#  define IS_SUPPORT_SCREEN_STRETCH (1)
#else
#  define IS_SUPPORT_SCREEN_STRETCH (0)
#endif

#if defined(WANTS_SCREEN_STRETCH_ENABLED)
#	define SEXY_IS_SCREEN_STRETCH_ENABLED (IS_SUPPORT_SCREEN_STRETCH)
#else
#	define SEXY_IS_SCREEN_STRETCH_ENABLED (0)
#endif

//
//
// define macro to support screen scale or not
//

#if defined( SUPPORT_SCREEN_SCALE )
#  define IS_SUPPORT_SCREEN_SCALE (1)
#else
#  define IS_SUPPORT_SCREEN_SCALE (0)
#endif

#if defined(WANTS_SCREEN_SCALE_ENABLED)
#	define SEXY_IS_SCREEN_SCALE_ENABLED (IS_SUPPORT_SCREEN_SCALE)
#else
#	define SEXY_IS_SCREEN_SCALE_ENABLED (0)
#endif

//PVZ2_CHINESE_END



//
// Compact Vertex Format
//
// Available project defines: WANTS_COMPACT_VERTEX_FORMAT_DISABLED
//

#ifdef WANTS_COMPACT_VERTEX_FORMAT_DISABLED
#	define IS_COMPACT_VERTEX_FORMAT (0)
#else
#	define IS_COMPACT_VERTEX_FORMAT (1)
#endif


//--------------------------------------------------------------------------

#endif // __SEXYAPPFRAMEWORK_COMMONDEFINES_H__

//-----------------------------------EOF!-----------------------------------
