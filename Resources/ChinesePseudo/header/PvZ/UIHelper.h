//
//  UIHelper.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 2/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UIHelper__
#define __PlantsVersusZombies2__UIHelper__

#include "Rect.h"
#include "TodCommon.h"
#include "UIWidget.h"

namespace Sexy
{
	class Graphics;
	class Image;
	class Font;
}

class PrimeText_PotentialTypeface;

void Draw3SliceImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_leftSliceImage, Sexy::Image* i_middleSliceImage, Sexy::Image* i_rightSliceImage, bool i_isStretched = false);
void Draw3SliceImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_threeSliceImage);
void Draw3SliceImageVertical(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_threeSliceImage);
void Draw3SliceImageVertical(Sexy::Graphics* i_g, const Sexy::Rect& i_destRect, Sexy::Image* i_topSliceImage, Sexy::Image* i_middleSliceImage, Sexy::Image* i_bottomSliceImage, bool i_isStretched = false);
void Draw9SliceImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_nineSliceImage);

void DrawAdaptiveImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_image);
void DrawAdaptiveInInscribedCircleImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_image);
void DrawHorizontalCropImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_image);
void DrawVerticalCropImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_image);
void DrawAutoCropImage(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_image);

// draw the 9 slice image with the middle one being optional
void Draw9Slice(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_topLeftImage, Sexy::Image* i_topMiddleImage, Sexy::Image* i_topRightImage
																, Sexy::Image* i_middleLeftImage, Sexy::Image* i_middleMiddleImage, Sexy::Image* i_middleRightImage
																, Sexy::Image* i_bottomLeftImage, Sexy::Image* i_bottomMiddleImage, Sexy::Image* i_bottomRightImage);

void DrawImageTiled(Sexy::Graphics* i_g, const Sexy::Rect i_destRect, Sexy::Image* i_image, const float i_scale = 1.0f);

void WriteWordInRect(Sexy::Graphics* i_g, const SexyString& i_label, const Sexy::Rect& i_inRect, Sexy::PrimeTypeface* i_font, Color i_color, DrawStringJustification i_justification, bool i_wrapped);


//PVZ2_CHINESE_BEGIN
void WriteWordInRect(Sexy::Graphics* i_g, const SexyString& i_label, const Sexy::Rect& i_inRect, PrimeText_PotentialTypeface* i_font, Color i_color, DrawStringJustification i_justification, bool i_wrapped);

void WriteWordInRect(Sexy::Graphics* i_g, const SexyString& i_label, const Sexy::Rect& i_inRect, Font* i_font, Color i_color, DrawStringJustification i_justification, bool i_wrapped);
//PVZ2_CHINESE_END

void DrawImageAsDisc(Sexy::Graphics* i_g, Sexy::Image* i_image, const Sexy::SexyVector2& i_centerPointOnScreen, const Sexy::SexyVector2& i_scale, float i_rotationDegrees);
void DrawImageFlipFlopped(Sexy::Graphics* i_g, Sexy::Image* i_image, const Sexy::SexyVector2& i_centerPointOnScreen, const Sexy::SexyVector2& i_scale);

void DrawSpaceSpiral(Sexy::Graphics* i_g, const int i_alpha, const Color i_spiralColorOverride = Color(0,0,0,0));
void DrawSpaceSpiralSpecial(Sexy::Graphics* i_g);

class PrimeTypeface* GetSizedFontForStrings(class PrimeTypeface* i_baseFont, const std::vector<SexyString>& i_strings, const int i_screenMaxTextWidth, const int i_screenMaxTextHeight, int& o_widthUsed, int& o_heightUsed, std::vector<int>& o_stringHeights);

// Given a source image and a bounding rectangle, returns a new rectangle that defines the area in which you
// should render that image if you want it to be centered and stretched to fill the given area, keeping its aspect ratio
Sexy::Rect StretchAndCenterImageInRect(Sexy::Image* i_image, Sexy::Rect i_destinationRect);

void ConvertJustificationToEAText(DrawStringJustification i_justification, EA::Text::HAlignment& i_horizAlignment, EA::Text::VAlignment& i_vertAlignment);

namespace UIHelper
{
	bool TriggerWorldMapBackButton();
};

//
// Class intended to aggregate temporary lists of UIWidgets for manual arranging.
//
class UIWidgetArranger
{
public:
    enum Layout
    {
        Horizontal,
        Vertical
    };
    
    UIWidgetArranger(const int i_maxCount)
    {
        assert(i_maxCount <= kMaxWidgetsToArrange);
        m_widgetMax = i_maxCount;
        m_widgetCount = 0;
    }

    void			AddBySheetName(const std::string& i_widgetName);
    int				Count() { return m_widgetCount; }
    UIWidget*		GetWidgetByID(const int i_widgetID);
    int				Arrange(const Layout i_layout, const int i_startX, const int i_startY, const int i_minGap, const int i_extraEndGap, const int i_minTotalWidth, const int i_maxTotalWidth);
    
private:
    const static int kMaxWidgetsToArrange = 3;
    
private:
    int				m_widgetMax;
    int				m_widgetCount;
    UIWidget*		m_widgets[kMaxWidgetsToArrange];
};


#endif /* defined(__PlantsVersusZombies2__UIHelper__) */
