#pragma once

// Precompile.h
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#ifdef __cplusplus
#ifndef __PRECOMPILE_H__
#define __PRECOMPILE_H__

#pragma warning(disable: 4201) // warning C4201: nonstandard extension used : nameless struct/union -- mmsystem.h generates this
#pragma warning(disable: 4244) // warning C4244: '???' : conversion from '???' to '???', possible loss of data -- Common.h generates this
#pragma warning(disable: 4100) // warning C4100: '???' : unreferenced formal parameter
#pragma warning(disable: 4127) // warning C4127: conditional expression is constant
#pragma warning(disable: 4505) // warning C4505: '???' : unreferenced local function has been removed
#pragma warning(disable: 4996) // warning C4996: '???': The POSIX name for this item is deprecated. -- PerfTimer.h generates this

#pragma warning(disable: 4481) // warning C4481: nonstandard extension used: override specifier 'override' -- Lots of SexyAppFramework generates this

#ifdef RELEASEFINAL
#pragma warning(disable: 4702) // warning C4701: unreachable code
#endif

#define MAKEMUSICPOS(order,row) (0x80000000|MAKELONG(order,row))

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/Debug.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "SexyAppFramework/PerfTimer.h"
#include "SexyAppFramework/DialogButton.h"
#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/ImageFont.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/MTRand.h"
#include "SexyAppFramework/Dialog.h"
#include "SexyAppFramework/DeviceImage.h"
#include "SexyAppFramework/MusicInterface.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/CurvedVal.h"
#include "SexyAppFramework/SexyApp.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/IFileDriver.h"

// re-enable warnings that occur in standard headers
//#pragma warning(default: 4201)
#pragma warning(default: 4244)
//#pragma warning(default: 4996)

#include <math.h>


// People say that putting "using" in a header is bad, but this allows me to ignore namespaces which is what I want to do.
using namespace Sexy;

#include "TodLib/TodDebug.h"
#include "TodLib/DataArray.h"
#include "TodLib/TodCommon.h"

#include "ScaledApp.h"
#include "ConsoleApp.h"
#include "ConsoleListener.h"
#include "ResUtil.h"

#include "CommandConsole.h"

// Not sure where else to put this for now...Implemented in Utils.cpp
std::string GetFolder(Sexy::IFileDriver::PathType i_pathType);



// some nice res scaling utility funcs, only usable when Resources.h is included
#define IMG_PL_S(Img, xOfs, yOfs)	Img, U_RS(ImgXOfs(Img##_ID) + (xOfs)), U_RS(ImgYOfs(Img##_ID) + (yOfs))
#define IMG_PL_NS(Img, xOfs, yOfs)	Img, U_RS(ImgXOfs(Img##_ID)) + (xOfs), U_RS(ImgYOfs(Img##_ID)) + (yOfs)
#define IMG_S(Img)					IMGPL_S(Img, 0, 0)
#define IMG_RECT_S(Img, xOfs, yOfs)  Rect(U_RS(ImgXOfs(Img##_ID) + (xOfs)), U_RS(ImgYOfs(Img##_ID) + (yOfs)), (Img)->GetCelWidth(), (Img)->GetCelHeight())
#define IMG_RECT_NS(Img, xOfs, yOfs) Rect(U_RS(ImgXOfs(Img##_ID)) + (xOfs), U_RS(ImgYOfs(Img##_ID)) + (yOfs), (Img)->GetCelWidth(), (Img)->GetCelHeight())
#define IMG_SRCRECT(Img, frame)		Rect((Img)->GetCelWidth() * (frame % (Img)->m_numCols), (Img)->GetCelHeight() * (frame / (Img)->m_numCols), (Img)->GetCelWidth(), (Img)->GetCelHeight())
#define IMG_CXS(Img)				( S(ImgXOfs(Img##_ID)) + (Img)->GetCelWidth() / 2 )
#define IMG_CYS(Img)				( S(ImgYOfs(Img##_ID)) + (Img)->GetCelHeight() / 2 )

#if WANTS_ASSERT_ENABLED && defined(RELEASE)
#undef DBG_ASSERT
#undef DBG_ASSERT_MSG
#define DBG_ASSERT(exp)		{ PRIME_ASSERT(exp) }
#define DBG_ASSERT_MSG(...) { PRIME_ASSERTM(__VA_ARGS__)}
#endif

#ifndef NDEBUG
#define TWEAKABLE static
#else
#define TWEAKABLE const
#endif

#endif //__PRECOMPILE_H__
#endif
