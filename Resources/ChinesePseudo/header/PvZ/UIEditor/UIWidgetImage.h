//
//  UIWidgetImage.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIWidgetImage_h_
#define _UIWidgetImage_h_
#include "Widget.h"
#include "PVZ2UIButton.h"

enum Align_Image
{
	Align_TopLeft,
	Align_center
};

class UIWidgetImage : public Sexy::Widget
{
public:
    enum
    {
        Color_Image = 0,
    };
public:
	UIWidgetImage();
	UIWidgetImage(const std::string& image_name);
	UIWidgetImage(class Sexy::Image* pImage);
	virtual ~UIWidgetImage();

	virtual void					Draw(Sexy::Graphics* i_g) override;

	void								SetImage(const std::string& image_name);
	void								SetImage(Sexy::Image* pImage);
	void								SetImage(const PVZ2UIImage& img);
	class Sexy::Image*	GetImage();
	const PVZ2UIImage& GetPVZ2Image() const { return m_image; }
	void								SetImageType(const PVZ2UIImageType& image_type, float i_rotate = 0.0f);
	void SetAlignImage(Align_Image alignImage);
protected:
    void                        internalDraw(Sexy::Graphics* i_g);

protected:
	PVZ2UIImage			m_image;
	Align_Image			m_AlignImage;
};



#endif
