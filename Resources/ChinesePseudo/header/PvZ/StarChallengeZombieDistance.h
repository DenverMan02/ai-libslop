//
//  StarChallengeZombieDistance.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeZombieDistance_h
#define PlantsVersusZombies2_StarChallengeZombieDistance_h

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "Timeline.h"
#include "Effect_PopAnim.h"
#include "TodStringFile.h"

class StarChallengeZombieDistance : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeZombieDistance, Challenge, RtClass);

	virtual void registerForEvents() override;

    StarChallengeZombieDistance()
	: m_goalState(GS_Safe)
	, m_enteredState(PVZ_EOT())
	, m_closestZombie(std::numeric_limits<float>::max())
	{}

private:
	virtual void onFail() override;
    
	enum GoalState
	{
		GS_Safe,
		GS_ProximityAlert,
		GS_Failed
	};

	virtual void initializeModule() override;

	void levelStarted();
	void gameplayUpdate();
	void levelEnded();
	void gameplayEnded();
	void winOutroStarted();
	void onAnimStopped(StandaloneEffect* i_effect);

	void setState(GoalState i_state);
	bool failed(float i_x);
	bool proximityAlert(float i_x);
	float calcGoalX();

	GoalState m_goalState;
	pvztime_t m_enteredState;
	float m_closestZombie;

	void createFlowers();
	void playFlowerAnimation(const std::string &i_animName, bool i_looping);
	std::vector<RtWeakPtr<Effect_PopAnim> > m_flowers;
};

class StarChallengeZombieDistanceProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeZombieDistanceProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeZombieDistance::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
        //PVZ2_CHINESE_START
//		SexyString distance = StrFormat(_S("%g"), TargetDistance);
//		return TodReplaceString(_S("[STARCHALLENGE_ZOMBIE_DISTANCE]"), _S("{DISTANCE}"), distance);
        return TodStringTranslate(_S("[STARCHALLENGE_ZOMBIE_DISTANCE]"));
        //PVZ2_CHINESE_END
	}
	
	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_ZOMBIE_DISTANCE_NAME]"));
	}
	
    StarChallengeZombieDistanceProps()
	: TargetDistance(0.0f)
	{}

	float TargetDistance;
};

#endif
