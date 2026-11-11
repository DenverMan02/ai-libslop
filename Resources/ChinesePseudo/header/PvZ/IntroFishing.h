//
//  IntroPooyan.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.27
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroPooyan__
#define __PlantsVersusZombies2__IntroPooyan__

#include <stdio.h>
#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"

STATE_ENUM_BASE_BEGIN(FIState)
	FIState_StartTutorial,
	FIState_ChangeLaser,
	FIState_CannonDesc,
	FIState_StartGame,
STATE_ENUM_END(FIState);

class IntroFishing : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(IntroFishing, StandardLevelIntro, RtClass);
    IntroFishing();
	virtual ~IntroFishing();
    
    virtual void			AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	class FishingModule*	GetFishingModule();
    
protected:
    virtual void			initializeModule() override;
    virtual void			registerForEvents() override;

	void						setState(FIState i_newState);
	bool						isInState(FIState i_state) const;
	bool						CheckZombiesDie();
	Zombie*				SpawnZombie(const SexyVector3& boardPos);
	void						ClearIntro();
    
    void						onIntroStarted();
    void						onUpdate();
    void						onLevelEnded();
    void						onGameplayStarted();
	void						onSkyCannonTypeSelected(int i_typeID);
	void						onFishingTutorial_CheckTouch(const Sexy::Touch& i_touch, bool* pCanTouch);

	DECLARE_STATE_FUNCTIONS(FIState, StartTutorial);
	DECLARE_STATE_FUNCTIONS(FIState, ChangeLaser);
	DECLARE_STATE_FUNCTIONS(FIState, CannonDesc);
	DECLARE_STATE_FUNCTIONS(FIState, StartGame);
protected:
	StateMachine<FIState> 									m_State;
	RtWeakPtr<class Effect_BouncingArrow>	m_arrowEffect;
	std::vector<ZombiePtr>									m_zombies;
	pvztime_t															m_timerDesc1;
	pvztime_t															m_timerDesc2;
	bool																		m_canTouch;
};

class IntroFishingProperties : public StandardLevelIntroProperties
{
public:
    RT_CLASS_DEFINE(IntroFishingProperties, StandardLevelIntroProperties, RtClass);
	IntroFishingProperties();
    
    virtual RtClass* GetModuleClass() const override
    {
        return IntroFishing::StaticGetClass();
    }
    
};

#endif /* defined(__PlantsVersusZombies2__IntroPooyan__) */
