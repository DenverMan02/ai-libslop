
#pragma once

#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/Widget.h"
#include "todlib/TodCommon.h"

namespace Sexy
{
int ImgXOfs(int i_id);
int ImgYOfs(int i_id);
Sexy::Image* GetImageById(int i_id);
}

class ResUtil
{
public:
	static void ImgSync( Sexy::Widget* i_widget, int i_imgId )
	{
		Sexy::Image* img = Sexy::GetImageById( i_imgId );
		if ( !img )
			return;

		i_widget->mX = S(U_INV_S(Sexy::ImgXOfs( i_imgId )));
		i_widget->mY = S(U_INV_S(Sexy::ImgYOfs( i_imgId )));
		i_widget->mWidth = img->GetWidth();
		i_widget->mHeight = img->GetHeight();
	}

    static inline bool IsCoordContainedInImg( int i_x, int i_y, int imgId )
    {
        Sexy::Image* img = Sexy::GetImageById( imgId );
        uint32* bits = ((Sexy::MemoryImage*)img)->GetBits();
        int imgX = i_x - U_RS(Sexy::ImgXOfs( imgId ));
        int imgY = i_y - U_RS(Sexy::ImgYOfs( imgId ));

        if ( imgX >= 0 && imgX < img->GetWidth()
            && imgY >= 0 && imgY < img->GetHeight() )
        {
            auto rgba = bits[ imgY * img->GetWidth() + imgX ];
            if ( ( rgba & 0xff000000 ) > 0 )
            {
                return true;
            }
        }

        return false;
    }

	static Sexy::Point GetImgIdCenter( int i_imageId )
	{
        Sexy::Image* image = Sexy::GetImageById( i_imageId );
		return Sexy::Point( Sexy::ImgXOfs( i_imageId ) + image->GetWidth() / 2,
                     Sexy::ImgYOfs( i_imageId ) + image->GetHeight() / 2 );
	}
	
	static void DrawImageCenteredOnId( Sexy::Graphics* g, Sexy::Image* i_image, int i_centerOnImageId, float i_scaleX = 1.f, float i_scaleY = 1.f )
	{
        Sexy::Image* centerImage = Sexy::GetImageById( i_centerOnImageId );
		DrawImageCentered( g, i_image, (float)Sexy::ImgXOfs( i_centerOnImageId ) + (float)centerImage->GetWidth() / 2.f, (float)Sexy::ImgYOfs( i_centerOnImageId ) + (float)centerImage->GetHeight() / 2.f, i_scaleX, i_scaleY );
	}
};
