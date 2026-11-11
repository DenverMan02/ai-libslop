//
//  WorldMapCamera.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 1/7/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMapCamera_h
#define PlantsVersusZombies2_WorldMapCamera_h

#include <cstddef>

#include "Point.h"
#include "Rect.h"
#include "SexyString.h"

class PopAnimRig;
namespace Sexy {
    class Graphics;
    class Image;
    class PrimeTypeface;
}  // namespace Sexy


class WorldMapCamera
{
    
public:
    
    WorldMapCamera(Sexy::Graphics* i_g)
    {
        // Scale is, by default 1.0f
        SetCameraScale(1.0f, 1.0f);
        
        SetGraphics(i_g);
        
        m_useClipViewport = false;
        m_viewport = Rect(0,0,1,1);
        
        /*
         m_cameraTransform.Identity();
         
         // By default, our camera points to the center of the viewport
         m_cameraCenter.mX = (float) viewportRect.mWidth / 2.0f;
         m_cameraCenter.mY = (float) viewportRect.mHeight / 2.0f;
         
         // Set the viewport (which will also build the view matrix and normalized
         // view matrices
         SetViewport(viewportRect);
         */
        
    };
    
    virtual ~WorldMapCamera()
    {
        
    };
    
    void						DrawImage(Sexy::Image* i_image, float i_posX, float i_posY, bool i_isMirrored = false, float i_width = -1.0f, float i_height = -1.0f);
    void						DrawImage(Sexy::Image* i_image, Sexy::Rect i_srcRect, Sexy::FRect i_destRect, bool i_isMirrored = false);
    void						DrawImageRotated(Sexy::Image* i_image, float i_posX, float i_posY, float i_rotationAngle, bool i_isMirrored = false, float i_width = -1.0f, float i_height = -1.0f);
    void						DrawImageRotated(Sexy::Image* i_image, Sexy::Rect i_srcRect, Sexy::FRect i_destRect, float i_rotationAngle, bool i_isMirrored = false);
    void						DrawRect(const Sexy::Rect& i_rect);
    void						DrawString(PrimeTypeface* font, const SexyString& i_text, int i_posX, int i_posY, int i_wrapWidth = 100000, int i_lineSpacing = -1, int i_justification = -1, int *i_maxWidth = NULL);
    void						DrawPopAnimRig(PopAnimRig* i_animRig, float i_posX, float i_posY, float i_scaleX = 1.0f, float i_scaleY = 1.0f, float i_rotation = 0.0f );
    void						DrawTexturedQuad(Sexy::Image* i_texture, Sexy::Point* i_vertexList, int i_numVertices);
    void						DrawLine(float i_startX, float i_startY, float i_endX, float i_endY);
    void						FillPoly(Sexy::Point* i_vertexList, int i_numVertices, bool i_isConvex = false);
    void						FillRect(const Sexy::Rect& i_rect);
    
    void						SetUseClipViewport(const bool i_useClipping);
    void						SetGraphics(Sexy::Graphics* i_g);
    void						SetCameraCenter(float i_centerX, float i_centerY);
    void						SetCameraScale(float i_scaleX, float i_scaleY);
    //	void						SetViewport(const Sexy::Rect& i_viewportRect);
    //	void						SetCameraTransform(const SimpleMatrix& i_cameraTransform);
    inline const Sexy::FPoint&	GetCameraScale() const;
    
    Sexy::FPoint				TransformPointToCamera(float i_X, float i_Y);
    Sexy::FPoint				TransformPointFromCamera(float i_X, float i_Y);
    
private:
    
    void						rebuildViewMatrices();
    
    Sexy::Graphics*				m_graphics;				// Pointer to the graphics object
    
    Sexy::FPoint				m_cameraScale;			// Camera scale
    Sexy::FPoint				m_cameraCenter;			// Center of camera on the screen
    Sexy::Rect					m_viewport;				// Viewport Info
    Sexy::Rect					m_clipViewportRect;		// Clip viewport info
    bool						m_useClipViewport;		// Turn on clipping for the viewport
    
    /*
     Sexy::SimpleMatrix			m_cameraTransform;		// Transform to be applied to normalized coordinates
     Sexy::SimpleMatrix			m_viewMatrix;			// Converts our normalized coordinates into screen space
     Sexy::SimpleMatrix			m_normalizedViewMatrix;	// Converts our screen coordinates into normalized coordinates based upon the camera's center
     Sexy::Rect					m_viewport;				// Viewport Info
     */	
};

inline const Sexy::FPoint& WorldMapCamera::GetCameraScale() const
{
    return m_cameraScale;
}

#endif
