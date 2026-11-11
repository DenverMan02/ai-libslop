//
//  StarChallengeSimultaneousPlants.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/8/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StarChallengeSimultaneousPlants_h
#define PlantsVersusZombies2_StarChallengeSimultaneousPlants_h

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "GameNotify.h"
#include "ScrollingCounter.h"
#include "TodStringFile.h"
#include "UIWidget.h"
#include "BoardEnums.h"

class StarChallengeSimultaneousPlants : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengeSimultaneousPlants, Challenge, RtClass);

	virtual void registerForEvents() override;

	SexyString GetProgressDescription() const override;

    StarChallengeSimultaneousPlants()
	: m_mostPlantsAtOnce(0)
	, m_plantsRightNow(0)
	, m_isFailureCondition(true)
	{}

protected:
	void postInitialize() override;

private:
	void gameplayStarted();
	void gameplayEnded();

	void onUpdate();
    
    void gatherPlantingRestrictions(const Sexy::Point &i_gridPosition, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons);
    void updateCurrentPlantCount();
	
	virtual ChallengeUI* getChallengeUI() override
	{
		return m_plantCountUI->Cast<ChallengeUI>();
	}

	int m_mostPlantsAtOnce;
	int m_plantsRightNow;

	RtWeakPtr<UIWidget> m_plantCountUI;
	bool m_isFailureCondition;
};

class StarChallengeSimultaneousPlantsProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengeSimultaneousPlantsProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengeSimultaneousPlants::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), MaximumPlants);
		return TodReplaceString(_S("[STARCHALLENGE_PLANTS_AT_ONCE]"), _S("{COUNT}"), target);
	}

	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANTS_AT_ONCE_NAME]"));
	}
	
    StarChallengeSimultaneousPlantsProps()
	: MaximumPlants(0)
	{}

	int MaximumPlants;
};

#endif
