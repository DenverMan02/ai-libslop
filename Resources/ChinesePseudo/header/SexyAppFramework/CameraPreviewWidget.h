//
//  CameraPreviewWidget.h
//  SexyAppFramework Prime
//
//  Created by Jason Weiler on 5/1/13.
//
//

#ifndef _CameraPreviewWidget_H_
#define _CameraPreviewWidget_H_

#include "KeyCodes.h"

#include "Widget.h"
#include "Rect.h"
#include "ICameraDriver.h"

namespace Sexy
{
    
    class Graphics;
    class Touch;
    class SexyAppBase;
	
    class CameraPreviewWidget : public Widget
    {
        enum ECPWDisplayMode
        {
            eCPW_StillImage
            , eCPW_LivePreview
        };
    public:
        CameraPreviewWidget( SexyAppBase * theApp, Widget * theParent );
        virtual ~CameraPreviewWidget();
        
        bool					TakePicture( ImageReceivedDelegate gotImageCB );
        
        void					ShowStillImage();
        void					ShowLivePreview();
        void                    StopLivePreview();
        void					SetStillImage( Image * theImage );

        // Widget Interface
        virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
        //virtual void            Resize(const Rect& i_rect) { Widget::Resize(i_rect); }
        virtual void			Draw(Graphics* g); // Already translated
        
        virtual void			Update();
        
    private:
        
        class SexyAppBase * mApp;
        class Widget * mParent;
        class ICameraPreview * mLivePreview;
        Image * mStillImage;
        ECPWDisplayMode mDisplayMode;
    };
    
} //namespace Sexy

#endif /* defined(__SexyAppFramework_Prime__CameraPreviewWidget__) */
