//
//  Plant_Toadstool.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 4/28/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Toadstool__
#define __PlantsVersusZombies2__Plant_Toadstool__

#include "ComponentVisualStretcher.h"
#include "PlantFramework.h"
#include "PlantAnimRig.h"

enum ToadstoolState
{
	TS_Idle = 0,
	TS_Biting,
	TS_StretchTongue,
	TS_TongueWait,
	TS_RetractTongue,
	TS_BeginChewing,
	TS_Chewing,
	TS_Swallowing,

	TS_PlantfoodIdleSearch,
	TS_PlantfoodStretchTongue,
	TS_PlantfoodTongueWait,
	TS_PlantfoodRetractTongue,
	TS_PlantfoodBeginChewing,
	TS_PlantfoodChewing,
	TS_PlantfoodSwallowing,
	TS_PlantfoodEnd,
    TS_PlantfoodBurp
};

class ComponentVisualStretcher;

#pragma mark - ToadstoolProps

class ToadstoolProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ToadstoolProps, PlantPropertySheet, RtClass);
	
	ToadstoolProps()
	{
		TongueOffRowRangeOffset = 2;
		TimeBetweenBites = 0.5f;
		
		NormalTongueRange = 3.f;
        NormalTongueRangeHighLevel = NormalTongueRange + 1.f;
		NormalTongueSlapDamage = 200.0f;
		NormalTongueWaitTimeSeconds = 0.3f;
		NormalChewTimeSeconds = 5.0;
		NormalAmountOfSunProducedPerZombie = 25;
        NormalAmountOfSunProducedPerZombieHighLevel = 50;
		
		PFTargetSearchExpirationSeconds = 4.0f;
		PFMaxNumberOfTargets = 5;
		PFTongueRange = 5.f;
        PFTongueRangeHighLevel = PFTongueRange + 1.f;
		PFTongueSlapDamage = 200.0f;
		PFTongueWaitTimeSeconds = 0.1f;
		PFChewTimeSeconds = 5.0;
		PFAmountOfSunProducedPerZombie = 25;
        PFAmountOfSunProducedPerZombieHighLevel = 50;
	}
	
	std::vector<std::string>		ZombieChewBlacklist;
	
	int								TongueOffRowRangeOffset;
	float							TimeBetweenBites;
	Rect							RectInstantGulpTriggerRange;
	
	ComponentVisualStretcherProps	NormalTongueStretcherProps;
	float							NormalTongueRange;
    float                           NormalTongueRangeHighLevel;
	float							NormalTongueSlapDamage;
	pvztime_t						NormalTongueWaitTimeSeconds;
	pvztime_t						NormalChewTimeSeconds;
	int								NormalAmountOfSunProducedPerZombie;
    int                             NormalAmountOfSunProducedPerZombieHighLevel;
    
	ComponentVisualStretcherProps	PFTongueStretcherProps;
	pvztime_t						PFTargetSearchExpirationSeconds;
	int								PFMaxNumberOfTargets;
	float							PFTongueRange;
    float                           PFTongueRangeHighLevel;
	float							PFTongueSlapDamage;
	pvztime_t						PFTongueWaitTimeSeconds;
	pvztime_t						PFChewTimeSeconds;
	int								PFAmountOfSunProducedPerZombie;
    int                             PFAmountOfSunProducedPerZombieHighLevel;
};

#pragma mark - PlantToadstool

