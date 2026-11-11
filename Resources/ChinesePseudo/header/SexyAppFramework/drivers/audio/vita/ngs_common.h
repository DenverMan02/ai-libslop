/* SCE CONFIDENTIAL
 PSP2 Programmer Tool Runtime Library Release 00.931.000
 *
 *      Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 */

/*
 * Title:  NGS common code
 * File: ngs_common.h
 * Description: include file for functionality common to NGS samples
 */


#ifndef _SCE_NGS_COMMON_H
#define _SCE_NGS_COMMON_H

#include <ngs.h>
#include <ngs/error.h>


#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus) */

/********************************************************************************************/

typedef struct SoundInfo {
	void *pData;
	int  nNumBytes;
	int	 nNumChannels;
	int  nSampleRate;
	int  nType;				// SCE_NGS_PLAYER_TYPE_ADPCM or SCE_NGS_PLAYER_TYPE_ADPCM or
							// for ATRAC9, this member holds the configData value
	double basePan;
	double baseVolume;
	int    deleteData; //only for oggs... which should be rare
	std::string filename; //for debugging

	SoundInfo()
	{
		pData = NULL;
		nNumBytes = 0;
		nNumChannels = 2;
		nSampleRate = 0;
		nType = SCE_NGS_PLAYER_TYPE_PCM;
		deleteData = 0;
		baseVolume = 1.0f;
		basePan = 0.0f;
	}

	void SetFormat(int rate, int channels, int bits)
	{
		nNumChannels = channels;
		nSampleRate  = rate;
		nNumBytes = nSampleRate * nNumChannels * bits/8;
	}

} SoundInfo;

int loadVAGFile( const char *strFileName, SoundInfo *pSound );
int loadWAVFile( const char *strFileName, SoundInfo *pSound );
int loadAT9File( const char *strFileName, SoundInfo *pSound );

/********************************************************************************************/

// Flags for audio output mode
#define NGS_NO_OUTPUT		(0x00)
#define NGS_SEND_TO_DEVICE	(0x01)
#define NGS_WRITE_TO_FILE	(0x02)


int prepareAudioOut( int nMode, int nBufferGranularity, int nSampleRate, const char *strFileName );
int writeAudioOut( const short *pBuffer );
void shutdownAudioOut( void );

/********************************************************************************************/


#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus) */

#endif /* _NGS_COMMON_H */
