#ifndef Plant_Bromelblade_h
#define Plant_Bromelblade_h

#include "Plant.h"
#include "Projectile.h"
#include "PlantFramework.h"
#include "GameSubSystem.h"
#include "Precompile.h"
#include "GridItemAnimation.h"

enum BromelbladeState
{
    BROMELBLADE_STATE_PLANTING = STATE_FRAMEWORK_BEGIN,
    BROMELBLADE_STATE_IDLE,
    BROMELBLADE_STATE_ATTACK_NORMAL,
    BROMELBLADE_STATE_ATTACK_PROVOKE,
    BROMELBLADE_STATE_ATTACK_PIERCE,
    BROMELBLADE_STATE_ATTACK_SLASH,
    BROMELBLADE_STATE_ATTACK_LV5,
    BROMELBLADE_STATE_PLANTFOOD,
};

#pragma mark - PlantBromelbladeProps

class PlantBromelbladeProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantBromelbladeProps, PlantPropertySheet, RtClass);

    PlantBromelbladeProps()
    {
        RateSlash = 0.2;
        RateLevel5 = 0.5;
    }

    float RateSlash;
    float RateLevel5;
    std::vector<std::string> ZombieBlacklist;
};

#pragma mark - PlantBromelbladeProps

class PlantBromelblade : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantBromelblade, PlantFramework, RtClass);
    
    virtual void Initialize() override;
    virtual void UpdateActions() override;
    virtual bool CanApplyPlantfood() override;
    virtual void ApplyPlantfood() override;
    virtual void CancelPlantfood() override;
    virtual void UpdatePlantfood() override;

    virtual bool CanBeShoveled() override;
	virtual bool CanBeTargeted() override;
	virtual bool IsInvincible() const override;
    virtual Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    
    virtual void onKilled(bool i_instantKill) override;
    virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

private:
    bool            isZombieBlacklisted(ZombiePtr i_zombie);
    void            setState(uint i_plantState);
    bool            canProvokeZombie(RtWeakPtr<BoardEntity> i_target);
    float           getCoolDownByWeapon(PlantWeapon i_weapon);
    
    void            UpdateTargetPosition();
    void            UpdateTargetPositionAndRotation();
    void            EndProvoke();

    void            dealDamage(PlantWeapon i_weapon = PlantWeapon::WEAPON_PRIMARY);
    virtual void    onAnimStoppedCallback(const std::string& name) override;
    bool            isZombieArmorType(const ZombiePtr i_zombie);
    RtWeakPtr<BoardEntity> FindTarget(PlantWeapon i_plantWeapon);

    int m_attackCounter;

    Sexy::SexyVector3 m_startPosition;
    Sexy::SexyVector3 m_endPosition;
    float m_startZombieRotation;
    float m_endZombieRotation;

    Sexy::SexyVector3 m_rotateStartPosition;
    Sexy::SexyVector3 m_rotateEndPosition;

    float m_currentAimeRate;
    float m_timeStartPush;
    pvztime_t m_elapsedTime;
    pvztime_t m_steadyTime;
    ZombiePtr m_targetZombie;
    bool m_IsonProvoke;
    bool m_IsPushEnd;

    pvztime_t m_plantCoolDownTime;
    pvztime_t m_chargeEndTime;
    pvztime_t m_chargeTime;
};

#pragma mark - PlantAnimRig_Bromelblade

class PlantAnimRig_Bromelblade : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Bromelblade, PlantAnimRig, RtClass);

    PlantAnimRig_Bromelblade();
    void SetAvatar(bool i_avatar);

private:
    virtual std::string getPlantFoodMainAnimName() override;

    bool m_IsAvatarEnable;
};

#endif