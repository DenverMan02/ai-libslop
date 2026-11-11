//
//  Plant_Lemon.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-12-23.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Lemon_h
#define PlantsVersusZombies2_Plant_Lemon_h

#include "PlantFramework.h"
#include "Projectile.h"
#include "PlantUtils.h"

enum Lemon_State
{
    Lemon_Normal,
    Lemon_Level5_Attack,
    Lemon_Level5_Wait,
    Lemon_Level5_Back
};

class LemonPropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(LemonPropertySheet, PlantPropertySheet, RtClass);
    
    LemonPropertySheet() : AcidDamage(20) {}
    
    float AcidDamage;
    
    float EffectWaterTime;
    
    float WaterAcidDamge;

    float Level5AttackRate;
    
    std::vector<float> HelmAcidRate;
    std::vector<float> AllAcidRate;
};

class PlantLemon : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantLemon, PlantFramework, RtClass);
    
	void Initialize() override;
	
    bool CanApplyPlantfood() override;
    
	void ApplyPlantfood() override;
    
	void CancelPlantfood() override;
    
	bool CanEndPlantfood() override;
    
    void UpdateActions() override;
    
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    float GetLemonAcidDamage() { return GetProps<LemonPropertySheet>()->AcidDamage * m_plant->GetExtraDPSmodifier(); }
    
    void playBack();

private:
    
    class BeachStage* GetBeachStage();
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;

private:
    
    LemonPlantFoodCounter   m_LemonPlantFoodCounter;
    LemonNormalShooter      m_LemonNormalShooter;
    Lemon_State             m_LemonState;
};

class PlantAnimRig_Lemon : public PlantAnimRig
{
public:
    
	RT_CLASS_DEFINE(PlantAnimRig_Lemon, PlantAnimRig, RtClass);
    PlantAnimRig_Lemon();
    void setAttackState(int state);
    void setIdleState(int state);
    void playBack();
private:
    
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;
private:
    int m_attackState = 1;
    int m_idleState = 1;
};

class LemonRainEffectAnim : public Effect_PopAnim
{
public:
    
    RT_CLASS_DEFINE(LemonRainEffectAnim, Effect_PopAnim, RtClass);
    
    void onAnimStopped(const std::string& i_animLabel) override;
    
    void SetEntity(BoardEntityPtr pSrc, BoardEntityPtr pTarget);
    
private:

    BoardEntityPtr m_pTargetEntity;
    BoardEntityPtr m_pSrcEntity;
    
};

class LemonLevel5Property : public Projectile
{
public:
    RT_CLASS_DEFINE(LemonLevel5Property, Projectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual bool OnCollideRoof() override;
    void setPlant(Plant* i_plant);
protected:
    virtual void onUpdate(pvztime_t i_dt) override;
private:
    RtWeakPtr<Plant> m_bindPlant;
};
#endif
