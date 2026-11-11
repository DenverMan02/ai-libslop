//  Plant_Gluttonydragon
//  Created by lfy
//  2024.01.02


#ifndef __PLANT_GLUTTONYDRAGON_H__
#define __PLANT_GLUTTONYDRAGON_H__

#include "PlantFramework.h"
#include "PlantAnimRig.h"
#include "PlantUtils.h"
#include "ActionSubSystem.h"
#include "PropertySheetBase.h"
#include "Plant_Nekotail.h"


enum GluttonydragonState
{
    GLUTTONYDRAGON_IDLE = STATE_FRAMEWORK_BEGIN,
    GLUTTONYDRAGON_PREFIRE,
    GLUTTONYDRAGON_FIRE,
    GLUTTONYDRAGON_FIRE_BULE,
    GLUTTONYDRAGON_FIRE_PURPLE,
    GLUTTONYDRAGON_TURN_BIG,
    GLUTTONYDRAGON_POSTFIRE,
    GLUTTONYDRAGON_NORMAL_CHARGED,
    GLUTTONYDRAGON_SPECIAL_CHARGED,
    GLUTTONYDRAGON_GNAW,
    
    GLUTTONYDRAGON_PFBEGINSUCKING,
    GLUTTONYDRAGON_PFSUCKING,
    GLUTTONYDRAGON_PFENDSUCKING,
    GLUTTONYDRAGON_PFBURPING,
    GLUTTONYDRAGON_PFENDBURP,
    GLUTTONYDRAGON_PFEND
           
};

class GluttonyDragonProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(GluttonyDragonProps, PlantPropertySheet, RtClass);
    GluttonyDragonProps() 
    {
        
    }       
    float Lv2ReducedConsume;
    float Lv3ReducedConsume;
    int Lv2IncreasedDmg;
    int Lv3IncreasedDmg;
    float MaxEnergyValue;
    int EnergyCost;
    int NumberOfPlantfoodTargets;
    int SuctionSpeed;
    pvztime_t AttackInterval;
    float GnawEnergy;
    float SnackEnergy;
    float BurpingSpeed;    
    float ChargedTimeStamp;
    std::vector<std::string> ZombieChewBlacklist;
    std::vector<int> ColorSwitch;
};

class PlantGluttonydragon : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantGluttonydragon, PlantFramework, RtClass);
    // virtual ~PlantGluttonydragon();
    
    void Initialize() override;
    void UpdateActions() override;         
    void ApplyPlantfood() override;    
    void CancelPlantfood() override;
    
    void setState(GluttonydragonState i_plantState);        
    bool CanBeTargetedBy(const BoardEntity* i_entity) override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    class Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void UpdatePlantfood() override;
    void Draw(Graphics* g) override;
    void UpdateUnconditionally() override;
    int  GetCurrentState();
    bool CanBeRangeTargeted() override;
protected:
    void onAnimStoppedCallback(const std::string& i_animLabel) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    bool CanEndPlantfood() override;
    bool CanApplyPlantfood() override { return true; }
    // void UpdatePlantfood();
    void onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect) override;
    
private:    

    void damageTargets(PlantWeapon i_plantWeapon);
    void findTargets(PlantWeapon i_plantWeapon, std::vector<BoardEntity*> &o_targets);
    bool canBeMovedByPlant(const Zombie* i_zombie) const;
    void markSuctionZombies();
    bool zombieIsInRange(const Zombie* i_zombie) const;
    float calcSuctionDestination(const Zombie* i_zombie) const;
    bool allSuctionZombiesAreWithinRange();
    void pullSuctionZombies();
    void pushAllZombies();
    DamageInfo getDamageInfo(PlantWeapon i_plantWeapon);
    bool zombieIsBlacklisted(const Zombie* i_zombie) const;
    void playFireEffect();
    void turnToBig(float i_oldEnergy, bool i_immed = true);
    AttachedEffect& createLv5Effect();    
    void playLevelupEffect();
    void playEndEffect();

    GluttonydragonState m_state;
    float m_energyValue;
    float m_halfEnergyValue;
    float m_resumeEnergy;
    std::vector<ZombiePtr> m_suctionZombies;
    pvztime_t m_attackInterval;
    pvztime_t m_attackTimeStamp;  
    pvztime_t m_chargedTimeStamp;
    pvztime_t m_fireDuration;
    pvztime_t m_bulletTime;
    pvztime_t m_bulletDuration;
    pvztime_t m_gnawTime;
    bool m_canLv5Effect;
    bool m_isSpecialFire;      
};

class GluttonyFire_Effect : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(GluttonyFire_Effect, Effect_PopAnim, RtClass);    
    virtual void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam);
    void SetOwner(PlantPtr i_owner) { m_owner = i_owner; }
private:
    PlantPtr m_owner;
};


class GluttonyProjectileProps : public NekotailStabProps
{
public:
    RT_CLASS_DEFINE(GluttonyProjectileProps, NekotailStabProps, RtClass);
    float burnDuration;
    float burnDps;
};

class GluttonyDragonProjectile : public NekotailStab
{
public:
    RT_CLASS_DEFINE(GluttonyDragonProjectile, NekotailStab, RtClass);
protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
};

class PlantAnimRig_Gluttonydragon : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Gluttonydragon, PlantAnimRig, RtClass);
    
    PlantAnimRig_Gluttonydragon() {}
        
    // void PlayAttack2Loop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    // void PlayAttack2End(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayDragonPlantfood(const std::string& i_animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);    
    void PlayDragonIdle(const std::string& i_animName = "baby_idle");
    void PlayFire(const std::string& i_animName);
    void PlayJumpOrLanding(const std::string& i_animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayGnaw(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayCharged(const std::string& i_animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
protected:
    std::string getPlantFoodOnAnimName() { return "plantfood_start"; }

private:    
    virtual std::string getIdleAnimationName();

};

#endif // End of __PLANT_GLUTTONYDRAGON_H__