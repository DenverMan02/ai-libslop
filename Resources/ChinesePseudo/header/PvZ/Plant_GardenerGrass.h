/*
 * 	Plant_GardenerGrass.h
 * 	
 * 	Created on: 2022-2-16
 * 		Author: kkdud
 */

#ifndef _PLANTGARDENERGRASS_H__
#define _PLANTGARDENERGRASS_H__



#include "PlantFramework.h"
#include "Zombie.h"
#include "EffectObject.h"



/*

	attack_start -> attack_loop -> attack_end ---> saw_recovery ---> idle

	fire_level5 ---> saw_recovery ---> idle

	fire_plantfood ---> idle

	saw_loop -> saw_end

 */

enum GardenerGrassState
{
	GARDENERGRASS_IDLE = STATE_FRAMEWORK_BEGIN,
	GARDENERGRASS_ATTACK,
	GARDENERGRASS_COOLDOWN,
	GARDENERGRASS_TRANSFORM
};


class GardenerGrassProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(GardenerGrassProps, PlantPropertySheet, RtClass);

    float InitialOverHeatingTime;
    float InitialCoolDownTime;
    float CoolDownTimeLevel2;
    float CoolDownTimeLevel345;
    float CritRateNormalPS;
    float CritRateLevel5PS;
    float CritRatePlantfoodPS;
    float DamageAmountNormal;
    float DamageAmountPlantfood; // DamageAmountPlantfood * level
    float BurnDamageAmountPerSecond;
    float SawPlantfoodAliveTime;
    float CoolDownAfterFireSawOnLV5;
};


class PlantGardenerGrass : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantGardenerGrass, PlantFramework, RtClass);

    void Initialize() override;
    void UpdateActions() override;
    void DoSpecial(int i_extraParam = 0) override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    
private:
    void setState(uint i_plantState);

    void onAnimStoppedCallback(const std::string& name) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void onApplyCondition(PlantConditions i_condition) override;
	void onEndCondition(PlantConditions i_condition) override;
    
    void findTargets();
    
    void setOverrideCoolDownDuration(float i_duration) { m_overrideCoolDownDuration = i_duration; }
    void clearOverrideCoolDownDuration() { m_overrideCoolDownDuration = 0; }

    float m_attackDuration;
    float m_coolDownDuration;
    float m_overrideCoolDownDuration;
    pvztime_t m_startTimer;  
    Rect m_damageRectNormal;    
    RtWeakPtr<class EffectObject_GardenerGrass> m_attackNormal;
    SexyVector3 m_originalPosition;
};


class PlantAnimRig_GardenerGrass : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_GardenerGrass, PlantAnimRig, RtClass);

	bool playAndStopAnimWithCallback(std::string i_animLabel, const std::string& i_callback = "");

	virtual std::string getPlantFoodMainAnimName() override;
};


class EffectObject_GardenerGrassProps : public EffectObjectPropertySheet
{
public:
	RT_CLASS_DEFINE(EffectObject_GardenerGrassProps, EffectObjectPropertySheet, RtClass);

	std::vector<std::string> CannotBeShaked;
};


class EffectObject_GardenerGrass : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_GardenerGrass, EffectObject, RtClass);

	struct SawDes
	{
		DamageInfo 	damageInfo;
		Rect		damageRect;
		bool 		isNeedControl;
		bool		isNeedIgnite;
		float 		critRatePS;
		float 		aliveTime;
		bool 		isStandAlone;
		float 		burnDPS;

		std::string 	pamName;
		std::string 	loopAnimLabel;
		std::string 	endAnimLabel;

		PlantPtr		plantPtr;
	};

	struct ShakeDes
	{
		ZombiePtr	zombiePtr;
		ZombieState zombieState;
		SexyVector3 zombiePosition;
	};

	void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void onUpdate() override;
	void onAnimStopped(const std::string& i_animLabel);
	bool canZombieBeShaked(ZombiePtr i_zombiePtr);
    void setValues(SawDes i_des);
    void clearShakedZombies();
    
private:
//    void clearShakedZombies();
    void onDestroy() override;
        
    void registerForEvents() override;
    void onZombieDestroyed(Zombie* i_zombie);
    
    EffectObject_GardenerGrass::ShakeDes* findShakedZombie(ZombiePtr i_zombiePtr);

    bool m_isNeedControl;
    bool m_isNeedIgnite;
    bool m_isStandAlone;
    float m_aliveTime;
    Rect m_damageRect;
    DamageInfo m_damageInfo;
    float m_critRatePS;
    float m_burnDPS;
    pvztime_t m_timer;
    pvztime_t m_nextCritTime;
    PlantPtr		m_plantPtr;
	std::string 	m_loopAnimLabel;
	std::string 	m_endAnimLabel;

	std::vector<ShakeDes> m_controlledZombies;
	std::vector<ShakeDes> m_newControlledZombies;
	std::vector<ZombiePtr> m_deadZombies;
};



#endif
