#ifndef _WWISESOUNDBANK_H_INCLUDED_
#define _WWISESOUNDBANK_H_INCLUDED_

#include "common.h"

#if SEXY_IS_WWISE_ENABLED

#include "Soundbank.h"

namespace Sexy
{
    class WwiseSoundBank : public SoundBank
    {
    public:
		enum LoadMode 
		{
			LOAD_NONE,
			LOAD_FULL,
			LOAD_PARTIAL
		};
	
	public:
        RT_CLASS_DEFINE(WwiseSoundBank, SoundBank, ResourceClass) {}
        
        WwiseSoundBank();
        virtual ~WwiseSoundBank();
        
        // Load/prepare a sound bank.
        virtual bool        Load(const char* bankName) override;
		virtual bool		Prepare(const char* bankName) override;
        
        virtual bool        IsValidBank() override;
        virtual AudioBankId      GetBankId() override;
        virtual std::string GetBankName() override;
#if SEXY_IS_WWISE_ENABLED
        virtual void        SetBankError() override;
#endif
        
    protected:
        void destroy();
    protected:
		void * mBankDataBufferPtr;
        AudioBankId mBankId;
        std::string mBankName;
		LoadMode mMode;
    };
    
}

#endif // SEXY_IS_WWISE_ENABLED

#endif
