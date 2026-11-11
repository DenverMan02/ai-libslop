#ifndef __BASSMUSICINTERFACE_H__
#define __BASSMUSICINTERFACE_H__

#include "MusicInterface.h"

#ifndef BASSEXTERN
#define BASSEXTERN extern
#endif
#ifndef BASS_NAMESPACE
#define BASS_USE_NAMESPACE
#define BASS_NAMESPACE Bass
#endif

#ifdef _DEBUG
#include <assert.h>
#define CHECKBASSCALL(xCall) \
	{ \
		if (!(xCall)) \
		{ \
			int aErrorCode = Bass::BASS_ErrorGetCode(); \
			OutputDebugStrF("BASS Error Code: %d\n", aErrorCode); \
			assert(false && "BASS Call failed"); \
		} \
	}
#else
#define CHECKBASSCALL(xCall) (void)xCall
#endif


#if defined HOST_WINDOWS
#include "../windows/BassLoader.h"
#elif defined HOST_MACOSX
#include "bass.h"
typedef void* HWND;
#else
#error BassMusicInterface on UNBEKNOWN HOST
#endif

using namespace Bass;

namespace Sexy
{

class SexyAppBase;

BOOL BASS_MusicPlay(HMUSIC handle);
BOOL BASS_MusicPlayEx(HMUSIC handle, DWORD pos, int flags, BOOL reset, QWORD theStartPos = 0);
BOOL BASS_ChannelResume(DWORD handle);
BOOL BASS_StreamPlay(HSTREAM handle, BOOL flush, DWORD flags);

DWORD BASS_MusicGetOrders(HMUSIC handle);
DWORD BASS_MusicGetOrderPosition(HMUSIC handle);

BOOL BASS_MusicSetAmplify(HMUSIC handle, DWORD value);
DWORD BASS_MusicGetAmplify(DWORD handle);
BOOL BASS_MusicSetBPM(DWORD handle, DWORD value);
DWORD BASS_MusicGetBPM(DWORD handle);
BOOL BASS_MusicSetPanSep(DWORD handle, DWORD value);
DWORD BASS_MusicGetPanSep(DWORD handle);
BOOL BASS_MusicSetPScaler(DWORD handle, DWORD value);
DWORD BASS_MusicGetPScaler(DWORD handle);
BOOL BASS_MusicSetSpeed(DWORD handle, DWORD value);
DWORD BASS_MusicGetSpeed(DWORD handle);
BOOL BASS_MusicSetGlobalVolume(DWORD handle, DWORD value);
DWORD BASS_MusicGetGlobalVolume(DWORD handle);

BOOL BASS_MusicSetChannelVolumeFloat(DWORD handle, DWORD channel, float value);
float BASS_MusicGetChannelVolumeFloat(DWORD handle, DWORD channel);
BOOL BASS_MusicSetChannelVolumeInt(DWORD handle, DWORD channel, int value);
int BASS_MusicGetChannelVolumeInt(DWORD handle, DWORD channel);

BOOL BASS_MusicSetInstrumentVolumeFloat(DWORD handle, DWORD inst, float value);
float BASS_MusicGetInstrumentVolumeFloat(DWORD handle, DWORD inst);
BOOL BASS_MusicSetInstrumentVolumeInt(DWORD handle, DWORD inst, int value);
int BASS_MusicGetInstrumentVolumeInt(DWORD handle, DWORD inst);

BOOL BASS_ChannelSetAttributes(DWORD handle, int freq, int volume, int pan);
BOOL BASS_ChannelGetAttributes(DWORD handle, DWORD* freq, DWORD* volume, int* pan);
BOOL BASS_ChannelSetPosition(DWORD handle, QWORD pos);
QWORD BASS_ChannelGetPosition(DWORD handle);
QWORD BASS_ChannelGetLength(DWORD handle);
	
class BassMusicInfo
{
public:
	HMUSIC					mHMusic;
	HSTREAM					mHStream;
	double					mVolume;
	double					mVolumeAdd;
	double					mVolumeCap;
	bool					mStopOnFade;

public:
	BassMusicInfo();

	DWORD GetHandle() { return mHMusic?mHMusic:mHStream; }
};

typedef std::map<int, BassMusicInfo> BassMusicMap;

class BassMusicInterface : public MusicInterface
{
public:	
	BassMusicMap			mMusicMap;
	int						mMaxMusicVolume;
	int						mMusicLoadFlags;

public:
	BassMusicInterface(HWND theHWnd);
	virtual ~BassMusicInterface();
	
	virtual bool			LoadMusic(int theSongId, const std::string& theFileName) override;
	virtual void			PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false, uint64 theStartPos=0) override;
	virtual void			StopMusic(int theSongId) override;
	virtual void			StopAllMusic() override;		
	virtual void			UnloadMusic(int theSongId) override;
	virtual void			UnloadAllMusic() override;
	virtual void			PauseAllMusic() override;
	virtual void			ResumeAllMusic() override;
	virtual void			PauseMusic(int theSongId) override;
	virtual void			ResumeMusic(int theSongId) override;	
	virtual void			FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false) override;
	virtual void			FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004) override;
	virtual void			FadeOutAll(bool stopSong = true, double theSpeed = 0.004) override;
	virtual void			SetSongVolume(int theSongId, double theVolume) override;
	virtual void			SetSongMaxVolume(int theSongId, double theMaxVolume) override;
	virtual bool			IsPlaying(int theSongId) override;

	virtual void			SetVolume(double theVolume) override;
	virtual void			SetMusicAmplify(int theSongId, double theAmp) override; // default is 0.50
	virtual void			Update() override;

	// functions for dealing with MODs
	int						GetMusicOrder(int theSongId);
};

}

#endif //__BASSMUSICINTERFACE_H__
