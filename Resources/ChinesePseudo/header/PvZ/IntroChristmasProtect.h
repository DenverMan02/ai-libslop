//
//  IntroChristmasProtect.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-3.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroChristmasProtect__
#define __PlantsVersusZombies2__IntroChristmasProtect__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "Effect_BouncingArrow.h"
#include "BoardEnums.h"

STATE_ENUM_BASE_BEGIN(CMPState)
CMPState_START_TUTORIAL,
CMPState_WAIT_STEAL,
CMPState_WAIT_PLANTED,
CMPState_START_GAME,
STATE_ENUM_END(CMPState);

class AnimationMgr;
class Effect_BouncingArrow;

class ChristmasProtectIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(ChristmasProtectIntro, StandardLevelIntro, RtClass);
    
    std::string GetIntroPlant();
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    
	DECLARE_STATE_FUNCTIONS(CMPState, START_TUTORIAL);
    DECLARE_STATE_FUNCTIONS(CMPState, WAIT_STEAL);
    DECLARE_STATE_FUNCTIONS(CMPState, WAIT_PLANTED);
    DECLARE_STATE_FUNCTIONS(CMPState, START_GAME);
    
private:
	void        setState(CMPState i_newState);
	bool        isInState(CMPState i_state) const;
    
    int32       getChristmasProtectIntroStateSerialization();
    void        setChristmasProtectIntroStateSerialization(int32 i_state);
    
    void        onTipNarrationFinished();
    void        onCollectableHitGround(class Collectable * i_collectable);
    void        gatherPlantlessPlantingRestrictions(const Sexy::Point &i_gridPosition,
                                                    std::vector<PlantingReason> *io_plantingReasons);
    
    void        onProgressMeterSetFlagCount(int i_flagCount);
    
    void		onPlantPlanted(class Plant* i_plant);
	void		onCursorAdded(class BaseCursor* i_cursor);
	void		onCursorDestroyed(class BaseCursor* i_cursor);
    
    Effect_BouncingArrow * addBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    void                   clearBouncingArrows();
    
    void        DrawRightHighlight(Graphics* g);
	void 		startGame();
    
	std::vector<StandaloneEffectPtr>            m_bouncingArrows;
	StateMachine<CMPState> 						m_CMPState;
};


class ChristmasProtectIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(ChristmasProtectIntroProperties, StandardLevelIntroProperties, RtClass);
    
	virtual RtClass* GetModuleClass() const override
	{
		return ChristmasProtectIntro::StaticGetClass();
	}
    
    std::string IntroPlant;
};

#endif /* defined(__PlantsVersusZombies2__IntroChristmasProtect__) */
