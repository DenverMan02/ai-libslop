//
//  StarChallengePlantBeforeLine.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarChallengePlantBeforeLine__
#define __PlantsVersusZombies2__StarChallengePlantBeforeLine__

#include "ChallengeModule.h"
#include "GameNotify.h"
#include "Effect_PopAnim.h"
#include "TodStringFile.h"
#include "BoardEnums.h"

class StarChallengePlantBeforeLine : public Challenge
{
public:
	RT_CLASS_DEFINE(StarChallengePlantBeforeLine, Challenge, RtClass);

	virtual void registerForEvents() override;

    StarChallengePlantBeforeLine()
	: m_moldState(MS_Idle)
	{}

private:
	virtual void onFail() override;
	
	enum MoldState
	{
		MS_Idle,
		MS_Cowering,
		MS_Dead,
	};

	void levelStarted();
	void levelEnded();
	void winOutroStarted();
	void gameplayUpdate();
    void gameplayEnded();
    
    void gatherPlantingRestrictions(const Sexy::Point &i_gridPosition, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons);
    
    void playMoldAnimation(const std::string &i_animName, bool i_looping);
    
    void onRailcartMoved(class GridItemRailcart* i_railcart);
    void onAnimStopped(StandaloneEffect* i_effect);
    
    MoldState m_moldState;
    std::vector<RtWeakPtr<Effect_PopAnim> > m_mold;
    
    // Mold bound to objects (like railcarts)
    struct BoundMold
    {
        RtWeakPtr<BoardEntity> Owner;
        RtWeakPtr<Effect_PopAnim> Mold;
    };
    std::vector<BoundMold> m_boundMold;
};

class StarChallengePlantBeforeLineProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StarChallengePlantBeforeLineProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StarChallengePlantBeforeLine::StaticGetClass();
	}

	virtual SexyString GetDescription() const override
	{
		SexyString target = StrFormat(_S("%d"), CannotPlantBeforeColumn);
		return TodReplaceString(_S("[STARCHALLENGE_PLANT_BEFORE_LINE]"), _S("{COLUMN}"), target);
	}
	
	virtual SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PLANT_BEFORE_LINE_NAME]"));
	}
	
    StarChallengePlantBeforeLineProps()
    : CannotPlantBeforeColumn(0)
    , CannotPlantStartingColumn(0)
    {}
    
    int CannotPlantBeforeColumn;
    int CannotPlantStartingColumn;
};

#endif /* defined(__PlantsVersusZombies2__StarChallengePlantBeforeLine__) */
