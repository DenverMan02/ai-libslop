//
//  EffectObject_FrostWind.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/16/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectObject_FrostWind__
#define __PlantsVersusZombies2__EffectObject_FrostWind__

#include "EffectObject.h"

class EffectObject_FrostWind : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_FrostWind, EffectObject, RtClass);

	void	onUpdate() override;
	void	onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void	applyFrost();
	
private:
	pvztime_t	m_timeToApplyFrost = PVZ_EOT();
	
	int		m_row = 0;
};


#endif /* defined(__PlantsVersusZombies2__EffectObject_FrostWind__) */
