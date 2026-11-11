//
//  iPhoneOSCameraPreview.h
//  SexyAppFramework Prime
//
//  Created by Jason Weiler on 5/2/13.
//
//

#ifndef _iPhoneOSCameraPreview_H_
#define _iPhoneOSCameraPreview_H_

#include "Rect.h"

#include "ICameraPreview.h"

namespace Sexy
{

class iPhoneOSCameraDriver;
	
class iPhoneOSCameraPreview : public ICameraPreview
{
public:
	iPhoneOSCameraPreview( iPhoneOSCameraDriver * theCameraDriver );
	virtual ~iPhoneOSCameraPreview();
	
	virtual void Update() override;

	virtual void Resize( Rect const & newRect ) override;
	
	virtual bool ShowPreview( Rect const & newRect ) override;
	virtual bool HidePreview() override;
	
private:
	iPhoneOSCameraDriver * mCameraDriver;
	Rect mAbsRect;			// For now, this does not transform
	bool mbPreviewHiddenWhileRotating;
};

} // namespace Sexy

#endif
