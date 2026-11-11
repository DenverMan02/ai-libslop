//
//  PlantsVersusZombies2
//
//  Created by hanj on 11/21/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//


#ifndef PlantsVersusZombies2_PowerupCukeTutorialIntro_h
#define PlantsVersusZombies2_PowerupCukeTutorialIntro_h

#include "StandardLevelIntro.h"
#include "PopAnimRig.h"
#include "Effect_BouncingArrow.h"
#include "StateMachine.h"
#include "AnimationMgr.h"
#include "WaveGenerator.h"
#include "TutorialFinger.h"
#include "Plant.h"

//forward declaration
class BasePowerup;
class Zombie;

STATE_ENUM_BASE_BEGIN(PowerupCukeTutorialState)
	POWERUPCUKETUTORIAL_SpawnZombies,
	POWERUPCUKETUTORIAL_DaveProlog,
	POWERUPCUKETUTORIAL_ArrowAlert,
	POWERUPCUKETUTORIAL_Advice,
    POWERUPCUKETUTORIAL_Plantfood,
    POWERUPCUKETUTORIAL_UsePlantfood,
    POWERUPCUKETUTORIAL_PlantfoodEnd,
    POWERUPCUKETUTORIAL_Start,
    POWERUPCUKETUTORIAL_Resume,
    POWERUPCUKETUTORIAL_WaveTrigger,
STATE_ENUM_END(PowerupCukeTutorialState);

class PowerupCukeTutorialIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(PowerupCukeTutorialIntro, StandardLevelIntro, RtClass);

	void setState(PowerupCukeTutorialState i_newState);
	virtual void pauseWave(bool bPause);

	TutorialFinger  m_finger;

protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;

	void onLoadComplete() override;

	DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, SpawnZombies);
	DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, DaveProlog);
	DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, ArrowAlert);
	DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, Advice);
    DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, Plantfood);
    DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, UsePlantfood);
    DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, PlantfoodEnd);
    DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, Start);
    DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, Resume);
    DECLARE_STATE_FUNCTIONS(PowerupCukeTutorialState, WaveTrigger);

    virtual void startIntro();
    virtual void update();
    virtual void onEndLevel();
    virtual void onGameplayStarted();
    virtual void enterTutorial();
    virtual bool needCukeTutorial();
    virtual void onToolAppliedPlantFood(class PlantGroup* i_plant);

private:
    void addToRenderQueue(class RenderQueue* i_queue);
    void drawLawnOverlays(Graphics* i_g);
	//void update();
	//void setState(PowerupCukeTutorialState i_newState);
    bool isInState(PowerupCukeTutorialState i_state) const;

	//void startIntro();
	void onPowerupSelected(BasePowerup* i_powerup);
	void onPowerupDeactivated(BasePowerup* i_powerup);
    void onShowCukeConfirm(bool show);
    void onWaveStarted(int i_wave, WaveType::WaveType i_type, bool i_isFinal);
	void onNarrationFinished();
	//void onEndLevel();
    //void onGameplayStarted();
	void onEndOfAdvice();
	void introduceDave();
    void onCanApplyPlantfood(class PlantGroup* i_plant, bool* o_isCan);
    //void onToolAppliedPlantFood(Plant* i_plant);

	void setupOpeningZombies();
	void pointArrowAtPowerupButton();
	void makeZombieRiseFromGround(Zombie *i_zombie);
    //void pauseWave(bool bPause);

	RtWeakPtr<Effect_BouncingArrow> m_bouncingArrow;
	AnimationMgrWkPtr               m_animationMgr;

	StateMachine<PowerupCukeTutorialState> m_powerupCukeTutorialState;

    void setPowerupCukeTutorialStateSerialization(int32 i_state);
    int32 getPowerupCukeTutorialStateSerialization();
    
private:
    float           m_waveTriggerTime = 0.0f;
    //TutorialFinger  m_finger;
    PlantPtr        m_plantPtr;
    bool            m_bUsingPlantfood = false;
};

class PowerupCukeTutorialIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(PowerupCukeTutorialIntroProperties, StandardLevelIntroProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return PowerupCukeTutorialIntro::StaticGetClass();
	}

	std::string PlantfoodAdvice = "";
	std::string EatPlantfoodIntro = "";
	std::string UsePlantfoodIntro = "";
	bool SkipCuke = false;
	bool SkipIntro = false;
};

#endif
