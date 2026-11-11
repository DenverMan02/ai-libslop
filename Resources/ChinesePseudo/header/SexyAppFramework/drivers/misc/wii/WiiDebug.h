#ifndef WIIDEBUG_H_INCLUDED
#define WIIDEBUG_H_INCLUDED

/*!
	Since some of the Wii debug tools can't be combined, I'll use this header to make sure 
	two mutually exclusive tools aren't enabled.
*/

//Comment this out to disable the Wii profiler support (uses some MEM2)
//#define WII_PROFILER_ENABLED
//#define WII_SCREENSHOT_ENABLED

//Give the profiler precedence
#if defined(WII_PROFILER_ENABLED)
#undef WII_SCREENSHOT_ENABLED
#endif

#endif
