/*
 *  CoreAudioMusicStream.h
 *  BookWorm
 *
 *  Created by Joseph Mobley on 9/17/08.
 *  Copyright 2008 PopCap Games, Inc. All rights reserved.
 *
 */

#pragma once
#include "CoreAudioSoundInstance.h"

namespace Sexy
{

	static const int kNumberBuffers = 3;
	
	class CoreAudioMusicStream
	{
	public:
		
		CoreAudioMusicStream( int songId );
		int id() { return mSongId; }
		
		bool Open( const std::string& path );
		void Prime( AudioQueueRef queue );
		void Close( AudioQueueRef queue );
		void Start( AudioQueueRef queue, bool loop );
		void Resume( AudioQueueRef queue );
		bool IsDone();
		const AudioStreamBasicDescription& Format();
		void FeedAudioQueue( AudioQueueRef inAQ, AudioQueueBufferRef inBuffer );
		void DisposeBuffers( AudioQueueRef queue );
		
	protected:

		void DeriveBufferSize( UInt32 maxPacketSize, Float64 seconds );
		void AllocateBuffers( AudioQueueRef queue );
		
		int							mSongId;
		AudioStreamBasicDescription	mFormat;
		UInt32						mMagicCookieSize;
		unsigned char*				mMagicCookie;
		
		AudioQueueBufferRef			mBuffers[kNumberBuffers];
		AudioQueueBufferRef         mPrimingBuffers[kNumberBuffers];
		AudioFileID					mAudioFile;
		UInt32						mBufferByteSize;
		SInt32						mNumPrimedPackets;
		SInt64						mCurrentPacket;
		UInt32						mNumPacketsToRead;
		UInt64						mPacketCount;
		SInt32						mPrimingFrames;
		SInt32						mRemainderFrames;
		bool						mIsDone;
		bool						mIsLooping;
		
	};

}
