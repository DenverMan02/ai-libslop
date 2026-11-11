//
//  Plant_PyreVine.hpp
//  PlantsVersusZombies2
//
//  Created by Agarwal, Trisha on 6/10/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef Plant_ShineVine_hpp
#define Plant_ShineVine_hpp

#include "ComponentWarmingRadius.h"
#include "DamageInfo.h"
#include "GridItemAnimation.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "SunProducer.h"
#include "Zombie.h"
#include "PlantTypeVine.h"
class Zombie;
class Board;



STATE_ENUM_CHILD_BEGIN(ShineVineState, PlantState)
    ShineVineState_ATTACK2,

STATE_ENUM_END(ShineVineState)


class ShineVineProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ShineVineProps, PlantPropertySheet, RtClass);

    ShineVineProps(): SunProductionModifier(0) 
    {
        SunMoneyPerShot = 25;
		SunSuckInTime = 0.25f;
        AvatarCoinRate = 0.45f;
    }
    
	int SunMoneyPerShot;
	float SunSuckInTime;
    float AvatarCoinRate;
    int SunProductionModifier;
    PlantRestrictionSet SunProducerExcludelist;
};

class PlantTypeShinevine : public PlantTypeVine
{
public:
    RT_CLASS_DEFINE(PlantTypeShinevine, PlantTypeVine, RtClass);
};

class PlantShineVine : public PlantVineFramework
{
public:
    RT_CLASS_DEFINE(PlantShineVine, PlantFramework, RtClass);

    virtual ~PlantShineVine();

    void Initialize() override;
    void UpdateActions() override;
	void Draw(Graphics* g) override;
	void UpdateUnconditionally() override;
    virtual class Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

    bool CanApplyPlantfood() override;
    void ProduceSun(const PlantAction& i_fromAction) override;
    void DoSpecial(int i_extraParam = 0) override;
    void PostInitializeFromPropertySheet() override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    virtual void AutoFire() override;

	bool HasShadow() override { return false; }
    bool GetChargeAttack() const
    {
        return m_bChargeAttack;
    }
private:
    void setupForBasePlant(Plant* i_plant);
    bool isPlantExcluded(Plant* i_plant);
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

    bool hasValidTarget(PlantWeapon i_weapon);
    void tryAttackZombies(PlantWeapon i_weapon);
    void applyAttackEffects(Zombie* i_zombie, PlantWeapon i_weapon);
    ZombieTestFlag getZombieTargetExclusionFlags(PlantWeapon i_weapon);

//
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

	void SetTouchEnabled(bool i_enabled);
	bool onTouchEvent(const Sexy::Touch& i_touch);
    void ClearTouch();
	void onCancelEvent();

    int  GetSunMoneyPerShot();
	void startSunSuck();
	void drawSunSuck(Sexy::Graphics *i_g);

    bool DoTapAttack();
    bool Lv5Fire();

//
    PowerContext getPowerContextForWeapon(PlantWeapon i_weapon);
	void spendSun();
    virtual void ProduceCoin(const PlantAction& i_fromAction, const std::string& coinTypeName);
    Collectable * ProduceCollectable(const PlantAction& i_fromAction, const std::string &collectableTypeName);

//
    void onPlantPlaced(Plant* i_plant) override;
    void onPlantDied(Plant* i_plant) override;
    void onSunProductionTriggered(BoardEntity* i_entity);

	// virtual int		CalcRenderOrder() override;
    
    int m_sunProductionModifier = 0;
    pvztime_t m_nextAttackTime = 0;
    class PlantMagnifyingGrass* m_magnifyingGrass = nullptr;
    bool m_hostsTwinSunflower = false;
    bool m_modifyNextSunProduction = true;
    // bool m_boostMainPlant = false;
    int  damagezombiesize = 0;

    pvztime_t 			m_touchStartTime;
	pvztime_t           m_sunSuckStartTime;
    // pvztime_t           m_killtime;
    // pvztime_t           flashTime = 0.0;
    pvztime_t           m_attackcooldown;
    pvztime_t 			m_attackloopTime;
    bool                m_attackloopflag;
    Sexy::TouchID       m_touchIdent;
	bool                m_doingTapShot;
	bool                m_touchEnabled;
    bool                m_bChargeAttack;

	int                 m_sunSpentByGrass;
};

class PlantAnimRig_ShineVine : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_ShineVine, PlantAnimRig, RtClass);
	PlantAnimRig_ShineVine():i_attackTag("attacklv5_01")
    {
    }

	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	bool PlaySun();
	bool PlayTapAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void setAttackTag(const std::string& i_tag) { i_attackTag = i_tag; }
    std::string getPlantFoodOnAnimName() override;

//     virtual std::string getIdleAnimationName() override;

// private:
    std::string i_attackTag;
protected:
	void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
    
};



class ShineVineProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ShineVineProjectile, Projectile, RtClass);
    
    ShineVineProjectile()
    {
        chargeAttack = false;
        ratioAttack  = 1.0f;
    }
    
    void SetChargeAttack(bool i_chargeAttack, float i_ratioAttack);
    bool                handleImpact(BoardEntity* i_impactedEntity = nullptr) override;
    
protected:    
    virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
	void onProjectileInitialized() override;
    
private:
    bool chargeAttack;
    float ratioAttack;
};



#endif /* Plant_ShineVine_hpp */                                                                                                                    

