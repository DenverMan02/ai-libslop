#ifndef _ANDROIDSOUNDMANAGER_H_
#define _ANDROIDSOUNDMANAGER_H_

#include <drivers/audio/raw/RawAudioSoundManager.h>

#define MAX_SOURCE_SOUNDS	4096
#define MAX_CHANNELS		32
#define MAX_NUM_VOLUMES		16



namespace Sexy
{

class AndroidSoundManager : public RawAudioSoundManager
{
private:


//	double                       mMasterVolume[ MAX_NUM_VOLUMES ];

	bool                         mbEnabled;

	// time between the start of the buffer and now when we flush a chunk to the audio device
	uint32 mAudioTrackFetchSizeFrames;

public:

	AndroidSoundManager();
	virtual ~AndroidSoundManager();

	virtual void            Enable();
	virtual void 			Disable();

	virtual bool			LoadSound( unsigned int InSfxID, std::string const& InFilename );
	virtual void			Update( uint64 nowTimeUS );
	virtual void			Flush();

	// Called from Java land to feed the hungry audio beast
	int FetchAudioData( byte *__restrict__ pDestBuffer, int InNumFramesToRead );
	int SkipAudioData( int InNumFramesToSkip );

private:
	bool LoadWAVSound(unsigned int InSfxID, std::string const& InFilename);
	bool LoadOGGSound(unsigned int InSfxID, std::string const& InFilename);

};


} // namespace Sexy

#endif // _ANDROIDSOUNDMANAGER_H_

