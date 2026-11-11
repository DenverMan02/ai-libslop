//
//  CollectableCure.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-12-3.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CollectableCure__
#define __PlantsVersusZombies2__CollectableCure__

#include "CollectableType.h"
#include "Collectable.h"
#include "Plant.h"

class CollectableCureType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableCureType, CollectableType, RtClass);
    
	CollectableCureType() : CollectableType()
	{
		CureValue = 150;
	}
    
	int CureValue;
};

/// Implementation

class CollectableCure : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableCure, Collectable, RtClass);
    
	int GetCureValue() const;
	
	// ZombieRa functionality
	void StartCaptureEffect();
	void StopCaptureEffect();
    
    PlantPtr     m_curePlant;
	
protected:
	virtual void onCollectableInitialize() override;
	virtual void onFinishMotion() override;
	
	virtual void onUpdate() override;
};

#endif /* defined(__PlantsVersusZombies2__File__) */
