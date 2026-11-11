//
//  IntroOakTrain.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-29.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroOakTrain__
#define __PlantsVersusZombies2__IntroOakTrain__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "DamageInfo.h"

STATE_ENUM_BASE_BEGIN(OTIState)
OTIState_HEAD_SHOOT,
OTIState_RELOAD_ARROW,
OTIState_GET_ARROW,
OTIState_CHANGE_ARROW,
OTIState_MULTI_SHOT,
OTIState_START_GAME,
STATE_ENUM_END(OTIState);

class AnimationMgr;
class Effect_BouncingArrow;

class OakTrainIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(OakTrainIntro, StandardLevelIntro, RtClass);
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    
	DECLARE_STATE_FUNCTIONS(OTIState, HEAD_SHOOT);
    DECLARE_STATE_FUNCTIONS(OTIState, RELOAD_ARROW);
    DECLARE_STATE_FUNCTIONS(OTIState, GET_ARROW);
    DECLARE_STATE_FUNCTIONS(OTIState, CHANGE_ARROW);
    DECLARE_STATE_FUNCTIONS(OTIState, MULTI_SHOT);
    DECLARE_STATE_FUNCTIONS(OTIState, START_GAME);
    
private:
	void        setState(OTIState i_newState);
	bool        isInState(OTIState i_state) const;
    
	void 		startGame();
    
    void        onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
    
    void        onOakArrowManualReload();
    void        onOakArrowAutoReload();
    void        onOakArrowTouch(const int i_type);
    
    void        ShowArrow(const Sexy::SexyVector2 &i_position);
    
	//RtWeakPtr<AnimationMgr>   					m_animationMgr;
	RtWeakPtr<Effect_BouncingArrow>				m_arrow;
    
	StateMachine<OTIState> 						m_OTIState;
};


class OakTrainIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(OakTrainIntroProperties, StandardLevelIntroProperties, RtClass);
    
	virtual RtClass* GetModuleClass() const override
	{
		return OakTrainIntro::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__IntroOakTrain__) */
