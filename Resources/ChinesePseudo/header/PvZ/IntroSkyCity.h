//
//  IntroSkyCity.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-7-23.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroSkyCity__
#define __PlantsVersusZombies2__IntroSkyCity__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "Effect_BouncingArrow.h"

STATE_ENUM_BASE_BEGIN(SCIState)
SCIState_START_TUTORIAL,
SCIState_SHOW_REGIONSKY,
SCIState_WAIT_PLANT_SELECT,
SCIState_WAIT_PLANTED,
SCIState_SHIP_HEALTH,
SCIState_START_GAME,
STATE_ENUM_END(SCIState);

class AnimationMgr;
class Effect_BouncingArrow;

class SkyCityIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(SkyCityIntro, StandardLevelIntro, RtClass);
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
    void            onAddToRenderQueue(class RenderQueue* i_queue);
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    
	DECLARE_STATE_FUNCTIONS(SCIState, START_TUTORIAL);
    DECLARE_STATE_FUNCTIONS(SCIState, SHOW_REGIONSKY);
    DECLARE_STATE_FUNCTIONS(SCIState, WAIT_PLANT_SELECT);
    DECLARE_STATE_FUNCTIONS(SCIState, WAIT_PLANTED);
    DECLARE_STATE_FUNCTIONS(SCIState, SHIP_HEALTH);
    DECLARE_STATE_FUNCTIONS(SCIState, START_GAME);
    
private:
	void        setState(SCIState i_newState);
	bool        isInState(SCIState i_state) const;
    
    int32       getSkyCityIntroStateSerialization();
    void        setSkyCityIntroStateSerialization(int32 i_state);
    
    void        onShowReginSkyNarrationFinished();
    void        onShowShipHealthNarrationFinished();
    
    void        onProgressMeterSetFlagCount(int i_flagCount);
    
    void		onPlantPlanted(class Plant* i_plant);
	void		onCursorAdded(class BaseCursor* i_cursor);
	void		onCursorDestroyed(class BaseCursor* i_cursor);
    
    Effect_BouncingArrow * addBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    void                   clearBouncingArrows();
    
    void        DrawRightHighlight(Graphics* g);
	void 		startGame();
    
	std::vector<StandaloneEffectPtr>            m_bouncingArrows;
	StateMachine<SCIState> 						m_SCIState;
};


class SkyCityIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(SkyCityIntroProperties, StandardLevelIntroProperties, RtClass);
    
	virtual RtClass* GetModuleClass() const override
	{
		return SkyCityIntro::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__IntroSkyCity__) */
