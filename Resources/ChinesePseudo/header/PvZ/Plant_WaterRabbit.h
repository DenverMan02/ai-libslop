//
//  Plant_WaterRabbit.h
//  PlantsVersusZombies2
//
//  Created by Sai Prasad on 10/28/22.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_WATERRABBIT_H__
#define __PLANT_WATERRABBIT_H__

#include "PlantFramework.h"
#include "RtObject.h"
#include "PlantAnimRig.h"


namespace
{
    const int k_FinalStrikeIndex = 4;
    const int k_MaxChiStacks = 5;
}

enum WaterRabbitState
{
    WATERRABBIT_IDLE = STATE_FRAMEWORK_BEGIN,
    WATERRABBIT_ATTACK,
    WATERRABBIT_THUNDERCLAP,
    WATERRABBIT_PLANTFOOD,
    WATERRABBIT_LEVELUP
};

struct KnockbackData
{
    float KnockbackCells;
    float KnockbackHeight;
    float KnockbackTime;
};

class WaterRabbitProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(WaterRabbitProps, PlantPropertySheet, RtClass);
    
    int NormalStrikeDamage;
    int FinalStrikeDamage;
    KnockbackData KnockbackDetails;
    std::vector<float> AttackMultiplier;
    std::vector<float> KnockbackMultiplier;
    std::vector<int> MaxTargetCounts;
    float TimeBetweenChains;
    float ChiResetTimer;
    int ThunderClapActionDamage;
    int FoodPlayCount;
    float ThunderClapDamageReductionDuration;
    float ThunderClapDamageReduction;
    ClassRestrictionSet AffectEatDPSExcludelist;
    ClassRestrictionSet KnockbackExcludelist;
    int MaxDPS;//This is a dummy variable added for stats purpose
};

class PlantWaterRabbit : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantWaterRabbit, PlantFramework, RtClass);
	
    PlantWaterRabbit();

	void Initialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	int CalcRenderOrder() override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    bool CanEndPlantfood() override;
    void DoEventCall(RealObject* pTarget) override;
    bool CanBeWatered() override;

protected:
    void onAnimStoppedCallback(const std::string& i_animLabel) override;
    void Idle() override;
    
private:
    void setState(const uint i_state);
    BoardEntityPtr getTarget(std::vector<BoardEntityPtr>& o_entityList);
	bool findTargetAndPlayAttackAnim();
    BoardEntityPtr getZombieTarget(std::vector<BoardEntityPtr>& o_entityList);
    // BoardEntityPtr getGridTarget(std::vector<BoardEntityPtr>& o_entityList);
    bool shouldChangeTarget();
    bool isValidTarget(BoardEntity* i_target);
    bool canAffectEatDPS(Zombie* i_zombie);
    bool canKnockBack(Zombie* i_zombie);
    bool canBeLaunchedByPlants(Zombie* i_zombie) const;
    void updateChiStacks(int i_value, bool i_animNeeded = true);
    
    void attackUseAction();
    void thunderAttackUseAction(bool i_isPf = true, bool i_isKnock = false);
    
    void registerForEvents() override;
    void unregisterForEvents() override;
    bool onTouchEvent(const Sexy::Touch& i_touch);
    
	// Serialized
    int m_plantFoodPlayCount;
    pvztime_t m_lastAttackTime;
    pvztime_t m_lastLevelupTime;
    pvztime_t m_autoLevelupTime;
    BoardEntityPtr m_currentTarget;
    int m_currentStrike;
    int m_chiStacks;
    int m_maxTargetsCount;
    // Not Serialized
    Sexy::TouchID    m_touchIdent;
    int m_pfCount;
};

class PlantAnimRig_WaterRabbit : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_WaterRabbit, PlantAnimRig, RtClass);

    bool PlayPreviewAnim(bool bHideLayer = false);
    bool PlayBasicAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayThunderclapAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayLevelUp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayPlantFoodAttack(const std::string& i_animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    void UpdateLayer(int i_level);
    
private:
    // Not Serialized
    std::map<int, int> m_layerMapping = {{0, 0}, {1, 1}, {2, 1}, {3, 2}, {4, 2}, {5, 3}, {6, 3}};
};


#endif  //__PLANT_WATERRABBIT_H__
