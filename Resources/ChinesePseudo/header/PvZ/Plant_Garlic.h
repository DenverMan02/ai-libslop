//
//  Plant_Garlic.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 10/3/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Garlic__
#define __PlantsVersusZombies2__Plant_Garlic__

#include "GameSubSystem.h"
#include "PlantFramework.h"
#include "RestrictionSet.h"

class ZombieType;

struct GarlicStateInfo
{
	pvztime_t EatDuration;
	pvztime_t RegretfulDuration;
	pvztime_t LaneChangeDuration;
	pvztime_t StunDuration;
	pvztime_t IndifferenceDuration;
	std::string SoundOfRegret;
	std::string SoundOfMoveUp;
	std::string SoundOfMoveDown;
};

class GarlicProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GarlicProps, PlantPropertySheet, RtClass);
	
	GarlicProps()
	: PlantFoodGasEffectDelay(0.0f)
    , GasDPS(10)
	{}
	
	GarlicStateInfo FromEating;
	GarlicStateInfo FromPlantfood;
    GarlicStateInfo FromPoisoned;
	float PlantFoodGasEffectDelay;
    float GasDPS;
	ZombieRestrictionSet ZombiesAffectedByEating;
	ZombieRestrictionSet ZombiesAffectedByPlantfood;
};

enum GarlicEffectedZombieState
{
	PVZ_BEGIN_ENUM(GARLICED_ZOMBIE_),
	GARLICED_ZOMBIE_Eating,
	GARLICED_ZOMBIE_Regretting,
	GARLICED_ZOMBIE_Moving,
	GARLICED_ZOMBIE_Stunned,
	GARLICED_ZOMBIE_Indifferent,
	PVZ_END_ENUM(GARLICED_ZOMBIE_)
};

struct GarlicAffectedZombieRecord
{
	GarlicAffectedZombieRecord()
	:ptrZombie(nullptr)
	,StartingRow(0)
    ,PlantLevel(1)
    ,GasDPS(0.0f)
	,TimeInCurrentState(0.0f)
	,State(GARLICED_ZOMBIE_Eating)
	{}
	
	RtWeakPtr<Zombie> ptrZombie;
	int StartingRow;
    int PlantLevel;
    float GasDPS;
	
	GarlicStateInfo StateInfo;
	pvztime_t TimeInCurrentState;
	GarlicEffectedZombieState State;
};

class PlantGarlic : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantGarlic, PlantFramework, RtClass);

	void Initialize() override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void UpdatePlantfood() override;
	
private:
	void createGasTrailEffect();
	void gasTheZombiesInMyRow();
	void gasThis(Zombie* zombie);
	
	bool isAffectedByEatingGarlic(BoardEntity *i_instigator);
	bool isAffectedByPlantfoodGarlic(BoardEntity *i_instigator);

	GarlicAffectedZombieRecord createGarlicAffectZombieRecordWith(Zombie* i_zombie);
    void pushZombieAway(Zombie* i_zombie);
	
	float m_timeToStartGas;
    float m_durationToPushZombie;
    float m_pushZombieEndTime;
};

class PlantAnimRig_Garlic : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Garlic, PlantAnimRig, RtClass);

	bool PlayIdleLooped() override;
	int CalcDamageStateCount() override;
	std::string getDamageIdleAnimationName() override { return "idle_damage"; }
};

class GarlicSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(GarlicSubsystem, GameSubSystem, RtClass);
	GarlicSubsystem();
	
	void Update() override;

	bool IsZombieIndifferent(const RtWeakPtr<Zombie> zombie);
	void AddZombie(GarlicAffectedZombieRecord& record);
	void RemoveZombie(Zombie* zombie);
	
	static bool ZombieIsValid(RtWeakPtr<Zombie> zombie);
	static bool ZombieNotValid(RtWeakPtr<Zombie> zombie) { return !ZombieIsValid(zombie); }
	
private:
	bool shouldAdd(Zombie* zombie);
	GarlicAffectedZombieRecord* findRecordFor(RtWeakPtr<Zombie> zombie);
	
	void updateRecord(GarlicAffectedZombieRecord& record);
	static bool isArmoredPharaoh(RtWeakPtr<Zombie> i_zombie);
	bool shouldStartRegretting(GarlicAffectedZombieRecord& record);
	bool shouldStartMoving(GarlicAffectedZombieRecord& record);
	bool shouldStartBeingStuned(GarlicAffectedZombieRecord& record);
	bool shouldRemoveZombie(GarlicAffectedZombieRecord& record);
	bool shouldStartBeingIndifferent(GarlicAffectedZombieRecord& record);
	
	void setState(GarlicAffectedZombieRecord& record, GarlicEffectedZombieState newState);

	void makeZombieRegretChoices(GarlicAffectedZombieRecord& record);
    void poisonZombie(GarlicAffectedZombieRecord& record);
    
	void stunZombieInRecord(GarlicAffectedZombieRecord& record, float duration);
	void spawnGarlicStinkLinesOverZombie(Zombie* i_zombie, pvztime_t i_cloudDuration);
	
	void setupZombieStunnedAnimation(GarlicAffectedZombieRecord& record);
    void setupZombiePoisonedAnimation(GarlicAffectedZombieRecord& record);
	
	void moveZombieToNewLane(GarlicAffectedZombieRecord& record);
	bool shouldMoveUp();
	void moveZombieUpOneRow(GarlicAffectedZombieRecord& record);
	void moveZombieDownOneRow(GarlicAffectedZombieRecord& record);
	void moveZombieByRows(GarlicAffectedZombieRecord& record, int numRows);
	
	std::vector<GarlicAffectedZombieRecord> m_garlicAffectedZombies;
	RtWeakPtr<GarlicProps> m_props;
};

#pragma mark
class Effect_GarlicStinkLines : private Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_GarlicStinkLines, Effect_PopAnim, RtClass);
	
	void StartStinkLines(Zombie* i_zombie, pvztime_t i_cloudDuration);
	
protected:
	void onUpdate() override;
	
private:
	RtWeakPtr<Zombie> m_targetZombie;
};

class Effect_PoisonGas : private Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_PoisonGas, Effect_PopAnim, RtClass);
    
    void PoisonZombie(Zombie* i_zombie, pvztime_t i_duration);
    
protected:
    void onUpdate() override;
    
private:
    RtWeakPtr<Zombie> m_targetZombie;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Garlic__) */
