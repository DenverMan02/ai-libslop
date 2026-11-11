//
//  ICameraPreview.h
//  SexyAppFramework Prime
//
//  Created by Jason Weiler on 5/2/13.
//
//

#ifndef _ICameraPreview_h_
#define _ICameraPreview_h_

#include "Rect.h"

namespace Sexy
{
    
    class ICameraPreview
    {
    public:
        virtual ~ICameraPreview() {}
        
        virtual void Update() = 0;
        virtual void Resize( Rect const & newRect ) = 0;
        
        virtual bool ShowPreview( Rect const & newRect ) = 0;
        virtual bool HidePreview() = 0;
        
    };
    
} // namespace Sexy

#endif
