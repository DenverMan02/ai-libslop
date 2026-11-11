//
//  ComponentZombieMovement.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 6/11/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentZombieFall__
#define __PlantsVersusZombies2__ComponentZombieFall__

#include "ComponentBase.h"
#include "TimeLine.h"

enum ComponentZombieMovementMotionType
{
	CZMMT_X = 1,
	CZMMT_Y,
	CZMMT_Z
};

class ComponentZombieMovement : public ComponentBase
{
public:
	RT_CLASS_DEFINE(ComponentZombieMovement, ComponentBase, RtClass);
	
	ComponentZombieMovement() {}
	~ComponentZombieMovement() {}
	
	void AddCurve(ComponentZombieMovementMotionType i_componentToCurve, pvztime_t i_duration, const float& i_startValue, const float& i_endValue, CurveType i_interpMethod);
	
protected:
	void onBegin() override;
	void onUpdate() override;
	void onEnd() override;
	
private:
	const std::string& getStringForMotionType(ComponentZombieMovementMotionType i_componentToCurve) const;
	
	CurveCollection_Float				m_lerpingValues;
};

#endif /* defined(__PlantsVersusZombies2__ComponentZombieFall__) */
