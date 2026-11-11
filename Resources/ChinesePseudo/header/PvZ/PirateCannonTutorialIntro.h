//
//  PirateCannonTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PirateCannonTutorialIntro_h
#define PlantsVersusZombies2_PirateCannonTutorialIntro_h

#include "StandardLevelIntro.h"
#include "Core.h"
#include "Zombie.h"
#include "GridItem.h"
#include "AnimationMgr.h"

class PirateCannonTutorialIntro : public StandardLevelIntro
{

public:
	
	RT_CLASS_DEFINE(PirateCannonTutorialIntro, StandardLevelIntro, RtClass) {}
	
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	
	virtual void					initializeModule() override;
	virtual void					registerForEvents() override;

	virtual bool					manualIntroStart() const override { return true; }
	virtual bool					suppressReadySetGo() const override { return true; }
	virtual void					startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false) override;

private:

	enum State
	{
		PVZ_BEGIN_ENUM(STATE_CT_),
		STATE_CT_LOADING,
		STATE_CT_START,
		STATE_CT_DAVE_INTRO,
		STATE_CT_WAIT_FOR_CANNON_FIRE,
		STATE_CT_FIRED,
		STATE_CT_FAILED,
		STATE_CT_READY,
		STATE_CT_SET,
		STATE_CT_FIRE,
		STATE_CT_PLAYING,
		PVZ_END_ENUM(STATE_CT_),
	};
	
	void							onStartIntro();
	void							onUpdate();
	void							onEndLevel();

    void                            setState(State i_state);
	void							addToRenderQueue(class RenderQueue* i_queue);
	void                            showTools(bool i_isShown);

    void                            startGame();

    void                            setupDaveProlog(bool i_returningFromFailedState=false);
    void                            setupWaitForCannonFire();
    void                            setupCannonFired();
    void                            setupDaveFailed();
	
	void							onNarrationFinished();
    void                            onZombieDestroyed(Zombie* i_zombie);
    void                            onPlantDied(Plant* i_plant);
    
    State                           m_state;
    AnimationMgr                    m_animationMgr; 
    
    class ShowAdvice*               m_showAdvice;
};

class PirateCannonTutorialProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(PirateCannonTutorialProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PirateCannonTutorialIntro::StaticGetClass();
	}
	
	PirateCannonTutorialProperties()
	{
		ShowTutorial = false;
	}
	
	bool ShowTutorial;
};


#endif
