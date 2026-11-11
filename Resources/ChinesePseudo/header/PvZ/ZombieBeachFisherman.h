//
//  ZombieBeachFisherman.h
//  PlantsVersusZombies2
//
//  Created by Brad Buchanan on 7/10/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieBeachFisherman__
#define __PlantsVersusZombies2__ZombieBeachFisherman__

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "BoardEnums.h"

class FishHookProjectile;

STATE_ENUM_CHILD_BEGIN(ZombieBeachFishermanState, ZombieState)
	ZS_FISHERMAN_FishermanIntro,
	ZS_FISHERMAN_FishermanIdle,
	ZS_FISHERMAN_FishermanCast,
	ZS_FISHERMAN_FishermanWait,
	ZS_FISHERMAN_FishermanReel,
	ZS_FISHERMAN_FishermanAttackAdjacent,
STATE_ENUM_END(ZombieBeachFishermanState)

class ZombieBeachFisherman : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieBeachFisherman, Zombie, RtClass);
	
	enum AttackType
	{
		ADJACENT,
		RANGED,
	};
	
	GroundEffectType GetTideEffect() const override;
    
    bool ShouldDrawShadow() const override;
	
protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, FishermanIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, FishermanIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, FishermanCast);
	DECLARE_STATE_FUNCTIONS(ZombieState, FishermanWait);
	DECLARE_STATE_FUNCTIONS(ZombieState, FishermanReel);
	DECLARE_STATE_FUNCTIONS(ZombieState, FishermanAttackAdjacent);

	void registerForEvents() override;
	void chooseDeathState(const DamageInfo& i_deathBlow) override;
	
	void onZombieInitialize() override;
	void onPlaceOnBoard() override;
	void onIntroCompleted(const std::string&);
	void onAttackCompleted(const std::string&);
	void onCastCompleted(const std::string&);
	void onDraw(class Sexy::Graphics* i_g) override;
	
private:
	void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	void blockGravestoneSpawning(const Sexy::Point& i_gridPosition, bool* o_blocked);
	
	// Intro
	int selectSpawnRow() const;
	void clearSpawnLocation();
	
	// Idle
	void findTargetAndCast();
	
	// Cast
	void castHook();
	void onHookReachedTarget();
	
	// Reel
	void onHookReeledIn();
	
	// AttackAdjacent
	void throwAdjacentPlant();
	
	void	onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	BoardEntity*	findTargetForAttackType(const AttackType& i_attackType);
	bool isValidTargetForAttackType(PlantGroupPtr i_targetGroup, const AttackType& i_attackType) const;
	void	pullRowWhileBlacklistingSelf(PlantGroupPtr i_target);
	
	RtWeakPtr<FishHookProjectile> m_hook;
	SexyVector2 m_targetPos;
	bool m_shouldUseTideEffect = true;
	bool m_needsToReel = false;
};

class ZombieBeachFishermanProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBeachFishermanProps, ZombiePropertySheet, RtClass);

	ZombieBeachFishermanProps()
	: DelayBetweenCasting(-1.f)
	, DelayBeforeReeling(-1.f)
	, CastingAreaMinRange(-1)
	, CastingAreaMaxRange(-1)
	, CastingAreaHeight(-1)
	, CastTimePerGridSquare(-1.f)
	, ReelTimePerGridSquare(-1.f)
	{}
	
	void Validate() const;

	float DelayBetweenCasting;
	float DelayBeforeReeling;
	
	int CastingAreaMinRange, CastingAreaMaxRange, CastingAreaHeight;
	float CastTimePerGridSquare, ReelTimePerGridSquare;

	std::vector<std::string> PlantablePlants;
	
	std::vector<std::string> AllowedLowPlants;
};

class ZombieAnimRig_BeachFisherman : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_BeachFisherman, ZombieAnimRig, RtClass);

	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieBeachFisherman__) */
