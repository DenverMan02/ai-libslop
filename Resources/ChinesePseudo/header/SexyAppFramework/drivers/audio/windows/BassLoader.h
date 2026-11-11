#ifndef __BASSLOADER_H__
#define __BASSLOADER_H__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#ifndef BASSDEF
	#define BASSDEF(f) (WINAPI *f)
#endif
#ifndef BASS_NAMESPACE
#define BASS_USE_NAMESPACE
#define BASS_NAMESPACE Bass
#endif
#include "drivers/audio/bass/bass.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
namespace Sexy
{

struct BASS_INSTANCE
{
	BASS_INSTANCE(const char *dllName);
	virtual ~BASS_INSTANCE();

    HMODULE         mModule;
};

extern BASS_INSTANCE *gBass;

void LoadBassDLL(); // exits on failure
void FreeBassDLL();

} // namespace Sexy

#endif
