
#ifndef Plant_DragonCane_hpp
#define Plant_DragonCane_hpp

#include "PlantFramework.h"

enum DragonCaneState
{
    CANESTATE_IDLE = STATE_FRAMEWORK_BEGIN,
    CANESTATE_NORMAL_ATTACK,
    CANESTATE_ADVANCED_ATTACK,
    CANESTATE_SPECIAL_ATTACK,
    CANESTATE_PLANTFOOD,
};

class DragonCaneProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(DragonCaneProps, PlantPropertySheet, RtClass);
    
    DragonCaneProps()
    {
        KnockbackChance1 = 0.7;
        KnockbackChance2 = 1.0;
        KnockbackTime = 0.5;
        KnockbackHeight = 130;
        KnockbackGridX1Min = 1;
        KnockbackGridX1Max = 3;
        KnockbackGridX2Min = 2;
        KnockbackGridX2Max = 5;
    }
    
    float KnockbackChance1;
    float KnockbackChance2;
    float KnockbackTime;
    float KnockbackHeight;
    int KnockbackGridX1Min;
    int KnockbackGridX1Max;
    int KnockbackGridX2Min;
    int KnockbackGridX2Max;
};

class PlantDragonCane : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantDragonCane, PlantFramework, RtClass);
    
    virtual void Initialize() override;
    virtual void UpdateActions() override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    virtual bool CanApplyPlantfood() override;
    virtual void ApplyPlantfood() override;
    virtual void CancelPlantfood() override;
    virtual void UpdatePlantfood() override;
    
    virtual int CalcRenderOrder() override;
protected:
    virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    bool shouldKnockback(BoardEntity* i_impactedEntity);
    void knockbackZombie(BoardEntity* i_impactedEntity);
    std::vector<BoardEntity*> SearchNearZombies(PlantWeapon i_plantWeapon);
    void ApplyDamageToEntities(PlantWeapon i_plantWeapon);
    void ApplyDamageToEntities(PlantWeapon i_plantWeapon, std::vector<BoardEntity*> &entities);
protected:
    void NormalAttackHandler();
    void PunchAttackHandler();
    void TurnStickAttackHandler();
    void PfAttackHandler();
    void ExtraAttackHandler();
    
    void GeneratePfAttackEffect();
    void GenerateParticleEffect(float offsetX = 0, float offsetY = 0);
    float GetParticleOffsetX();
    float GetParticleOffsetY();
    float GetParticleTimeInterval();
    bool IsValidZombieTarget(Zombie* i_zombie);
private:
    bool FindTargetsAndPlayAttackAnim();
    bool WouldKillTarget(ZombiePtr i_targetZombie, const DamageInfo &damageInfo);
    void filterTargets(const std::vector<BoardEntity*>& i_entities, std::vector<BoardEntity*> *o_targets);
private:
    pvztime_t m_plantfoodDamageEndTime;
    pvztime_t m_pfDamageStartTime;
    pvztime_t m_pfDamageDuration;
    pvztime_t m_particleStartTime;
    pvztime_t m_effectInterval;
    float m_particleOffsetX;
    float m_particleOffsetY;
};

#pragma mark - PlantAnimRig_DragonRoar

class PlantAnimRig_DragonCane : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_DragonCane, PlantAnimRig, RtClass);

    virtual bool PlayIdleLooped() override;
    
    bool PlayNormalAttack();
    bool PlayAdvancedAttack();
    bool PlayAdvancedExtAttack();
    bool PlaySpecialAttack();
private:
    std::string getPlantFoodOffAnimName() override;
    
private:
    std::string m_lastUsedIdleAnim;
};

#endif /* Plant_DragonCane_hpp */
