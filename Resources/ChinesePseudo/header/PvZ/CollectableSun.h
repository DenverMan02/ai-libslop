//
//  CollectableSun.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/18/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableSun_h
#define PlantsVersusZombies2_CollectableSun_h

#include "CollectableType.h"
#include "Collectable.h"

/// Parameters

class CollectableSunType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableSunType, CollectableType, RtClass);

	CollectableSunType() : CollectableType()
	{
		SunValue = 25;
	}

	int SunValue;
};

/// Implementation

class CollectableSun : public Collectable
{
public:
    enum SunType
    {
        SUN_NORMAL,
        SUN_BOMB,
    };

public:
	RT_CLASS_DEFINE(CollectableSun, Collectable, RtClass);

	int GetSunValue() const;
	
	// ZombieRa functionality
	void StartCaptureEffect(std::string i_color);
	void StopCaptureEffect();

	SunType GetSunType() const
	{
		return m_sunType;
	}
	void SetSelfAutoCollect(bool i_collect) { m_selfAutoCollect = i_collect; }

protected:
	virtual void onCollectableInitialize() override;
	virtual void onFinishMotion() override;
	
	virtual void onUpdate() override;

	bool m_isSunBomb;

	SunType m_sunType;
	bool m_selfAutoCollect;
};


class CollectableHeroPlantFakeSun : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableHeroPlantFakeSun, Collectable, RtClass);

	CollectableHeroPlantFakeSun();

	void setSunValue(int i_sunValue);
	int getSunValue();

protected:
	virtual void onFinishMotion() override;

private:
	int SunValue;
};


#endif
