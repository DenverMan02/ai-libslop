//
//  IntroThunder.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-7-24.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroThunder__
#define __PlantsVersusZombies2__IntroThunder__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "Effect_BouncingArrow.h"

STATE_ENUM_BASE_BEGIN(TIState)
TIState_START_TUTORIAL,
TIState_THUNDER,
TIState_WAIT_PLANT_SELECT,
TIState_WAIT_PLANTED,
TIState_START_GAME,
STATE_ENUM_END(TIState);

class ThunderIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(ThunderIntro, StandardLevelIntro, RtClass);
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    
	DECLARE_STATE_FUNCTIONS(TIState, START_TUTORIAL);
    DECLARE_STATE_FUNCTIONS(TIState, THUNDER);
    DECLARE_STATE_FUNCTIONS(TIState, WAIT_PLANT_SELECT);
    DECLARE_STATE_FUNCTIONS(TIState, WAIT_PLANTED);
    DECLARE_STATE_FUNCTIONS(TIState, START_GAME);
    
private:
	void        setState(TIState i_newState);
	bool        isInState(TIState i_state) const;
    
    int32       getThunderIntroStateSerialization();
    void        setThunderIntroStateSerialization(int32 i_state);
    
    void        onShowThunderNarrationFinished();
    void        onPlantedNarrationFinished();
    
    void        onProgressMeterSetFlagCount(int i_flagCount);
    
    void		onPlantPlanted(class Plant* i_plant);
	void		onCursorAdded(class BaseCursor* i_cursor);
	void		onCursorDestroyed(class BaseCursor* i_cursor);
    
    void        onThunderStart();
	void        onThunderEnd();
    
    Effect_BouncingArrow * addBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    void                   clearBouncingArrows();
    
    void        DrawRightHighlight(Graphics* g);
	void 		startGame();
    
	std::vector<StandaloneEffectPtr>            m_bouncingArrows;
	StateMachine<TIState> 						m_TIState;
};


class ThunderIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(ThunderIntroProperties, StandardLevelIntroProperties, RtClass);
    
	virtual RtClass* GetModuleClass() const override
	{
		return ThunderIntro::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__IntroThunder__) */
