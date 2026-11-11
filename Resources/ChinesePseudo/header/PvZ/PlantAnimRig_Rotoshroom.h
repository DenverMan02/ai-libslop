//
//  PlantAnimRig_Rotoshroom.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 9/26/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_ROTOSHROOM_H__
#define __PLANTANIMRIG_ROTOSHROOM_H__

#include <string>

#include "PlantAnimRig.h"
#include "RtObject.h"
#include "SexyVector.h"

namespace Sexy {
class Graphics;
class PASpriteInst;
class PATransform;
}  // namespace Sexy

class PlantAnimRig_Rotoshroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Rotoshroom, PlantAnimRig, RtClass);
	
	PlantAnimRig_Rotoshroom();
	
	void SetRotation(float rotation);
	void SetOverlayVisibility(bool visible);
	
private:
	virtual void onPopAnimInitialized() override;
	virtual void onPostDraw(Graphics* i_graphics) override;
	
	void drawSpriteWithRotation(Graphics* i_graphics, const std::string& i_layerName, const SexyVector2& i_pivot);
	
	PASpriteInst* getSpriteAndDrawTransform(const std::string& i_layerName, PASpriteInst* i_spriteInst, PATransform* i_parentTransform, bool i_additive, bool i_parentFrozen, PATransform &o_transform);
	SexyVector2 getPivotForLayer(const std::string& i_layerName);
	
	float	m_rotation;
	bool	m_isOverlayVisible;
};

#endif // __PLANTANIMRIG_ROTOSHROOM_H__
