//
//  Plant_Fishhookgrass.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 4/28/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Fishhookgrass__
#define __PlantsVersusZombies2__Plant_Fishhookgrass__

#include "ComponentVisualStretcher.h"
#include "PlantFramework.h"
#include "PlantAnimRig.h"

// Projectile hook
#include "Projectile.h"
typedef RtReflectionDelegate<Delegate0> HookLandedDelegate;

enum FishhookgrassState
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
class FishHookGrassProjectile;

#pragma mark - FishhookgrassProps

class FishhookgrassProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(FishhookgrassProps, PlantPropertySheet, RtClass);
	
	FishhookgrassProps()
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

#pragma mark - PlantFishhookgrass

class PlantFishhookgrass : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantFishhookgrass, PlantFramework, RtClass);
	
	virtual ~PlantFishhookgrass();

	void Initialize() override;
	
	bool CanApplyPlantfood() override { return true; }
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool CanEndPlantfood() override;
	int PF_LNum = 0;
	std::vector<BoardEntityPtr>  PF_zombies;
	std::vector<BoardEntityPtr>  PF_zombies_Temp;
	std::vector<BoardEntityPtr>  PF_zombies_BT;
	std::vector<Zombie*>  PF_zombies_Z;
	std::vector<BoardEntityPtr>  PF_zombies_ZH;
	bool m_needsToReel = false;
	bool m_PFneedsToReel = false;
	
	void UpdateActions() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
    ZombiePtr FindTargetZombie(Rect& i_attackRect, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	GridItemPtr FindTargetDamageableGridItem(Rect& i_attackRect, PlantWeapon i_plantWeapon) override;
	
	void Draw(Graphics* i_g) override;
    void onDestroy() override;

	virtual bool CanBeWatered() override;

	RtWeakPtr<FishHookGrassProjectile> m_hook;
	RtWeakPtr<FishHookGrassProjectile> m_hook0;
	RtWeakPtr<FishHookGrassProjectile> m_hook1;
	RtWeakPtr<FishHookGrassProjectile> m_hook2;
	RtWeakPtr<FishHookGrassProjectile> m_hook3;
	RtWeakPtr<FishHookGrassProjectile> m_hook4;
	RtWeakPtr<FishHookGrassProjectile> m_hook5;
	RtWeakPtr<FishHookGrassProjectile> m_hook6;
	RtWeakPtr<FishHookGrassProjectile> m_hook7;
	std::vector<RtWeakPtr<FishHookGrassProjectile>> PF_hook;

private:
	void setState(FishhookgrassState i_state);
	void onExit(FishhookgrassState i_exitingState);
	void onEnter(FishhookgrassState i_enteringState);
	void onUpdate(FishhookgrassState i_updatingState);
	
	bool tryToAcquireTargetForWeapon(PlantWeapon i_plantWeapon, bool i_closeRange);
	bool tryToAcquireAllTarget();
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
	SexyVector2 getTongueStretchDestinationAll(PlantWeapon i_weapon,BoardEntityPtr i_currentTarget) const;
	SexyVector2 getTongueRetractDestination(PlantWeapon i_weapon) const;
	SexyVector2 getTongueRetractDestinationAll(PlantWeapon i_weapon,BoardEntityPtr i_currentTarget) const;
	void launchTongue(PlantWeapon i_weapon);
	void launchTongueAll(PlantWeapon i_weapon);
	void onHookReachedTarget();
	void onHookReeledIn();
	void retractTongue(PlantWeapon i_weapon);
	void retractTongueAll(PlantWeapon i_weapon);
	
	void transitionIfTimeIsUp(FishhookgrassState i_nextState, pvztime_t i_durationToWait);
	void transitionIfCurrentAnimationIsDone(FishhookgrassState i_nextState);
	
	void swallowZombiesAndProduceSun(int i_sunPerZombie);
	void produceSun(int i_sunAmount);
	
	FishhookgrassState						m_toadstoolState;
	BoardEntityPtr						m_currentTarget;
	Zombie*                             m_zombie;
	std::vector<BoardEntityPtr>			m_previousTargetsHit;
	pvztime_t							m_animStartTime;
	int									m_totalTargetsHit;
	int									m_zombieKillCount;
	float								h_lang = 0;
    float								T_attack = 0;
    int 								r_num = 0;
    int									m_PFCount;
    int									m_Bcount;
    int									m_SMcount;
	pvztime_t							m_biteTime;
	float								T_PFST = 0;
	float								T_ST = 0;
	
//	RtWeakPtr<ComponentVisualStretcher>	m_normalTongueStretcherComponent;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent0;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent1;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent2;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent3;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent4;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent5;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent6;
//	RtWeakPtr<ComponentVisualStretcher>	m_plantfoodTongueStretcherComponent7;
//
//	std::map<int, RtWeakPtr<ComponentVisualStretcher>> mapStretcherComponent;
	std::map<int, RtWeakPtr<FishHookGrassProjectile>> map_hook;
};

