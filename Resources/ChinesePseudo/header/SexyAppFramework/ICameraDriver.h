//
//  ICamera.h
//  SexyAppFramework Prime
//
//  Created by Jason Weiler on 4/30/13.
//
//

#ifndef _ICAMERA_H_
#define _ICAMERA_H_

#include "RtDelegate.h"
#include "MemoryImage.h"

namespace Sexy {
    
    enum ECameraPlacement
    {
        eCP_Unknown
        , eCP_FrontFacing
        , eCP_RearFacing
    };
    
    class ICameraPreview;
	
    typedef Delegate1<MemoryImage *> ImageReceivedDelegate;
	
    class ICameraDriver
    {
    public:
        static ICameraDriver* CreateCameraDriver( SexyAppBase * baseApp );
        
    public:
        
        virtual bool StartupCaptureManager() = 0;
        virtual void ShutdownCaptureManager() = 0;
        
        virtual unsigned int GetNumCameras( ECameraPlacement placement = eCP_Unknown ) const = 0;
        
        virtual ICameraPreview * CreateCameraPreview() { return NULL; }
        virtual void DestroyCameraPreview( ICameraPreview * mPreview ) {}
        
        virtual bool TakeCameraPicture( ImageReceivedDelegate gotImageCB ) = 0;
        
        //	virtual bool EnumerateCameraDevices();
        
    };

} // namespace Sexy



#endif
