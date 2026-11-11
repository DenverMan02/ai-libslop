//
//  ZombieAnimRig_StaticArtPrototype.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/14/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_StaticArtPrototype_h
#define PlantsVersusZombies2_ZombieAnimRig_StaticArtPrototype_h

#include "ZombieAnimRig.h"

class ZombieAnimRig_StaticArtPrototype : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_StaticArtPrototype, ZombieAnimRig, RtClass) {}
	
	ZombieAnimRig_StaticArtPrototype()
	: m_scale(1.f, 1.f)
	{
	}
	
	void SetImage(ImagePtr i_image);
	void SetImageScale(SexyVector2 i_scale);
	void SetColor(Color i_color);
	
protected:
	virtual void onPopAnimInitialized() override;
	virtual void onPostDraw(Graphics* i_g) override;

private:
	ImagePtr 		m_staticImage;
	SexyVector2 	m_scale;
	Color			m_color;
};


#endif
