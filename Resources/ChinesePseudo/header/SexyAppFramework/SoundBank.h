#pragma once
#ifndef SOUNDBANK_H_INCLUDED
#define SOUNDBANK_H_INCLUDED

#include "common.h"
#include "ResourceTypes.h"

#if SEXY_IS_WWISE_ENABLED

#include "ResourceManager.h"
#include "IInteractiveAudioDriver.h"
#include "RtObject.h"

namespace ResourceInfoTypes { class SoundBankRes; }

namespace Sexy
{
    class SoundBank : public BaseResource
    {
    public:
        RT_CLASS_DEFINE_ABSTRACT(SoundBank, BaseResource, ResourceClass)
		{
			StaticGetClass()->SetInfoClass(RTC(InfoClass));
		}

		typedef ResourceInfoTypes::SoundBankRes InfoClass;

		static SoundBank* Create();

		SoundBank() {}
        virtual ~SoundBank() {}
        
        // Load/prepare a sound bank.
		// If a sound bank is in a group that is loaded via ResourceGroup::Load,
		// its Load method is called, and the bank is marked as fully loaded.
		// If the bank is in a group that is not entirely loaded into memory,
		// but instead only has its file index loaded via ResourceGroup::LoadFileIndex,
		// then its Prepare method is called and the bank is marked as partially loaded.
		// Any event in a partially loaded bank must be prepared via a call to
		// IIinteractiveAudioDriver::PrepareEvent before it can be used.
        virtual bool        Load(const char* bankName) = 0;
		virtual bool		Prepare(const char* bankName) = 0;
        
        virtual bool        IsValidBank() = 0;
        virtual AudioBankId      GetBankId() = 0;
        virtual std::string GetBankName() = 0;
#if SEXY_IS_WWISE_ENABLED
        virtual void        SetBankError() = 0;
#endif
        
        // FIXME!AUDIO: Add methods to extract info from the sound bank:
        // - given a name/id of an audio file, extract the file name
        // - given a name/id of an event referencing external sources, extract the list of external source names.
        
    };
};

#else
namespace Sexy 
{ 
	class SoundBank : public BaseResource
    {
    public:
        RT_CLASS_DEFINE_ABSTRACT(SoundBank, BaseResource, ResourceClass) {}
	};
};
#endif // SEXY_IS_WWISE_ENABLED

#endif