#pragma mark - PlantAnimRig_Fishhookgrass

class PlantAnimRig_Fishhookgrass : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Fishhookgrass, PlantAnimRig, RtClass);
	
	PlantAnimRig_Fishhookgrass()
	: m_currentAnimationHandle(ANIMHANDLE_NONE)
    , m_toadstoolState(TS_Idle) {
		// Do nothing.
	}
	
	bool PlayIdleLooped() override;
	bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
	bool PlayPlantFoodEnd() override;
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	
	void SetFishhookgrassState(FishhookgrassState i_state);
	
	void PlayBeginTongueAttack(bool is_lv5);
	void PlayBeginPFTongueAttack();
	void PlayTongueGrab();
	void PlayBite();
	void PlayBiteContinued();
	void PlayBeginChewing();
	void PlayBeginthrow(bool is_lv5);
	void PlayBeginPFthrow();
	void PlayReceiveHook(bool is_lv5);
	void PlayPFReceiveHook();
	
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
	
	FishhookgrassState m_toadstoolState;
	AnimHandle m_currentAnimationHandle;
};


// #Projectile hook

class FishHookGrassProjectile : public Projectile
{
private:
	enum HookState
	{
		PVZ_BEGIN_ENUM(HOOKSTATE_),
		HOOKSTATE_IDLE,
		HOOKSTATE_CASTING,
		HOOKSTATE_REELING,
		HOOKSTATE_BOUNCING,
		PVZ_END_ENUM(HOOKSTATE_),
	};

public:
	RT_CLASS_DEFINE(FishHookGrassProjectile, Projectile, RtClass);

	void CastHook(const float i_timePerSquare, std::function<void()> i_onHookLanded);
	void ReelHook(const float i_timePerSquare, const pvztime_t i_length, SexyVector2 i_pos, std::function<void()> i_onHookLanded);

	bool IsBouncing() { return HOOKSTATE_BOUNCING == m_state; }
	bool OnCollideEntity(BoardEntity* i_entity) override;
//	Plant* GetHookedPlant() { return m_hookedPlant; }
	Zombie* GetHookedZombie() { return m_hookedZombie; }
	bool m_isend = false;
	bool is_R = false;
	bool is_Y = false;
	bool is_PF = false;
	bool is_PF_Avatar = false;
	RtWeakPtr<Zombie> m_hookedZombie;

protected:
	void onUpdate(pvztime_t i_dt) override;
	void onDestroy() override;

private:

//	SexyVector3 getAttachmentPosition(Plant* i_plant);
	SexyVector3 getAttachmentPosition(Zombie* i_Zombie);

	HookState m_state;

	pvztime_t m_motionStartTime;
	pvztime_t m_motionEndTime;
	SexyVector3 m_motionStartPos;
	SexyVector3 m_motionEndPos;
	std::function<void()> m_onHookLandedDelegate;
//	RtWeakPtr<Plant> m_hookedPlant;
};

class FishHookGrassProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(FishHookGrassProjectileProps, ProjectilePropertySheet, RtClass);

	FishHookGrassProjectileProps()
	{
		// Do nothing.
	}
};




#endif /* defined(__PlantsVersusZombies2__Plant_Fishhookgrass__) */
