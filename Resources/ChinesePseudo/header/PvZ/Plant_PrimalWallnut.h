#ifndef __PLANT_PRIMAL_WALLNUT_H__
#define __PLANT_PRIMAL_WALLNUT_H__

#include "RtObject.h"
#include "Plant_Wallnut.h"
#include "PlantAnimRig_Wallnut.h"

enum PrimalWallnut_State
{
    PWNS_STATE_BEGIN = STATE_FRAMEWORK_BEGIN,
    PWNS_STATE_CURE,
};

enum PWN_STATE
{
    PWNS_SPAWN = PLANTANIM_USERDEFINED,
    PWNS_MINIIN,
    PWNS_MINIIDLE,
    PWNS_CURE,
    PWNS_GROWTHUP,
};

class PrimalWallnutProps : public WallnutProps
{
public:
	RT_CLASS_DEFINE(PrimalWallnutProps, WallnutProps, RtClass);
    
    float 	SmashDamage = 0.0f;
    float   HealthSpan  = 20.0f;
    float   HealthIdleSpan = 5.0f;
    float   HealthCureValue = 1000.0f;
    std::vector<int> MiniPrimalWallNutHP;
};


class PlantPrimalWallnut : public PlantWallnut
{
public:
	RT_CLASS_DEFINE(PlantPrimalWallnut, PlantWallnut, RtClass);
    
    virtual void Initialize() override;
    virtual void onKilled(bool i_instantKill) override;
    virtual void TakeSmashAttack(ZombiePtr i_instigator) override;
    virtual bool IsDelayDestroy() override;
    virtual void ApplyPlantfood() override;
    virtual bool CanApplyPlantfood() override;
    virtual bool CanBeTargeted() override;
    virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void setState(uint i_plantState);
    virtual void UpdateActions() override;
    void OnAnimStopped(const std::string &i_animName);
    void sendCureProjectile();
private:
    int BirthMiniWallnutHP();
    bool IsOutofBoard();

private:
    void applySmashDamage(ZombiePtr i_srcZombie);
    
    float healthTime;
    float healthIdleTime;
    bool  isCuring;
    float m_growthTime;
};

class PlantAnimRig_PrimalWallnut : public PlantAnimRig_Wallnut
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_PrimalWallnut, PlantAnimRig_Wallnut, RtClass);
    
    void PlayBabyIn(AnimStoppedDelegate i_onStopDelegate);
    void onAnimStopped() override;
    void PlayMiniIdleLooped();
    void PlayBabyIn();
    void PlayGrowUp();
    std::string getPlantFoodOnAnimName() override;
    
    void PlayCure(AnimStoppedDelegate i_onStopDelegate);

};

#endif //__PLANT_PRIMAL_WALLNUT_H__