class PlantToadstool : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantToadstool, PlantFramework, RtClass);
	
	virtual ~PlantToadstool();

	void Initialize() override;
	
	bool CanApplyPlantfood() override { return true; }
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool CanEndPlantfood() override;
	
	void UpdateActions() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
    ZombiePtr FindTargetZombie(Rect& i_attackRect, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	GridItemPtr FindTargetDamageableGridItem(Rect& i_attackRect, PlantWeapon i_plantWeapon) override;
	
	void Draw(Graphics* i_g) override;
    void onDestroy() override;

	virtual bool CanBeWatered() override;
	
private:
	void setState(ToadstoolState i_state);
	void onExit(ToadstoolState i_exitingState);
	void onEnter(ToadstoolState i_enteringState);
	void onUpdate(ToadstoolState i_updatingState);
	
	bool tryToAcquireTargetForWeapon(PlantWeapon i_plantWeapon, bool i_closeRange);
	BoardEntity* searchForTarget(PlantWeapon i_plantWeapon, bool i_closeRange);
	float getTongueRange(PlantWeapon i_plantWeapon) const;
	Sexy::Rect getPlantAttackRect(PlantWeapon i_plantWeapon);
	float calculateDistanceToTarget(const BoardEntity* i_target, PlantWeapon i_plantWeapon) const;
	
	BoardEntityPtr findTargetInAttackRect(Rect& i_attackRect, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams, BoardEntityTypeFlag i_targetType);
	void findEntitiesInAttackRect(std::vector<BoardEntity*>& o_entities, Rect& i_attackRect, PlantWeapon i_plantWeapon, BoardEntityTypeFlag i_targetType) const;
	
	bool zombieIsBlacklisted(const Zombie* i_zombie) const;
	bool canZombieBeTargeted(const Zombie* i_zombie) const;
	bool canZombieBeMoved(const Zombie* i_zombie) const;
	bool isInRange(const BoardEntity* i_boardEntity, PlantWeapon i_plantWeapon) const;
	bool isTargetInCorrectRowAndColumn(const BoardEntity* i_boardEntity) const;
	bool isTargetUnique(const BoardEntity* i_boardEntity) const;
	
	SexyVector2 getTongueOrigin() const;
	
	SexyVector2 getTongueStretchDestination(PlantWeapon i_weapon) const;
	SexyVector2 getTongueRetractDestination(PlantWeapon i_weapon) const;
	
	void launchTongue(PlantWeapon i_weapon);
	void retractTongue(PlantWeapon i_weapon);
	
	void transitionIfTimeIsUp(ToadstoolState i_nextState, pvztime_t i_durationToWait);
	void transitionIfCurrentAnimationIsDone(ToadstoolState i_nextState);
	
	void swallowZombiesAndProduceSun(int i_sunPerZombie);
	void produceSun(int i_sunAmount);
	
	ToadstoolState						m_toadstoolState;
	BoardEntityPtr						m_currentTarget;
	std::vector<BoardEntityPtr>			m_previousTargetsHit;
	pvztime_t							m_animStartTime;
	int									m_totalTargetsHit;
	int									m_zombieKillCount;
	pvztime_t							m_biteTime;
	
	RtWeakPtr<ComponentVisualStretcher>	m_normalTongueStretcherComponent;
	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent;
};

#pragma mark - PlantAnimRig_Toadstool

class PlantAnimRig_Toadstool : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Toadstool, PlantAnimRig, RtClass);
	
	PlantAnimRig_Toadstool()
	: m_currentAnimationHandle(ANIMHANDLE_NONE)
    , m_toadstoolState(TS_Idle) {
		// Do nothing.
	}
	
	bool PlayIdleLooped() override;
	bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
	bool PlayPlantFoodEnd() override;
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	
	void SetToadstoolState(ToadstoolState i_state);
	
	void PlayBeginTongueAttack();
	void PlayTongueGrab();
	void PlayBite();
	void PlayBiteContinued();
	void PlayBeginChewing();
	
	void PlayPlantfoodBeginTongueAttack();
	void PlayPlantfoodTongueGrab();
	void PlayPlantfoodTongueAttackLoop();
	void PlayPlantfoodBeginChewing();
	void PlayPlantfoodEndSwallowing();
    void PlayPlantfoodBurp();
	
	bool CurrentAnimationIsFinished();
	
private:
	void onTongueAttackContinued(const std::string& i_animEnded);
	void onChewingContinued(const std::string& i_animEnded);
	void onBitingCompleted(const std::string& i_animEnded);
	
	void onPlantfoodTongueAttackContinued(const std::string& i_animEnded);
	void onPlantfoodChewingContinued(const std::string& i_animEnded);
	
	ToadstoolState m_toadstoolState;
	AnimHandle m_currentAnimationHandle;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Toadstool__) */
