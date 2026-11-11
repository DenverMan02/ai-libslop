//
//  WwiseSoundManager.h
//  SexyAppFramework Prime
//


#ifndef SexyAppFramework_Prime_WwiseSoundManager_h
#define SexyAppFramework_Prime_WwiseSoundManager_h


#if SEXY_IS_WWISE_ENABLED

#include "InteractiveSoundManager.h"

namespace Sexy
{

struct WwiseSoundManagerConfig : public InteractiveSoundManagerConfig
{
	WwiseSoundManagerConfig();

#if defined(HOST_IPHONEOS)
    std::map<std::string, std::string> mFileIdToPathMap;
#endif

#if defined(HOST_ANDROID)
    std::string mAssetFilePath;
#endif
};




class WwiseSoundManager : public InteractiveSoundManager
{
public:
	WwiseSoundManager ( IInteractiveAudioDriver * InDriver );

	virtual bool Initialize( InteractiveSoundManagerConfig const & config );
};

}; // namespace Sexy

#endif // SEXY_IS_WWISE_ENABLED

#endif
