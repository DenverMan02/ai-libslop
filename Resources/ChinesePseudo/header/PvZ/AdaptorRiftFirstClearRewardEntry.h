//
//  AdaptorRiftFirstClearRewardEntry.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 11/21/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftFirstClearRewardEntry_h
#define AdaptorRiftFirstClearRewardEntry_h

#include "HotUIAdaptor.h"
#include "LevelOfTheDay_RewardData.h"
#include "RtObject.h"

class AdaptorRiftFirstClearRewardEntry : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRiftFirstClearRewardEntry, HotUIAdaptor, RtClass);
	
public:
	AdaptorRiftFirstClearRewardEntry() { m_cleared = false; }
	virtual ~AdaptorRiftFirstClearRewardEntry() {}
	void SetReward(LevelOfTheDay_RewardItemType* i_reward, bool i_cleared, int i_difficulty, bool i_firstClear);
	
protected:
	void refresh();
	
private:
	LevelOfTheDay_RewardItemType* m_reward;
	bool m_cleared;
	int m_difficulty;
	bool m_firstClear;
};

#endif /* AdaptorRiftFirstClearRewardEntry_h */
