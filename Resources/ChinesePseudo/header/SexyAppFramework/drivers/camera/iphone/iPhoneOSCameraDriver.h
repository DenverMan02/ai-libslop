//
//  iPhoneOSCameraDriver.h
//  SexyAppFramework Prime
//
//  Created by Jason Weiler on 5/1/13.
//
//

#ifndef _iPhoneOSCameraDriver_H_
#define _iPhoneOSCameraDriver_H_

#include "ICameraDriver.h"

namespace Sexy
{
	
    class SexyAppBase;
    class ICameraPreview;
	
    class iPhoneOSCameraDriver : public ICameraDriver
    {
    public:
        iPhoneOSCameraDriver( SexyAppBase * pAppBase );
        
        virtual bool StartupCaptureManager() override;
        virtual void ShutdownCaptureManager() override;
        
        virtual bool TakeCameraPicture( ImageReceivedDelegate gotImageCB ) override;
        
        virtual unsigned int GetNumCameras( ECameraPlacement placement = eCP_Unknown ) const override;
        
        virtual ICameraPreview * CreateCameraPreview() override;
        virtual void DestroyCameraPreview( ICameraPreview * mPreview ) override;
        
        
        SexyAppBase * GetApp() const { return mAppBase; }
        
    private:
        class SexyAppBase * mAppBase;
        int mRefCount;
    };
    
} // namespace Sexy


#endif // _iPhoneOSCameraDriver_H_
