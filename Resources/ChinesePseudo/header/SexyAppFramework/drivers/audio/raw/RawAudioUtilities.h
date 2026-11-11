
#ifndef _RAWAUDIOUTILITIES_H_
#define _RAWAUDIOUTILITIES_H_

namespace RawAudio
{

inline uint32 Util_TimeOffsetToFrameOffset( uint64 InTimeOffsetUS, uint64 InSampleRate )
{
	return (uint32)((InTimeOffsetUS * InSampleRate) / 1000000ULL);
}

inline uint64 Util_FrameOffsetToTimeOffset( uint64 InFrameOffset, uint64 InSampleRate ) 
{
	return (InFrameOffset * 1000000ULL) / InSampleRate;
}

}

#endif // _RAWAUDIOUTILITIES_H_

