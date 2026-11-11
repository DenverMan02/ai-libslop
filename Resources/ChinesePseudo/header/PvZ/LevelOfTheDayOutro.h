//
//  LevelOfTheDayOutro.h
//  PlantsVersusZombies2
//
//  Created by Matt Westhoff on 10/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelOfTheDayOutro__
#define __PlantsVersusZombies2__LevelOfTheDayOutro__

#include <vector>

#include "OutroModule.h"
#include "RtObject.h"
#include "LevelOfTheDayConfigInfo.h"

namespace Message
{
	void LevelRewardDropped();
}

class LevelOfTheDayOutro : public OutroModule
{
public:
    RT_CLASS_DEFINE(LevelOfTheDayOutro, OutroModule, RtClass);

	LevelOfTheDayOutro();
    virtual ~LevelOfTheDayOutro();
	
    void registerForEvents() override;
    
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
	const TheDayRewardItem* GetProgressiveRewardAwarded() {return m_progressiveAward;}

protected:
    void startVictoryOutro();
    void onFailure();
	bool getPreventSave();
	void onRewardSequenceFinished();
	void onProgressiveRewardSequenceFinished();
	void hideUI();
    
    void OnLeveloftheDayReward(bool i_success);
    void onGotChristmasProtect(bool i_success);
    void onNetworkError(int erroId);

    void Update();
	
private:
	const TheDayRewardItem* getAwardScreenReward() const;

	void showAwardScreen();
	void onAwardScreenDismissed();
    
    void getReward();

	const TheDayRewardItem* m_progressiveAward;
	std::vector<const TheDayRewardItem* > m_rewards;
	pvztime_t m_nextRequestTime;
	int m_requestCount;
};

class LevelOfTheDayOutroPropeties : OutroModuleProperties
{
    RT_CLASS_DEFINE(LevelOfTheDayOutroPropeties, OutroModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return LevelOfTheDayOutro::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__LevelOfTheDayOutro__) */
