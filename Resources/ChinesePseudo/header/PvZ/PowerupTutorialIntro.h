//
//  PowerupTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/24/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PowerupTutorialIntro_h
#define PlantsVersusZombies2_PowerupTutorialIntro_h

#include "StandardLevelIntro.h"
#include "Core.h"
#include "PopAnimRig.h"
#include "Effect_BouncingArrow.h"
#include "Zombie.h"
#include "PowerupWizardFinger.h"

class WaveDefinition;

struct PowerupHandAction
{
	// x positions in the vectors are percentage based
	PowerupHandAction()
	: m_startPos(0.f, 0.f), m_endPos(0.f, 0.f), m_seconds(0.f), m_activationTime(0.f)
	{}

	PowerupHandAction(const SexyVector2& i_startPos, const SexyVector2& i_endPos, const std::string& i_actionName, const float i_seconds=0.f)
	: m_startPos(i_startPos), m_endPos(i_endPos), m_actionName(i_actionName), m_seconds(i_seconds), m_activationTime(0.f)
	{
	}

	SexyVector2 m_startPos;
	SexyVector2 m_endPos;
	float m_seconds;
	std::string m_actionName;

	float m_activationTime;
};

class PowerupTutorialIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(PowerupTutorialIntro, StandardLevelIntro, RtClass);

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	virtual void onPostLoad() override;
	
	enum State
	{
		PVZ_BEGIN_ENUM(STATE_PUT_),

		STATE_PUT_START,

		// these three set up the state of the specific powerup tutorial
		// STATE_PUT_PINCH_SETUP,
		STATE_PUT_FLICK_SETUP,
		STATE_PUT_WIZARDFINGER_SETUP,
		STATE_PUT_END_OF_TUTORIAL,

		// these states are the state of the tutorial we're currently in
		STATE_PUT_DEMO_SETUP,
		STATE_PUT_DEMO,
		STATE_PUT_PLAYER_UNLIMITED_SETUP,
		STATE_PUT_PLAYER_UNLIMITED_USE,
		STATE_PUT_PLAYER_SELECT_POWERUP_SETUP,
		STATE_PUT_PLAYER_SELECT_POWERUP,
		STATE_PUT_PLAYER_POWERUP_KILL_ZOMBIES,
		STATE_PUT_PLAYER_ZOMBIE_WAVE,
		STATE_PUT_PLAYER_KILL_ALL_ZOMBIES,

		PVZ_END_ENUM(STATE_PUT_),
	};

	void setState(State i_state);
	void onLoadComplete() override;
	void update();

	void onLevelEnded();
	
	pvztime_t getTimeInState() const { return PVZ_T() - m_stateEntryTime; }
	
private:

	void onNarrationFinished();
	void spawnZombies(const std::vector<float>& i_zombieXPositionPercents, const bool i_clearZombies);
	void killZombies();
	void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
	void onAnimContinued(const std::string& i_endingAnimName, const std::string& i_newAnimName, int i_animEndCount);
	void onAnimFinished(const std::string& i_animName);
	void onAddToRenderQueue(class RenderQueue* i_queue);
	void onPowerupSelected(class BasePowerup* i_powerup);
	void onPowerupDeselected(class BasePowerup* i_powerup);
	void onPowerupDeactivated(class BasePowerup* i_powerup);
	void onWaveGenerated(int i_waveIndex, const WaveDefinition* i_wave);

	void doNextTutorialAnim();
	void pinchFinished();
	void swipeFinished();
	void wizardFingerFinished();
	void pointArrowAtPowerupButton(const std::string& i_powerupName);

	bool handleTouch(const Sexy::Touch& i_touch);

	void setupTutorial(const std::string& i_powerupName, const SexyString& i_powerupAdvice, const SexyString& i_demoBarText,
					   const std::vector<float>& i_zombieOffsets, const std::vector<PowerupHandAction>& i_handActions, const State i_nextTutorialState);
    
    void drawHandAnimation(class Graphics* i_g);

	State m_tutorialState;
	State m_nextTutorialPortionState;
	pvztime_t m_stateEntryTime;
	int m_tutorialAttemptCount;
	bool m_firstTimeThroughDemo;
	std::string m_currentPowerupName;
	std::vector<float> m_currentZombieOffsets;
	std::vector<PowerupHandAction> m_currentHandActions;
	SexyString m_currentPowerupUseAdvice;
	bool m_waitingForIdleToFinish;

	RtWeakPtr<Effect_BouncingArrow> m_bouncingArrow;
	PopAnimRigPtr m_handAnimation;
	std::vector<ZombiePtr> m_tutorialZombies;
	int m_currentHandAction;
	RtWeakPtr<WizardFingerGameObject> m_WFGameObject;
};

class PowerupTutorialIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(PowerupTutorialIntroProperties, StandardLevelIntroProperties, RtClass) {}

	virtual RtClass* GetModuleClass() const override
	{ 
		return PowerupTutorialIntro::StaticGetClass();
	}
};

#endif
