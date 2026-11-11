//
//  Plant_Endurian.h
//  PlantsVersusZombies2
//
//  Created by Kelmore, Austin on 4/27/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Endurian__
#define __PlantsVersusZombies2__Plant_Endurian__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "GameSubSystem.h"
#include "RestrictionSet.h"

class PlantEndurian : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantEndurian, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;

	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	void TakeSmashAttack(ZombiePtr i_srcZombie) override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
    void	 onKilled(bool i_instantKill) override;
    void	 NotifySetHidden(bool i_newValue, bool i_oldValue) override;
    void onApplyCondition(PlantConditions i_condition) override;
    void onEndCondition(PlantConditions i_condition) override;
    bool CanBeWatered() override;
protected:

	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:

	enum State
	{
		STATE_START_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_ATTACK,
		STATE_FINISH_ATTACK
	};

	void setState(const uint i_state);
	void updateShieldLayers();
    void CreateGasEffect();
    void ShowGasEffect(bool show);
    float GetFullSheldHealth();
    
	pvztime_t m_lastAttack;
	float m_shieldHealth;
	int m_pfDamageHits;
};

class PlantAnimRig_Endurian : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Endurian, PlantAnimRig, RtClass);

	void onPopAnimInitialized() override;

	void StartAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void LoopAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void StopAttacking(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SetArmorPct(const float i_armorPct);
    
    std::vector<std::string> GetArmorLayers();
};

class EndurianProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(EndurianProps, PlantPropertySheet, RtClass);

	EndurianProps()
	{
		PlantFoodShieldHitpoints = 8000;
        AvatarShieldHitpoints = 0;
	}

	float PlantFoodShieldHitpoints;
    float AvatarShieldHitpoints;
    std::vector<float> GasDamage;
    ZombieRestrictionSet ZombieAffectedByGas;
};

class EndurianGasSubsystem : public GameSubSystem
{
public:
    class Item
    {
    public:
        float damage;
        PlantPtr plant;
        Item(float damage = 0, const PlantPtr& plant = PlantPtr());
    };
public:
    RT_CLASS_DEFINE(EndurianGasSubsystem, GameSubSystem, RtClass);
    void Register(const PlantPtr& plant, float damage);
    void Unregister(const PlantPtr& plant);
    void Update() override;
    EndurianGasSubsystem();
private:
    static bool Sort(const Item& item1, const Item& item2);
    bool IsBlackList(Zombie* zombie);
private:
    const ZombieRestrictionSet* m_zombieAffected = nullptr;
    pvztime_t m_nextUpdate;
    std::vector<Item> m_item;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Endurian__) */
