//
//  Effect_StaticImage.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_StaticImage_h
#define PlantsVersusZombies2_Effect_StaticImage_h

#include "StandaloneEffect.h"

class Effect_StaticImage : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_StaticImage, StandaloneEffect, RtClass);

	virtual void SetColor(const Color& i_color) override;
	virtual void SetScale(float i_scale) override;
	
	void SetCentered(bool i_centered);
	void SetImage(ImagePtr i_image);
    
    SexyVector2 GetDimensions() override;
	
    void SetPieceName(const std::string& i_name);
protected:
	virtual void onInitialized() override;
	virtual void onDraw(Graphics* i_g) override;

private:
	ImagePtr m_image;
	Color m_imageColor;
	bool m_centered = true;
	float m_scale = 1.0f;
	std::string m_pieceName;
};

#endif
