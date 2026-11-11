//
//  PinataRewardDrawer.h
//  PlantsVersusZombies2
//
//  Created by Matt Westhoff on 10/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PinataRewardDrawer__
#define __PlantsVersusZombies2__PinataRewardDrawer__

#include <string>
#include <vector>

#include "Color.h"
#include "SexyVector.h"
#include "StandaloneEffect.h"
#include "LevelOfTheDayConfigInfo.h"

class StandaloneEffect;

class PinataRewardDrawer
{
public:

	enum RewardAccent
	{
		RewardAccent_None,
		RewardAccent_Small,
		RewardAccent_Big,
	};

	PinataRewardDrawer();
	virtual ~PinataRewardDrawer();
	virtual void SetReward(int i_x, int i_y, const TheDayRewardItem* i_reward, bool i_showAccent);
	void SetOpacity(int i_fadeAmount);
	void SetDarkened(bool i_isDarkened);
	Sexy::SexyVector2 GetDrawDimensions() const;

private:

	std::vector<StandaloneEffectPtr> m_effects;
	//OwnedResourceManager m_resourceMgr; //nanlanglevel
	Sexy::Color m_color;
};

#endif /* defined(__PlantsVersusZombies2__PinataRewardDrawer__) */
