#ifndef __COREAUDIOSOUNDUTILITY_H__
#define __COREAUDIOSOUNDUTILITY_H__

#include <AudioToolbox/AudioToolbox.h>
#include <string>

#define STATUSCALL(call) Sexy::StatusCheckedCall( (call), #call )
#define UNUSED(x) (void)x

namespace Sexy
{
	struct CoreAudioSoundBuffer
	{
		std::string fileName;
		AudioStreamBasicDescription format;
		AudioBufferList* buffer;
		double baseVolume;
		int basePan;
		bool ownsBuffer;
	
		CoreAudioSoundBuffer();
		void SetFormat( UInt32 rate, UInt32 channels, UInt32 bits );
		void AllocateWithPacketCount( UInt32 packetCount );
		void AllocateWithFrameCount( UInt32 frameCount );
		void AllocateWithByteCount( UInt32 byteCount );
		
		void SetResidentBuffer( uint8*, uint32);
		char* GetInterleavedDataPtr();
		size_t GetInterleavedDataSize();
		UInt32 GetPacketCount();
	};

	OSStatus StatusCheckedCall( OSStatus status, const char* call );
	AudioUnit CreateAudioUnit( const OSType& compType, const OSType& compSubType );
	void DestroyAudioUnit( AudioUnit unit );
	OSStatus ConnectAudioUnits( AudioUnit destUnit, UInt32 destInputNumber, AudioUnit srcUnit, UInt32 srcOutputNumber );
	OSStatus ConnectRender( AudioUnit destUnit, UInt32 destInputNumber, AURenderCallback renderProc, void* userData );
	UInt32 GetComponentVersion( const OSType& compType, const OSType& compSubType );
	void DebugPrintStreamFormats( const char* label, AudioUnit unit );
	AudioBufferList* NewAudioBufferList( UInt32 numBuffers );
	void DeleteAudioBufferList( AudioBufferList* bufferList );
	AudioBufferList* AllocateAudioBuffer( const AudioStreamBasicDescription& format, UInt32 byteCount );
	void DeallocateAudioBuffer( AudioBufferList* bufferList );
	void CopyAudioPackets( AudioBufferList* dest, UInt32 destPacket, AudioBufferList* source, UInt32 sourcePacket, UInt32 packetCount, UInt32 bytesPerPacket );
	void ReferenceAudioPackets( AudioBufferList* dest, AudioBufferList* source, UInt32 sourcePacket, UInt32 packetCount, UInt32 bytesPerPacket );
	void ClearAudioPackets( AudioBufferList* dest, UInt32 destPacket, UInt32 packetCount, UInt32 bytesPerPacket );

}

#endif //__COREAUDIOSOUNDUTILITY_H__
