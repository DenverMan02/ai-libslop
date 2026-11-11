//
//  IntroTowerDefend.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-29.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroTowerDefend__
#define __PlantsVersusZombies2__IntroTowerDefend__

#include "StandardLevelIntro.h"
#include "StateMachine.h"

STATE_ENUM_BASE_BEGIN(TDIState)
TDIState_START_TUTORIAL,
TDIState_START_GAME,
STATE_ENUM_END(TDIState);

class AnimationMgr;
class Effect_BouncingArrow;

class TowerDefendIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(TowerDefendIntro, StandardLevelIntro, RtClass);
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    
    void            onPlantTouch(const Point& i_pos);
	void            onPlantUpgradeTouch(const Point& i_pos);
    
    
	DECLARE_STATE_FUNCTIONS(TDIState, START_TUTORIAL);
    DECLARE_STATE_FUNCTIONS(TDIState, START_GAME);
    
private:
	void        setState(TDIState i_newState);
	bool        isInState(TDIState i_state) const;
    
    int32 getTowerDefendIntroStateSerialization();
    void  setTowerDefendIntroStateSerialization(int32 i_state);
    
	void 		startGame();
    
	//RtWeakPtr<AnimationMgr>   			    m_animationMgr;
    
	RtWeakPtr<Effect_BouncingArrow>				m_arrow;
	StateMachine<TDIState> 						m_TDIState;
    pvztime_t                                   m_showTipTime;
};


class TowerDefendIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(TowerDefendIntroProperties, StandardLevelIntroProperties, RtClass);
    
	virtual RtClass* GetModuleClass() const override
	{
		return TowerDefendIntro::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__IntroTowerDefend__) */
